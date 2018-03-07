/**
* ScriptData
* SDName:      npc_teleport
* SD%Complete: 100
* SDComment:世界传送
* EndScriptData
**/

#include "AI/ScriptDevAI/include/precompiled.h"

bool GossipHello_npc_teleport(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->getRace() == 1 || pPlayer->getRace() == 3 || pPlayer->getRace() == 4 || pPlayer->getRace() == 7 || pPlayer->getRace() == 11)//判断是否联盟
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Spell_Arcane_TeleportStormWind:28|t 主城-暴风城　  ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Spell_Arcane_TeleportIronForge:28|t 主城-铁炉堡　  ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Spell_Arcane_TeleportDarnassus:28|t 主城-达纳苏斯  ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Spell_Arcane_TeleportExodar:28|t 主城-埃索达　  ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    }
    else
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Spell_Arcane_TeleportOrgrimmar:28|t 主城-奥格瑞玛  ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Spell_Arcane_TeleportThunderBluff:28|t 主城-雷霆崖　  ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Spell_Arcane_TeleportUnderCity:28|t 主城-幽暗城　  ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Spell_Arcane_TeleportSilvermoon:28|t 主城-银月城　  ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    }

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Spell_Arcane_TeleportShattrath:28|t 中立-沙斯塔城　  ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Spell_Arcane_TeleportMoonglade:28|t 中立-黑暗之门　  ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
    pPlayer->SEND_GOSSIP_MENU(99999, pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_teleport(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
    if (!pPlayer)
        return true;

    pPlayer->PlayerTalkClass->ClearMenus();

    switch (uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:   // 暴风城 统一格式说明：(MapID, X, Y, Z, 0);
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(0, -8831.41f, 625.35f, 93.92f, 0.0f);
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 2:   // 铁炉堡
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(0, -4923.08f, -952.88f, 501.53f, 0.0f);
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 3:  // 达纳苏斯
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(1, 9952.12f, 2280.47f, 1341.39f, 0.0f);
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 4:   // 埃索达
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(530, -4074.264f, -12017.234f, -1.376f, 1.331f);
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 5:   // 奥格瑞玛
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(1, 1605.77f, -4388.93f, 10.0f, 0.0f);
            break;
        }  
        case GOSSIP_ACTION_INFO_DEF + 6:   // 雷霆崖
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(1, -1277.57f, 123.413f, 131.265f, 0.0f);
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 7:  // 幽暗城
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(0, 1633.3f, 240.18f, -43.1f, 0.0f);
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 8:   // 银月城
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(530, 9336.9f, -7278.399f, 13.608f, 4.06f);
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 13:  //沙斯塔城
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(530, -1820.317f, 5312.883f, -12.427f, 1.972f);
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 14: //黑暗之门
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(530, -248.258f, 921.199f, 84.021f, 1.555f);
            break;
        }
    }
    return true;
}

void AddSC_teleport()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_teleport";
    pNewScript->pGossipHello = &GossipHello_npc_teleport;
    pNewScript->pGossipSelect = &GossipSelect_npc_teleport;
    pNewScript->RegisterSelf(false);
}