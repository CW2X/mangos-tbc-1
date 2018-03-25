/**
* ScriptData
* SDName:      item_custom_box
* SD%Complete: 100
* SDComment:自定义功能
* EndScriptData
**/

#include "AI/ScriptDevAI/include/precompiled.h"


/*####################
## item_custom_dualspec
######################*/

bool GossipItemUse_custom_dualspec(Player* pPlayer, Item* pItem, const SpellCastTargets& /*pTargets*/)
{

    if (pPlayer->isInCombat())  //是否战斗
    {
        pPlayer->GetSession()->SendNotification("你当前处于战斗状态，暂时无法使用！ ");
        return false;
    }

    if (pPlayer->IsFlying() || pPlayer->IsTaxiFlying() || pPlayer->IsMounted())   //是否骑乘
    {
        pPlayer->GetSession()->SendNotification("你当前处于骑乘状态，暂时无法使用！ ");
        return false;
    }

    if (pPlayer->isDead())    //是否死亡
    {
        pPlayer->GetSession()->SendNotification("你已死亡，暂时无法使用！ ");
        return false;
    }

    if (pPlayer->GetSpecsCount() < MAX_TALENT_SPECS || !(pPlayer->IsDualSpecArrive()))
    {
        pPlayer->GetSession()->SendNotification("你未激活双天赋功能，暂时无法使用！ ");
        return false;
    }

    if (pPlayer->getLevel() < 10) //10级才有天赋点
    {
        pPlayer->GetSession()->SendNotification("你当前等级小于十级，暂时无法使用！ ");
        return false;
    }

    
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface\\Icons\\Mail_GMIcon:28|t |cffCD6889官方网站: www.243wow.com|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 999);

    uint8 specCount = pPlayer->GetSpecsCount();
    for (uint8 i = 0; i < specCount; ++i)
    {
        std::stringstream specNameString;
        specNameString << "|cFF0041FF[天赋页] ";
        if (pPlayer->GetSpecName(i) == "NULL")
            specNameString << " [未命名] ";
        else
            specNameString << pPlayer->GetSpecName(i);
        if (i == pPlayer->GetActiveSpec())
            specNameString << " 〖当前激活〗　 ";
        else
            specNameString << "";

        specNameString << "|r";

 
        pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, specNameString.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + (1 + i), "你是否需要切换双天赋？　 ", 0, false);
    }

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|cFF00CC99※〓〓〓〓双天赋功能已经开启〓〓〓〓※|r 　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 999);

    for (uint8 i = 0; i < specCount; ++i)
    {
        std::stringstream specNameString;
        specNameString << "|cFFCC00CC[天赋名称] ";
        if (pPlayer->GetSpecName(i) == "NULL")
            specNameString << "[未命名]";
        else
            specNameString << pPlayer->GetSpecName(i);

        specNameString << "|r";

        pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, specNameString.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + (10 + i), "", 0, true);
    }

    pPlayer->SEND_GOSSIP_MENU(999999, pItem->GetObjectGuid());
    return true;
}

bool GossipSelectItem_custom_dualspec(Player* pPlayer, Item* pItem, uint32 sender, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
        {
            pPlayer->ActivateSpec(0);
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 2:
        {
            pPlayer->ActivateSpec(1);
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 999:
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        }
        default:
            break;
    }

    return true;
}

bool GossipSelectItemWithCode_custom_dualspec(Player* pPlayer, Item* pItem, uint32 sender, uint32 action, const char* sCode)
{
    if (action == GOSSIP_ACTION_INFO_DEF + 10)
        pPlayer->SetSpecName(0, sCode);
    else if (action == GOSSIP_ACTION_INFO_DEF + 11)
        pPlayer->SetSpecName(1, sCode);

    pPlayer->CLOSE_GOSSIP_MENU();
    return true;
}

/*####################
## item_xp_rate0
######################*/
bool GossipItemUse_xp_rate0(Player* pPlayer, Item* pItem, const SpellCastTargets& /*pTargets*/)
{
    if(!pPlayer)
        return false;

    pPlayer->SetBonusxp(0.5f, 7200);
    pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true, false);
    pPlayer->GetSession()->SendNotification("|cFFFFFF33恭喜你，经验获取提高 50％持续时间两小时！|r ");
    return true;
}

/*####################
## item_xp_rate1
######################*/
bool GossipItemUse_xp_rate1(Player* pPlayer, Item* pItem, const SpellCastTargets& /*pTargets*/)
{
    if (!pPlayer)
        return false;

    pPlayer->SetBonusxp(1.0f, 7200);
    pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true, false);
    pPlayer->GetSession()->SendNotification("|cFFFFFF33恭喜你，经验获取提高100％持续时间两小时！|r ");
    return true;
}

/*####################
## item_xp_rate2
######################*/
bool GossipItemUse_xp_rate2(Player* pPlayer, Item* pItem, const SpellCastTargets& /*pTargets*/)
{
    if (!pPlayer)
        return false;

    pPlayer->SetBonusxp(1.5f, 7200);
    pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true, false);
    pPlayer->GetSession()->SendNotification("|cFFFFFF33恭喜你，经验获取提高150％持续时间两小时！|r ");
    return true;
}

/*####################
## item_Reputation_rate0
######################*/
bool GossipItemUse_Reputation_rate0(Player* pPlayer, Item* pItem, const SpellCastTargets& /*pTargets*/)
{
    if (!pPlayer)
        return false;

    pPlayer->SetBonusReputation(0.5f, 7200);
    pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true, false);
    pPlayer->GetSession()->SendNotification("|cFFFFFF33恭喜你，声望获取提高 50％持续时间两小时！|r ");
    return true;
}

/*####################
## item_Reputation_rate1
######################*/
bool GossipItemUse_Reputation_rate1(Player* pPlayer, Item* pItem, const SpellCastTargets& /*pTargets*/)
{
    if (!pPlayer)
        return false;

    pPlayer->SetBonusReputation(1.0f, 7200);
    pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true, false);
    pPlayer->GetSession()->SendNotification("|cFFFFFF33恭喜你，声望获取提高100％持续时间两小时！|r ");
    return true;
}

/*####################
## item_Reputation_rate2
######################*/
bool GossipItemUse_Reputation_rate2(Player* pPlayer, Item* pItem, const SpellCastTargets& /*pTargets*/)
{
    if (!pPlayer)
        return false;

    pPlayer->SetBonusReputation(1.5f, 7200);
    pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true, false);
    pPlayer->GetSession()->SendNotification("|cFFFFFF33恭喜你，声望获取提高 150％持续时间两小时！|r ");
    return true;
}

void AddSC_item_custom_box()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "item_custom_dualspec";
    pNewScript->pItemUse = &GossipItemUse_custom_dualspec;
    pNewScript->pGossipSelectItem = &GossipSelectItem_custom_dualspec;
    pNewScript->pGossipSelectItemWithCode = &GossipSelectItemWithCode_custom_dualspec;
    pNewScript->RegisterSelf(false);

    pNewScript = new Script;
    pNewScript->Name = "item_xp_rate0";
    pNewScript->pItemUse = &GossipItemUse_xp_rate0;
    pNewScript->RegisterSelf(false);

    pNewScript = new Script;
    pNewScript->Name = "item_xp_rate1";
    pNewScript->pItemUse = &GossipItemUse_xp_rate1;
    pNewScript->RegisterSelf(false);

    pNewScript = new Script;
    pNewScript->Name = "item_xp_rate2";
    pNewScript->pItemUse = &GossipItemUse_xp_rate2;
    pNewScript->RegisterSelf(false);

    pNewScript = new Script;
    pNewScript->Name = "item_Reputation_rate0";
    pNewScript->pItemUse = &GossipItemUse_Reputation_rate0;
    pNewScript->RegisterSelf(false);

    pNewScript = new Script;
    pNewScript->Name = "item_Reputation_rate1";
    pNewScript->pItemUse = &GossipItemUse_Reputation_rate1;
    pNewScript->RegisterSelf(false);

    pNewScript = new Script;
    pNewScript->Name = "item_Reputation_rate2";
    pNewScript->pItemUse = &GossipItemUse_Reputation_rate2;
    pNewScript->RegisterSelf(false);
}