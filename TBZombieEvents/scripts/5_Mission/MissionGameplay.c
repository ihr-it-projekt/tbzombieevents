modded class MissionGameplay
{
	private ref TBZPlayerEventListener playerEventListener;
   	PlayerBase tbmPlayerBase;

	override void OnInit() {
		super.OnInit();
		playerEventListener = new TBZPlayerEventListener;
	}

 }
