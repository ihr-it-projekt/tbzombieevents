class TBZNeededItem
{
    string name;
    string position;
    float healthDecrease = 5.0;

    void TBZNeededItem(string itemName, string itemPosition) {
        name = itemName;
        position = itemPosition;
    }
}