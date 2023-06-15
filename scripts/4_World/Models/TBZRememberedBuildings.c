class TBZRememberedBuildings {
    private Building object;
    private vector initialPosition;

    void TBZRememberedBuildings(Building rm_object) {
        object = rm_object;
    }

    void ClearObject() {
        object.Delete();
    }
};