static void SendMessageToPlayerZombieEvent(string message, DayZPlayer player) {
    if (player) {
        GetGame().RPCSingleParam(null, TB_ZOMBIE_EVENT_RECEIVE_MESSAGE, new Param1<string>(message), true, player.GetIdentity());
    } else {
        array<Man> _players = new array<Man>;
        GetGame().GetPlayers(_players);
        if (_players) {
            foreach(Man _player: _players) {
                if (_player) {
                    GetGame().RPCSingleParam(_player, TB_ZOMBIE_EVENT_RECEIVE_MESSAGE, new Param1<string>(message), true, _player.GetIdentity());
                }
            }
        }
    }
}


