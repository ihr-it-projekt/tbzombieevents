class TBZRememberedZombies {
    private ZombieBase zoombie;
    private DayZCreatureAI object;
    private bool isReplaced;
    private int tick;
    private int tickNoAttack;

    void TBZRememberedZombies(DayZCreatureAI rm_object) {
        object = rm_object;
        zoombie = ZombieBase.Cast(rm_object);

        isReplaced = false;
        tick = 0;
        tickNoAttack = 0;
    }

    void ClearObject() {
        if(object) g_Game.ObjectDelete(object);
    }

    bool CanReSpawn(int tickForRespawn) {
        if((object && object.IsAlive()) || isReplaced) {
            return false;
        }
        ++tick;

        if(tick >= tickForRespawn) {
            return true;
        }

        return false;
    }

    bool MustRelocated(vector eventPosition, int radiusEventPosition) {
        if(!object || !object.IsAlive()) {
            return false;
        }

        float distance = vector.Distance(eventPosition, object.GetPosition());

        return distance > radiusEventPosition;
    }

    void Relocate(vector newPosition) {
        object.SetPosition(newPosition);
    }


    void isReplaced() {
        isReplaced = true;
    }
};