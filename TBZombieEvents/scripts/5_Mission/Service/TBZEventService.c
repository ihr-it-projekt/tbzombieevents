class TBZEventService : Managed {
    private ref TBZombieEventConfig config;
    private ref Timer gameTimer = new Timer;
    private ref array<ref TBZEventLocation> locations = new array<ref TBZEventLocation>;
    private int oldLocationIndex;
    private ref TBZLocationBuilder locationBuilder = new TBZLocationBuilder;

    void TBZEventService() {
        config = new TBZombieEventConfig;
        SetEventLocations(config.locations);
        gameTimer.Run(60, this, "StartEvent");
    }

    void ~TBZEventService() {
        if(gameTimer) {
            gameTimer.Stop();
        }
    }

    void StartEvent() {
        bool canStart = true;
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        if(config.playerControlled && config.minCountPlayer > 0) {
            if(players.Count() < config.minCountPlayer) {
                canStart = false;
            }
        }

        if(config.timeControlled) {
            int hour;
            int minute;
            int second;

            GetHourMinuteSecond(hour, minute, second);

            if(hour < config.startTimeHour || hour > config.endTimeHour) {
                canStart = false;
            } else if((hour == config.endTimeHour && minute > config.endTimeMinute) || (hour == config.startTimeHour && minute < config.startTimeMinute)) {
                canStart = false;
            }
        }

        if(locations.Count() == 0) {
            canStart = false;
        } else {
            foreach(TBZEventLocation location: locations) {
                if(location.IsActive()) {
                    canStart = false;
                    break;
                }
            }
        }

        if(canStart) {
            int newLocationIndex = locations.GetRandomIndex();

            while(newLocationIndex == oldLocationIndex && locations.Count() > 1) {
                newLocationIndex = locations.GetRandomIndex();
            }

            TBZEventLocation currentLocation = locations.Get(newLocationIndex);
            currentLocation.SetActive();

            locationBuilder.Create(currentLocation);

            oldLocationIndex = newLocationIndex;

            gameTimer.Stop();
            int randTimer = Math.RandomIntInclusive(config.minMinutesBetweenEvents, config.maxMinutesBetweenEvents);
            gameTimer.Run((currentLocation.durationInMinutes + randTimer) * 60, this, "StartEvent");

            for(int i = 0; i < players.Count(); i++) {
                PlayerBase player;
                Class.CastTo(player, players.Get(i));

                string message = "#new_event_start " + currentLocation.name;

                if(currentLocation.playerNeedsItemsToEnter && currentLocation.neededItemsToEnter.Count()) {
                    string neededItems = "";
                    foreach(TBZNeededItem itemNeeded: currentLocation.neededItemsToEnter) {
                        neededItems = neededItems + GetItemDisplayName(itemNeeded.name) + ";" ;
                    }

                    message = message + " #need_item " + neededItems;
                }

                SendMessageToPlayerZombieEvent(message, player);
            }
        } else {
            gameTimer.Stop();
            gameTimer.Run(60, this, "StartEvent");
        }
    }

    private void SetEventLocations(array<ref TBZEventLocationConfig> locationsConfigs) {
        foreach(TBZEventLocationConfig locationConfig: locationsConfigs) {
            TBZEventLocation location = new TBZEventLocation(locationConfig);
            locations.Insert(location);
        }
    }

};