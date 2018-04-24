/**
* ScriptData
* SDName:      npc_custom_box
* SD%Complete: 100
* SDComment:自定义功能
* EndScriptData
**/

#include "AI/ScriptDevAI/include/precompiled.h"
#include "Chat/Chat.h"

#define SETSKILL_MAXVAL           375          //商业技能最大值(ZERO 300  TBC 375)
#define SETSKILL_ITEM_VALUE_1     50           //增加技能最大值需要的物品数量1
#define SETSKILL_ITEM_VALUE_2     100          //增加技能最大值需要的物品数量2
#define SET_ITEM_ID               90000        //兑换物品ID  1积分等于 1个兑换物品

/*####################
## npc_tool
######################*/

bool GossipHello_npc_tool(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\INV_Misc_Coin_04:28|t |cFF0041FF积分查询|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\INV_Misc_Coin_02:28|t |cFF0041FF兑换积分|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "|TInterface\\Icons\\INV_Misc_Rune_01:28|t |cFF0041FF绑定炉石|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3, "你是否需要绑定回城点？　 ", 0, false);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\INV_Misc_Coin_01:28|t |cFF0041FF游戏商店|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cFF0041FF我要秒专业|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);

    if (pPlayer->IsDualSpecArrive())  //如果开通了双天赋包月就显示续费操作
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cFFFF6600[已开通]|r|cFF0041FF开启双天赋包月服务（查看信息）|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    else
        pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "|cFFFF6600[30积分]|r|cFF0041FF开启双天赋页包月（30天）|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8, "你是否需要开通包月双天赋？　 ", 0, false);

    if (pPlayer->IsFlyInstantArrive())  //如果开通了瞬飞包月就显示续费操作
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cFFFF6600[已开通]|r|cFF0041FF开启瞬飞包月服务（查看信息）|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    else
        pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "|cFFFF6600[20积分]|r|cFF0041FF开启瞬飞包月（30天）|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10, "你是否需要开通包月瞬飞？　 ", 0, false);

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cFFFF6600[功　能]|cFF0041FF角色服务 |r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
    
    pPlayer->SEND_GOSSIP_MENU(999999, pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_tool(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
    if (!pPlayer)
        return true;

    pPlayer->PlayerTalkClass->ClearMenus();

    switch (uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
        {
            pPlayer->GetSession()->SendNotification("|cFFFFFF33你当前帐户积分：|r|cFF33FF00%u|r ", pPlayer->Getjifen());
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 2:  //兑换货币
        {
            pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "|cFF0041FF兑换1个积分|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100, "你是否需要兑换积分货币？　 ", 0, false);
            pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "|cFF0041FF兑换10个积分|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 101, "你是否需要兑换积分货币？　 ", 0, false);
            pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "|cFF0041FF兑换100个积分|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 102, "你是否需要兑换积分货币？　 ", 0, false);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cFFCC00CC注意：兑换的时候至少需要四个背包格子，出现损失概不负责，兑换比例一比一。|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 999);
            pPlayer->SEND_GOSSIP_MENU(999999, pCreature->GetObjectGuid());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 3: //绑定炉石
        {
            pPlayer->GetSession()->SendBindPoint(pCreature);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 4: //商店
        {
            pPlayer->SEND_VENDORLIST(pCreature->GetObjectGuid());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 5: //秒升专业
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\INV_Misc_Gem_01:28|t |cFFFF6600[100积分]|r|cFF0041FF珠宝加工等级加满|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 199);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Trade_Alchemy:28|t |cFFFF6600[100积分]|r|cFF0041FF炼金等级加满|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 200);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Trade_BlackSmithing:28|t |cFFFF6600[100积分]|r|cFF0041FF锻造等级加满|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 201);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Trade_Tailoring:28|t |cFFFF6600[100积分]|r|cFF0041FF裁缝等级加满|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 202);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Trade_Engineering:28|t |cFFFF6600[100积分]|r|cFF0041FF工程等级加满|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 203);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Trade_LeatherWorking:28|t |cFFFF6600[100积分]|r|cFF0041FF制皮等级加满|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 204);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Trade_Engraving:28|t |cFFFF6600[100积分]|r|cFF0041FF附魔等级加满|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 205);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Trade_Fishing:28|t |cFFFF6600[50积分]|r|cFF0041FF钓鱼等级加满|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 206);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\INV_Misc_Food_15:28|t |cFFFF6600[50积分]|r|cFF0041FF烹饪等级加满|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 207);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Trade_Mining:28|t |cFFFF6600[50积分]|r|cFF0041FF采矿等级加满|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 208);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Trade_Herbalism:28|t |cFFFF6600[50积分]|r|cFF0041FF草药等级加满|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 209);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\INV_Misc_Pelt_Wolf_01:28|t |cFFFF6600[50积分]|r|cFF0041FF剥皮等级加满|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 210);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\Icons\\Spell_Holy_SealOfSacrifice:28|t |cFFFF6600[50积分]|r|cFF0041FF急救等级加满|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 211);
            pPlayer->SEND_GOSSIP_MENU(999999, pCreature->GetObjectGuid());
            break;
        }

        case GOSSIP_ACTION_INFO_DEF + 8: //双天赋包月
        {
            if (pPlayer->HasItemCount(SET_ITEM_ID, 30)) // 判断物品是否足够.
            {
                if (pPlayer->GetSpecsCount() < MAX_TALENT_SPECS)   //判断是否已经激活双天赋 已经激活的就不需要再执行
                    pPlayer->SetSpecsCount(pPlayer->GetSpecsCount() + 1);

                pPlayer->DestroyItemCount(SET_ITEM_ID, 30, true);  //销毁用户背包里面的物品
                pPlayer->SetDualSpecArriveDate(2592000); //30天
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->GetSession()->SendNotification("|cFFFFFF33双天赋包月服务开通成功！|r ");
            }
            else
            {
                pPlayer->GetSession()->SendNotification("你的物品不足，无法开通双天赋包月功能！　 ");
                pPlayer->CLOSE_GOSSIP_MENU();
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 9: //双天赋包月
        {
            std::string last_date = "已到期 ";
            QueryResult* result = CharacterDatabase.PQuery("SELECT guid, talent_last_date FROM characters_limited WHERE guid = '%u' AND talent_last_date >= NOW()", pPlayer->GetGUIDLow());
            if (result)
            {
                Field* fields = result->Fetch();
                last_date = fields[1].GetString(); //得到数据库时间
                delete result;
            }
 
            std::string sDate = "|cFFCC00CC到期时间: ";
            sDate += last_date;
            sDate += "|r　 ";
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, sDate, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 999);
            pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "|cFFFF6600[30积分]|r|cFF0041FF延长双天赋包月三十天|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 301, "你是否需要延长包月双天赋？　 ", 0, false);
            pPlayer->SEND_GOSSIP_MENU(999999, pCreature->GetObjectGuid());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 10: //瞬飞包月
        {
            if (pPlayer->HasItemCount(SET_ITEM_ID, 20)) // 判断物品是否足够.
            {
                pPlayer->DestroyItemCount(SET_ITEM_ID, 20, true);  //销毁用户背包里面的物品
                pPlayer->SetFlyInstantArriveDate(2592000); //30天
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->GetSession()->SendNotification("|cFFFFFF33瞬飞包月服务开通成功！|r ");
            }
            else
            {
                pPlayer->GetSession()->SendNotification("你的物品不足，无法开通瞬飞包月功能！ ");
                pPlayer->CLOSE_GOSSIP_MENU();
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 11: //瞬飞包月续费与到期时间
        {
            std::string last_date = "已到期 ";
            QueryResult* result = CharacterDatabase.PQuery("SELECT guid, fly_last_date FROM characters_limited WHERE guid = '%u' AND fly_last_date >= NOW()", pPlayer->GetGUIDLow());
            if (result)
            {
                Field* fields = result->Fetch();
                last_date = fields[1].GetString(); //得到数据库时间
                delete result;
            }

            std::string sDate = "|cFFCC00CC到期时间: ";
            sDate += last_date;
            sDate += "|r　 ";
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, sDate, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 999);
            pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "|cFFFF6600[20积分]|r|cFF0041FF延长瞬飞包月三十天|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 300, "你是否需要延长包月瞬飞？　 ", 0, false);
            pPlayer->SEND_GOSSIP_MENU(999999, pCreature->GetObjectGuid());
            break;
        }

        case GOSSIP_ACTION_INFO_DEF + 12: //增强功能
        {
            pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "|cFFFF6600[50积分]|r|cFF0041FF修改角色名称|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 400, "你是否需要修改角色名称？　 ", 0, false);
            pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "|cFFFF6600[免　费]|r|cFF0041FF武器技能全满|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 401, "你是否需要升级武器技能？　 ", 0, false);
            pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, "|cFFFF6600[2 积分]|r|cFF0041FF人物等级提升一级|r　 ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 402, "你是否需要提升等级？　 ", 0, false);
            pPlayer->SEND_GOSSIP_MENU(999999, pCreature->GetObjectGuid());
            break;
        }

        ////////////////////////////////////////////////////  兑换开始  //////////////////////////////////////////////////////////////////
        case GOSSIP_ACTION_INFO_DEF + 100:
        {
            if (pPlayer->Getjifen() >= 1)
            {
                pPlayer->AddItem(SET_ITEM_ID, 1);
                pPlayer->Modifyjifen(-(int32)1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->GetSession()->SendNotification("|cFFFFFF33你当前帐户积分：|r|cFF33FF00%d|r ", pPlayer->Getjifen());
            }
            else
            {
                pPlayer->GetSession()->SendNotification("你的积分不足，无法兑换物品！ ");
                pPlayer->CLOSE_GOSSIP_MENU();
            }
            break;
        }

        case GOSSIP_ACTION_INFO_DEF + 101:
        {
            if (pPlayer->Getjifen() >= 10)
            {
                pPlayer->AddItem(SET_ITEM_ID, 10);
                pPlayer->Modifyjifen(-(int32)10);
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->GetSession()->SendNotification("|cFFFFFF33你当前帐户积分：|r|cFF33FF00%d|r ", pPlayer->Getjifen());
            }
            else
            {
                pPlayer->GetSession()->SendNotification("你的积分不足，无法兑换物品！ ");
                pPlayer->CLOSE_GOSSIP_MENU();
            }
            break;
        }

        case GOSSIP_ACTION_INFO_DEF + 102:
        {
            if (pPlayer->Getjifen() >= 100)
            {
                pPlayer->AddItem(SET_ITEM_ID, 100);
                pPlayer->Modifyjifen(-(int32)100);
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->GetSession()->SendNotification("|cFFFFFF33你当前帐户积分：|r|cFF33FF00%d|r ", pPlayer->Getjifen());
            }
            else
            {
                pPlayer->GetSession()->SendNotification("你的积分不足，无法兑换物品！ ");
                pPlayer->CLOSE_GOSSIP_MENU();
            }
            break;
        }

        ////////////////////////////////////////////////////  兑换结束  //////////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////秒升专业开始//////////////////////////////////////////////////////////////////
        case GOSSIP_ACTION_INFO_DEF + 199:
        case GOSSIP_ACTION_INFO_DEF + 200:
        case GOSSIP_ACTION_INFO_DEF + 201:
        case GOSSIP_ACTION_INFO_DEF + 202:
        case GOSSIP_ACTION_INFO_DEF + 203:
        case GOSSIP_ACTION_INFO_DEF + 204:
        case GOSSIP_ACTION_INFO_DEF + 205:
        case GOSSIP_ACTION_INFO_DEF + 206:
        case GOSSIP_ACTION_INFO_DEF + 207:
        case GOSSIP_ACTION_INFO_DEF + 208:
        case GOSSIP_ACTION_INFO_DEF + 209:
        case GOSSIP_ACTION_INFO_DEF + 210:
        case GOSSIP_ACTION_INFO_DEF + 211://专业  
        {
            uint32 Item_Value = 0;   //物品数量
            uint32 Skill_Type = 0;   //技能类型

            switch (uiAction)
            {
                case GOSSIP_ACTION_INFO_DEF + 199:   //珠宝加工 755
                {
                    Item_Value = SETSKILL_ITEM_VALUE_2;
                    Skill_Type = SKILL_JEWELCRAFTING;
                    break;
                }
                case GOSSIP_ACTION_INFO_DEF + 200:  //炼金171
                {
                    Item_Value = SETSKILL_ITEM_VALUE_2;
                    Skill_Type = SKILL_ALCHEMY;
                    break;
                }
                case GOSSIP_ACTION_INFO_DEF + 201:  //锻造164
                {
                    Item_Value = SETSKILL_ITEM_VALUE_2;
                    Skill_Type = SKILL_BLACKSMITHING;
                    break;
                }
                case GOSSIP_ACTION_INFO_DEF + 202:  //裁缝197
                {
                    Item_Value = SETSKILL_ITEM_VALUE_2;
                    Skill_Type = SKILL_TAILORING;
                    break;					
                }
                case GOSSIP_ACTION_INFO_DEF + 203:  //工程学202
                {
                    Item_Value = SETSKILL_ITEM_VALUE_2;
                    Skill_Type = SKILL_ENGINEERING;
                    break;
                }
                case GOSSIP_ACTION_INFO_DEF + 204:  //制皮165
                {
                    Item_Value = SETSKILL_ITEM_VALUE_2;
                    Skill_Type = SKILL_LEATHERWORKING;
                    break;
                }
                case GOSSIP_ACTION_INFO_DEF + 205:  //附魔333
                {
                    Item_Value = SETSKILL_ITEM_VALUE_2;
                    Skill_Type = SKILL_ENCHANTING;
                    break;
                }
                case GOSSIP_ACTION_INFO_DEF + 206:  //钓鱼
                {
                    Item_Value = SETSKILL_ITEM_VALUE_1; 
                    Skill_Type = SKILL_FISHING;
                    break;
                }
                case GOSSIP_ACTION_INFO_DEF + 207:  //烹饪
                {
                    Item_Value = SETSKILL_ITEM_VALUE_1;
                    Skill_Type = SKILL_COOKING;
                    break;
                }
                case GOSSIP_ACTION_INFO_DEF + 208:  //采矿
                {
                    Item_Value = SETSKILL_ITEM_VALUE_1;
                    Skill_Type = SKILL_MINING;
                    break;
                }
                case GOSSIP_ACTION_INFO_DEF + 209:  //草药
                {
                    Item_Value = SETSKILL_ITEM_VALUE_1; 
                    Skill_Type = SKILL_HERBALISM;
                    break;
                }
                case GOSSIP_ACTION_INFO_DEF + 210:  //剥皮
                {
                    Item_Value = SETSKILL_ITEM_VALUE_1;
                    Skill_Type = SKILL_SKINNING;
                    break;
                }
                case GOSSIP_ACTION_INFO_DEF + 211:  //急救
                {
                    Item_Value = SETSKILL_ITEM_VALUE_1;
                    Skill_Type = SKILL_FIRST_AID;
                    break;
                }
            }

            if (pPlayer->HasSkill(Skill_Type))
            {
                if (pPlayer->HasItemCount(SET_ITEM_ID, Item_Value) && pPlayer->GetBaseSkillValue(Skill_Type) < SETSKILL_MAXVAL)
                {
                    pPlayer->DestroyItemCount(SET_ITEM_ID, Item_Value, true);  //销毁用户背包里面的物品
                    pPlayer->SetSkill(Skill_Type, SETSKILL_MAXVAL, SETSKILL_MAXVAL);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
                else
                {
                    //pPlayer->GetSession()->SendNotification("你的物品不足，或者你的技能值已到最大值！技能提升失败.　 ");
                    pCreature->MonsterWhisper("|cFFFF00FF你的物品不足，或者你的技能值已到最大值！技能提升失败。|r　 ", pPlayer);   //NPC 密语发送消息
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
                    
            }
            else
            {
                //pPlayer->GetSession()->SendNotification("你没有学习技能，请学习技能后再来!　 ");
                pCreature->MonsterWhisper("|cFFFF00FF你没有学习技能，请学习技能后再来！|r　 ", pPlayer);   //NPC 密语发送消息
                pPlayer->CLOSE_GOSSIP_MENU();
            }
            break;
        }
        ////////////////////////////////////////////////////秒升专业结束//////////////////////////////////////////////////////////////////
        case GOSSIP_ACTION_INFO_DEF + 300: //瞬飞延长时间
        {
            if (pPlayer->HasItemCount(SET_ITEM_ID, 20)) // 判断物品是否足够.
            {
                pPlayer->DestroyItemCount(SET_ITEM_ID, 20, true); //销毁用户背包里面的物品
                pPlayer->SetFlyInstantArriveDate(2592000);//30天
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->GetSession()->SendNotification("|cFFFFFF33延长瞬飞包月服务时间成功！|r ");
            }
            else
            {

                pPlayer->GetSession()->SendNotification("你的物品不足，无法延长瞬飞包月时间！ ");
                pPlayer->CLOSE_GOSSIP_MENU();
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 301: //双天赋延长时间
        {
            if (pPlayer->HasItemCount(SET_ITEM_ID, 30)) // 判断物品是否足够.
            {
                pPlayer->DestroyItemCount(SET_ITEM_ID, 30, true); //销毁用户背包里面的物品
                pPlayer->SetDualSpecArriveDate(2592000);//30天
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->GetSession()->SendNotification("|cFFFFFF33延长双天赋包月服务时间成功！|r ");
            }
            else
            {

                pPlayer->GetSession()->SendNotification("你的物品不足，无法延长双天赋包月时间！ ");
                pPlayer->CLOSE_GOSSIP_MENU();
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 400: //修改名称
        {
            if (pPlayer->HasItemCount(SET_ITEM_ID, 50)) // 判断物品是否足够.
            {
                pPlayer->DestroyItemCount(SET_ITEM_ID, 50, true);  //销毁用户背包里面的物品
                pPlayer->SetAtLoginFlag(AT_LOGIN_RENAME);    //修改名字
                pPlayer->GetSession()->SendNotification("你需要重新登录，然后才能修改角色的名字！ ");
                pPlayer->CLOSE_GOSSIP_MENU();
            }
            else
            {
                pPlayer->GetSession()->SendNotification("你的物品不足，无法修改角色名称！ ");
                pPlayer->CLOSE_GOSSIP_MENU();
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 401: //武器技能全满
        {
            pPlayer->UpdateSkillsToMaxSkillsForLevel();
            pPlayer->GetSession()->SendNotification("恭喜你，所有武器技能已经提升到最大值！ ");
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 402: //人物升级
        {
            if (pPlayer->HasItemCount(SET_ITEM_ID, 2))
            {
                if (pPlayer->getLevel() == DEFAULT_MAX_LEVEL)
                {
                    pPlayer->GetSession()->SendNotification("你已最高等级，提升失败！ ");
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
                else
                {
                    pPlayer->DestroyItemCount(SET_ITEM_ID, 2, true);
                    pPlayer->GiveLevel(pPlayer->getLevel() + 1);
                    pPlayer->GetSession()->SendNotification("恭喜你，等级提升成功了！ ");
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
            }
            else
            {
                pPlayer->GetSession()->SendNotification("你的物品不足，无法提升角色等级！ ");
                pPlayer->CLOSE_GOSSIP_MENU();
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 999:
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        }
    }
    return true;
}

/*####################
## npc_training_dummy     //训练假人
######################*/

#define OUT_OF_COMBAT_TIME 5000

struct npc_training_dummyAI : public ScriptedAI
{
    npc_training_dummyAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 combat_timer;

    void Reset() override
    {
        combat_timer = 0;
    }

    void DamageTaken(Unit* pDoneby, uint32& uiDamage, DamageEffectType /*damagetype*/) override
    {
        combat_timer = 0;
    }

    void UpdateAI(const uint32 diff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        m_creature->ModifyHealth(m_creature->GetMaxHealth());

        combat_timer += diff;
        if (combat_timer > OUT_OF_COMBAT_TIME)
            EnterEvadeMode();
    }
};

CreatureAI* GetAI_npc_training_dummy(Creature* pCreature)
{
    return new npc_training_dummyAI(pCreature);
}

void AddSC_npc_custom_box()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_tool";
    pNewScript->pGossipHello = &GossipHello_npc_tool;
    pNewScript->pGossipSelect = &GossipSelect_npc_tool;
    pNewScript->RegisterSelf(false);

    pNewScript = new Script;
    pNewScript->Name = "npc_training_dummy";
    pNewScript->GetAI = &GetAI_npc_training_dummy;
    pNewScript->RegisterSelf(false);

}