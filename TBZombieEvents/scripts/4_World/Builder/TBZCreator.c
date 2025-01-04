class TBZCreator {
    static DayZCreatureAI SpawnCreature(vector pos, string gameObjectName) {
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
        DayZCreatureAI game_obj = DayZCreatureAI.Cast(GetGame().CreateObject(gameObjectName, pos, false, true));
        if(!game_obj) {
            return game_obj;
        }
        game_obj.SetPosition(pos);
        game_obj.SetOrientation("0 0 0");
        game_obj.SetOrientation(game_obj.GetOrientation()); //Collision fix
        game_obj.Update();
        game_obj.SetAffectPathgraph(true, false);
        if(game_obj.CanAffectPathgraph()) {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, game_obj);
        }

        return game_obj;
    }

    static ItemBase SpawnItem(vector pos, TBZItem item) {
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
        ItemBase game_obj = ItemBase.Cast(GetGame().CreateObject(item.type, pos));
        if(!game_obj) {
            return game_obj;
        }
        game_obj.SetOrientation("0 0 0");
        game_obj.SetOrientation(game_obj.GetOrientation()); //Collision fix
        game_obj.Update();
        game_obj.SetAffectPathgraph(true, false);
        if(game_obj.CanAffectPathgraph()) {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, game_obj);
        }

        TBZCreator.AddAttachments(item, game_obj);

        return game_obj;
    }

    private static void AddAttachments(TBZItem type, EntityAI item) {
        if(!item) return;
        if(!type.attachments) return;

        foreach(TBZItem attachment: type.attachments) {
            if(item.GetInventory()) {
                EntityAI itemAttachment = item.GetInventory().CreateInInventory(attachment.type);

                if(!itemAttachment) {
                    itemAttachment = item.GetInventory().CreateEntityInCargo(attachment.type);
                    if(!itemAttachment) {
                        itemAttachment = item.GetInventory().CreateAttachment(attachment.type);
                    }
                }

                if(itemAttachment && attachment.attachments) {
                    TBZCreator.AddAttachments(attachment, itemAttachment);
                }
            }
        }
    }

    static Object Spawn(vector position, vector orientation, string gameObjectName) {
        Object house = GetGame().CreateObject(gameObjectName, position);
        if(!house) {
            return house;
        }
        house.SetPosition(position);
        house.SetOrientation(orientation);
        house.SetOrientation(house.GetOrientation()); //Collision fix
        house.Update();
        house.SetAffectPathgraph(true, false);
        if(house.CanAffectPathgraph()) {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, house);
        }

        return house;
    }
};