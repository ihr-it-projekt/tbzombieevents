class TBZItem
{
    string type;
    ref array<ref TBZItem> attachments;

    void TBZItem(string _type, array<ref TBZItem> _attachments = null) {
        this.type = _type;
		this.attachments = _attachments;
    }
}
