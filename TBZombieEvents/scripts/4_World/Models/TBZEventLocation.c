class TBZEventLocation {

	string name;
    vector position;
    float radiusOfSpawn;
    int countOfMaxZombies;
    int countOfMinZombies;
    int countOfMaxItems;
    int countOfMinItems;
    ref array<string> zombieTypes;
    ref array<ref TBZItem> itemTypes;
    ref array<ref TBZEventObject> eventObjects;
    ref array<ref TBZNeededItem> neededItemsToEnter;
    bool playerNeedsItemsToEnter;
    bool zombieReSpawn;
    int zombieReSpawnTick;
    int durationInMinutes;
    bool randomItemHealths;
    int randomItemHealthsMax;
    int randomItemHealthsMin;

    private ref array<ref TBZRememberedZombies> creaturesCollection;
    private ref array<ref TBZRememberedObjects> itemCollection;
    private ref array<ref TBZRememberedBuildings> buildingCollection;
    private bool isActive;
    private ref Timer gameTimer;
    private ref Timer zombieTimer;
    private ref Timer zombieAttackTimer;
    private ref Timer playerCheckTimer;

    void ~TBZEventLocation() {
        if (gameTimer) {
            gameTimer.Stop();
        }
        if (zombieTimer) {
            zombieTimer.Stop();
        }
        if (zombieAttackTimer) {
            zombieAttackTimer.Stop();
        }
        if (playerCheckTimer) {
            playerCheckTimer.Stop();
        }
		SetInactive();
    }

    void TBZEventLocation(TBZEventLocationConfig config) {
         name = config.name;
         position = config.position;
         radiusOfSpawn = config.radiusOfSpawn;
         countOfMaxZombies = config.countOfMaxZombies;
         countOfMinZombies = config.countOfMinZombies;
         countOfMaxItems = config.countOfMaxItems;
         countOfMinItems = config.countOfMinItems;
         zombieTypes = config.zombieTypes;
         itemTypes = config.itemTypes;
         neededItemsToEnter = config.neededItemsToEnter;
         playerNeedsItemsToEnter = config.playerNeedsItemsToEnter;
         zombieReSpawn = config.zombieReSpawn;
         zombieReSpawnTick = config.zombieReSpawnTick;
         durationInMinutes = config.durationInMinutes;
         randomItemHealths = config.randomItemHealths;
         randomItemHealthsMax = config.randomItemHealthsMax;
         randomItemHealthsMin = config.randomItemHealthsMin;
         eventObjects = config.eventObjects;

         creaturesCollection = new array<ref TBZRememberedZombies>;
         itemCollection = new array<ref TBZRememberedObjects>;
		 buildingCollection = new array<ref TBZRememberedBuildings>;
         isActive = false;
    }

    void AddCreature(DayZCreatureAI creature) {
        if (creature) {
            ZombieBase zombie = ZombieBase.Cast(creature);
            if (zombie) {
                zombie.maxRadius = radiusOfSpawn;
                zombie.attackPosition = position;
            }

            creaturesCollection.Insert(new TBZRememberedZombies(creature));
        }
    }

    void AddItem(ItemBase item) {
        if (!item) {
            return;
        }

		if (randomItemHealths) {
			item.SetHealth(Math.RandomIntInclusive(randomItemHealthsMin, randomItemHealthsMax));
		}

        itemCollection.Insert(new TBZRememberedObjects(item));
    }

    void AddBuilding(Building house) {
        buildingCollection.Insert(new TBZRememberedBuildings(house));
    }

    void SetActive() {
        isActive = true;

        gameTimer = new Timer();
		gameTimer.Run(durationInMinutes * 60, this, "SetInactive");
        zombieTimer = new Timer();
        zombieTimer.Run(1, this, "CheckZombies", null, true);
        zombieAttackTimer = new Timer();
        zombieAttackTimer.Run(1, this, "CheckZombieAttacks", null, true);
		if (playerNeedsItemsToEnter && neededItemsToEnter.Count() > 0) {
			playerCheckTimer = new Timer();
        	playerCheckTimer.Run(10, this, "CheckPlayers", null, true);
		}
    }

    void CheckZombies() {
        foreach(TBZRememberedZombies rm_creature: creaturesCollection) {
            if(zombieReSpawn && rm_creature.CanReSpawn(zombieReSpawnTick)) {
                DayZCreatureAI creature = TBZCreator.SpawnCreature(GetRandomSpawnPosition(), zombieTypes.GetRandomElement());
                if (creature != null) {
                    AddCreature(creature);
                    rm_creature.isReplaced();
                }
            }

            if (rm_creature.MustRelocated(position, radiusOfSpawn)) {
                rm_creature.Relocate(GetRandomSpawnPosition());
            }
        }
    }

	void CheckPlayers() {
		array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
		for (int i = 0; i < players.Count(); i++ ) {
            DayZPlayer player;
            Class.CastTo(player, players.Get(i));
			
			float distance = vector.Distance(position, player.GetPosition());
			if (distance <= radiusOfSpawn) {
        		ItemBase item;
				float decreaseFactor = 0;
				string missingItems = "";
				foreach (TBZNeededItem itemNeeded: neededItemsToEnter) {
                	EntityAI inventoryItem = player.FindAttachmentBySlotName(itemNeeded.position);

					if (!inventoryItem || inventoryItem.IsRuined() || !inventoryItem.IsKindOf(itemNeeded.name)) {
						decreaseFactor += itemNeeded.healthDecrease;
						missingItems = missingItems + itemNeeded.position + ": "+  GetItemDisplayName(itemNeeded.name) + ";";
					}
				}

				if (decreaseFactor != 0) {
                    SendMessageToPlayerZombieEvent("#has_not_items " + missingItems, player);

                    player.DecreaseHealth(decreaseFactor);
				}
			}
		}
	}

    void SetInactive() {
        if (false == isActive) {
            return;
        }

        if (gameTimer) {
            gameTimer.Stop();
        }

        if (zombieTimer) {
            zombieTimer.Stop();
        }

        if (playerCheckTimer) {
            playerCheckTimer.Stop();
        }

        foreach(TBZRememberedZombies creature: creaturesCollection) {
            creature.ClearObject();
        }

        foreach(TBZRememberedObjects item: itemCollection) {
            item.ClearObject();
        }

        foreach(TBZRememberedBuildings building: buildingCollection) {
            building.ClearObject();
        }

        creaturesCollection = new array<ref TBZRememberedZombies>;
        itemCollection = new array<ref TBZRememberedObjects>;
        buildingCollection = new array<ref TBZRememberedBuildings>;

        isActive = false;

        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        for ( int i = 0; i < players.Count(); i++ ) {
            PlayerBase player;
            Class.CastTo(player, players.Get(i));

            SendMessageToPlayerZombieEvent("#event_end " + name, player);
        }
    }

    bool IsActive() {
        return isActive;
    }

    vector GetRandomSpawnPosition() {
		vector random;
		
		random[0] = position[0] + Math.RandomFloatInclusive(radiusOfSpawn * -1, radiusOfSpawn);
		random[2] = position[2] + Math.RandomFloatInclusive(radiusOfSpawn * -1, radiusOfSpawn);
		random[1] = position[1];
		
		return random;
    }

};