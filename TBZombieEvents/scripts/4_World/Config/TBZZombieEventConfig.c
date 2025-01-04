class TBZombieEventConfig {
    string version = "1";
    bool timeControlled;
    int startTimeHour;
    int startTimeMinute;
    int endTimeMinute;
    int endTimeHour;
    bool playerControlled;
    int minCountPlayer;
    int minMinutesBetweenEvents
    int maxMinutesBetweenEvents
    ref array<ref TBZEventLocationConfig> locations;

    void TBZombieEventConfig() {
        if(!Load()) {
            timeControlled = false;
            startTimeHour = 18;
            startTimeMinute = 0;
            endTimeHour = 22;
            endTimeMinute = 0;
            playerControlled = false;
            minCountPlayer = 1;
            minMinutesBetweenEvents = 10;
            maxMinutesBetweenEvents = 60;
            locations = new array<ref TBZEventLocationConfig>;
            locations.Insert(new TBZEventLocationConfig);
            Save();
        }
    }

    private bool Load() {
        if(GetGame().IsServer() && FileExist(TB_ZOMBIE_EVENT_CONFIG_PATH)) {
            JsonFileLoader<TBZombieEventConfig>.JsonLoadFile(TB_ZOMBIE_EVENT_CONFIG_PATH, this);
            return true;
        }
        return false;
    }

    private void Save() {
        if(GetGame().IsServer()) {
            JsonFileLoader<TBZombieEventConfig>.JsonSaveFile(TB_ZOMBIE_EVENT_CONFIG_PATH, this);
        }
    }
};