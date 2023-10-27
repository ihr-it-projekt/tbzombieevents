class TBZRememberedObjects {
    private ItemBase object;
    private vector initialPosition;

    void TBZRememberedObjects(ItemBase rm_object) {
        object = rm_object;
        initialPosition = object.GetPosition();
    }

    void ClearObject() {
        if (object && object.GetPosition() == initialPosition) {
            object.Delete();
        }
    }
};