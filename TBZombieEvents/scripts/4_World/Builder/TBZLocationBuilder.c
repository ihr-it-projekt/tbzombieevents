class TBZLocationBuilder {

    void Create(TBZEventLocation location) {

        int zombiesCount = Math.RandomIntInclusive(location.countOfMinZombies, location.countOfMaxZombies);
        int itemsCount = Math.RandomIntInclusive(location.countOfMinItems, location.countOfMaxItems);

        int i = 0;
        while(i < zombiesCount) {
            DayZCreatureAI creature = TBZCreator.SpawnCreature(location.GetRandomSpawnPosition(), location.zombieTypes.GetRandomElement());
            if(creature) {
                location.AddCreature(creature);
            }
            i++;
        }

        for(i = 0; i < itemsCount; i++) {
            ItemBase item = TBZCreator.SpawnItem(location.GetRandomSpawnPosition(), location.itemTypes.GetRandomElement());
            if(item) {
                location.AddItem(item);
            }
        }

        foreach(TBZEventObject eventObjects: location.eventObjects) {
            Object house = TBZCreator.Spawn(eventObjects.position, eventObjects.orientation, eventObjects.name);
            if(house) {
                location.AddBuilding(house);
            }
        }
    }
}