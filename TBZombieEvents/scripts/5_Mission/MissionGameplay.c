modded class MissionGameplay {
    private ref TBZPlayerEventListener tbz_playerEventListener;
    PlayerBase tbmPlayerBase;

    override void OnInit() {
        super.OnInit();
        tbz_playerEventListener = new TBZPlayerEventListener;
    }

}
