class TBZPlayerEventListener
{
    private PlayerBase player;

    void TBZPlayerEventListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsTBZ);
    }

    void ~TBZPlayerEventListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsTBZ);
    }

    void HandleEventsTBZ(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        player = TBZPlayerBaseHelper.GetPlayer();
        if (player) {
            if (rpc_type == TB_ZOMBIE_EVENT_RECEIVE_MESSAGE) {
                Param1 <string> tbmMessage;
                if (ctx.Read(tbmMessage) && tbmMessage.param1){
                    player.TBZDisplayMessage(tbmMessage.param1);
                }
            }
        }
    }
}
