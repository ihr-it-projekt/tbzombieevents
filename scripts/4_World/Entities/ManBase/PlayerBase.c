modded class PlayerBase
{
    private ref TBZMessageMenu messageMenu;

    void TBZDisplayMessage(string message) {
        GetMessageMenu();
        messageMenu.SetText(message);
        SEffectManager.CreateSound("TBZ_Message_SoundSet", GetPosition()).SoundPlay();
        messageMenu.Init();
        messageMenu.Show();
    }

	TBZMessageMenu GetMessageMenu() {
		messageMenu = new TBZMessageMenu();
		return messageMenu;
	}

	override bool CanBeTargetedByAI(EntityAI ai)
    {
        if (GetGame().IsServer()) {
			ZombieBase zoombi = ZombieBase.Cast(ai);
            if (zoombi && false == zoombi.CanAttackPlayer(GetPosition())) {
                return false;
            }
        }

        return super.CanBeTargetedByAI(ai);
    }
}
