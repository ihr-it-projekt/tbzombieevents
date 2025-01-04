modded class PlayerBase {
    private ref TBZMessageMenu tbz_messageMenu;

    void TBZDisplayMessage(string message) {
        TBZGetMessageMenu();
        tbz_messageMenu.SetText(message);
        SEffectManager.CreateSound("TBZ_Message_SoundSet", GetPosition()).SoundPlay();
        tbz_messageMenu.Init();
        tbz_messageMenu.Show();
    }

    TBZMessageMenu TBZGetMessageMenu() {
        tbz_messageMenu = new TBZMessageMenu();
        return tbz_messageMenu;
    }

    override bool CanBeTargetedByAI(EntityAI ai) {
        if(GetGame().IsServer()) {
            ZombieBase zoombi = ZombieBase.Cast(ai);
            if(zoombi && false == zoombi.CanAttackPlayer(GetPosition())) {
                return false;
            }
        }

        return super.CanBeTargetedByAI(ai);
    }
}
