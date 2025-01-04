class TBZMessageMenu {
    private ref TBZUIItemCreator creator;
    private MultilineTextWidget message;
    private ref Timer timer;
    private string messageText;
    private Widget layoutRoot;


    void ~TBZMessageMenu() {
        if(layoutRoot) layoutRoot.Show(false);
    }


    void Init() {
        creator = new TBZUIItemCreator("TBZombieEvents/layout/TBZ_Message.layout");
        message = creator.GetMultilineTextWidget("Announcements");
        layoutRoot = creator.GetLayoutRoot();

        layoutRoot.Show(false);
        timer = new Timer;
    }

    void SetText(string text) {
        messageText = text;
    }

    void Show() {
        message.SetText(messageText);
        layoutRoot.Show(true);
        timer.Run(10, this, "CloseMenu");
    }

    void CloseMenu() {
        layoutRoot.Show(false);
        timer.Stop();
    }
}
