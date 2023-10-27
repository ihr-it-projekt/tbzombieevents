static bool IsServerZombieEvent() {
    return GetGame().IsServer();
}

static string GetItemDisplayName(string itemClassname){
    string cfg = "CfgVehicles " + itemClassname + " displayName";
    string displayName;
    GetGame().ConfigGetText(cfg, displayName);

    if (displayName == ""){
        cfg = "CfgAmmo " + itemClassname + " displayName";
        GetGame().ConfigGetText(cfg, displayName);
    }

    if (displayName == "") {
        cfg = "CfgMagazines " + itemClassname + " displayName";
        GetGame().ConfigGetText(cfg, displayName);
    }

    if (displayName == "") {
        cfg = "cfgWeapons " + itemClassname + " displayName";
        GetGame().ConfigGetText(cfg, displayName);
    }

    if (displayName == "") {
        cfg = "CfgNonAIVehicles " + itemClassname + " displayName";
        GetGame().ConfigGetText(cfg, displayName);
    }

    if (displayName != "") {
        displayName.Replace("$UNT$", "");
		return displayName;
    }

    return itemClassname;
}
