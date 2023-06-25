class CfgPatches
{
	class TBZombieEvents
	{
		units[]={};
        weapons[]={};
        requiredVersion=1.0;
        requiredAddons[]={
            "DZ_Data",
            "DZ_Scripts"
        };
	};
};

class CfgAddons
{
	class PreloadBanks {};
	class PreloadAddons
	{
		class dayz
		{
			list[] ={};
		};
	};
};

class CfgMods
{
	class TBZombieEvents
	{
	    dir = "TBZombieEvents";
        picture = "";
        action = "";
        hideName = 0;
		name = "TBZombieEvents";
		credits = "TheBuster";
		author = "TheBuster";
		authorID = "76561198196317725";
		version = "1.0.0";
		extra = 0;
		type = "mod";
		
		dependencies[] = {"Game", "World", "Mission"};

		class defs
		{
            class gameScriptModule
            {
                value="";
                files[]=
                {
                    "TBZombieEvents/scripts/3_Game"
                };
            };
            class worldScriptModule
            {
                value="";
                files[]=
                {
                    "TBZombieEvents/scripts/4_World"
                };
                obfuscated=1;
            };
			class missionScriptModule
			{
				value = "";
				files[] = {
				        "TBZombieEvents/scripts/5_Mission"
				};
			};
		};
	};
};
