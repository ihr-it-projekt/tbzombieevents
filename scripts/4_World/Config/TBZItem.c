class TBZItem
{
    string type;
    ref array<ref TBZItem> attachments;

    void TBZItem(string type, array<ref TBZItem> attachments = null) {
        this.type = type;
		this.attachments = attachments;
    }
}
