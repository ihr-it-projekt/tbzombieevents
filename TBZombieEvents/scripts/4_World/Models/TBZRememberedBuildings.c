class TBZRememberedBuildings {
    private Object object;
    private vector initialPosition;

    void TBZRememberedBuildings(Object rm_object) {
        object = rm_object;
    }

    void ClearObject() {
        if(object) {
            g_Game.ObjectDelete(object);
        }
    }
};