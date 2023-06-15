class TBZPlayerBaseHelper {
    static PlayerBase GetPlayer() {
		return PlayerBase.Cast(GetGame().GetPlayer());
	}
}