/**
* ScriptData
* SDName:      scripted_on_events
* SD%Complete: n/n
* SDComment:   Custom script hooks
* EndScriptData
**/

#include "AI/ScriptDevAI/include/precompiled.h"
#include "World/World.h"
#include <cstring>


const int ALLIANCE_TITLES[14] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
};

const int HORDE_TITLES[14] = {
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28
};

const int TIME_RANKS[14] = {
    1, 3, 6, 12, 24, 48, 72, 96, 120, 144, 168, 240, 480, 720
};

//击杀BOSS 数组
const int CREATURE_ENTRY[129] = {
    24664, 24560, 24744, 24723, 20912, 20886, 20885, 20870, 17977, 17980,
    17978, 17975, 17976, 19220, 19221, 19219, 17881, 17880, 17879, 18096,
    17862, 17848, 18708, 18732, 18667, 18731, 18473, 23035, 18472, 20303,
    18373, 18371, 18344, 18343, 18341, 17798, 17796, 17797, 17882, 17826,
    18105, 17770, 17942, 17991, 17941, 16808, 16809, 20923, 16807, 17377,
    17380, 17381, 17537, 17308, 17306, 16152, 16151, 15687, 16457, 17521,
    17533, 17534, 17535, 18168, 15688, 16524, 15689, 15690, 15691, 17225,
    23574, 23576, 23577, 23578, 24239, 23863, 17711, 18728, 18831, 19044,
    17257, 21215, 21875, 21216, 21212, 21213, 21214, 21217, 19622, 20060,
    20062, 20063, 20064, 18805, 19514, 19516, 17767, 17808, 17842, 17888,
    17968, 22856, 23418, 23419, 23420, 22841, 22871, 22887, 22898, 22947,
    22948, 23426, 22949, 22950, 22951, 22952, 22917, 24850, 24892, 24882,
    25038, 25165, 25166, 25741, 25840, 25315, 25740, 23872, 23682
};

//普通挑战卡 - 稀有坐骑 死亡军马 迅捷美酒节赛羊 大型美酒节科多兽 迅捷飞行扫帚 默认 美酒节赛羊
const int ITEM_ENTRY_PT[50] = {
    13335, 33977, 37828, 33182, 33976, 33976, 33976, 33976, 33976, 33976,
    33976, 33976, 33976, 33976, 33976, 33976, 33976, 33976, 33976, 33976,
    33976, 33976, 33976, 33976, 33976, 33976, 33976, 33976, 33976, 33976,
    33976, 33976, 33976, 33976, 33976, 33976, 33976, 33976, 33976, 33976,
    33976, 33976, 33976, 33976, 33976, 33976, 33976, 33976, 33976, 33976
};

//中级挑战卡 - 稀有坐骑 拉扎什迅猛龙 乌龟坐骑 迅捷祖利安猛虎 默认 雷矛军用坐骑
const int ITEM_ENTRY_ZJ[50] = {
    19872, 23720, 19902, 19030, 19030, 19030, 19030, 19030, 19030, 19030,
    19030, 19030, 19030, 19030, 19030, 19030, 19030, 19030, 19030, 19030,
    19030, 19030, 19030, 19030, 19030, 19030, 19030, 19030, 19030, 19030,
    19030, 19030, 19030, 19030, 19030, 19030, 19030, 19030, 19030, 19030,
    19030, 19030, 19030, 19030, 19030, 19030, 19030, 19030, 19030, 19030
};

//高级挑战卡 - 稀有坐骑 幽灵虎缰绳 迅捷幽灵虎缰绳 迅捷虚空幼龙 阿曼尼战熊 默认 霜狼嗥叫者的号角
const int ITEM_ENTRY_GJ[50] = {
    13335, 33224, 33225, 30609, 33809, 19029, 19029, 19029, 19029, 19029,
    19029, 19029, 19029, 19029, 19029, 19029, 19029, 19029, 19029, 19029,
    19029, 19029, 19029, 19029, 19029, 19029, 19029, 19029, 19029, 19029,
    19029, 19029, 19029, 19029, 19029, 19029, 19029, 19029, 19029, 19029,
    19029, 19029, 19029, 19029, 19029, 19029, 19029, 19029, 19029, 19029
};

//T2幻化挑战卡
const int ITEM_TC_T2[56] = {
    92000, 92001, 92002, 92003, 92004, 92005, 92006, 92007, 92008, 92009,
    92010, 92011, 92012, 92013, 92014, 92015, 92016, 92017, 92018, 92019,
    92020, 92021, 92022, 92023, 92024, 92025, 92026, 92027, 92028, 92029,
    92030, 92031, 92032, 92033, 92034, 92035, 92036, 92037, 92038, 92039,
    92040, 92041, 92042, 92043, 92044, 92045, 92046, 92047, 92048, 92049, 
    92050, 92051, 92052, 92053, 92054, 92055
};

//This function is called when the player logs in (every login)  
void OnLogin(Player* pPlayer, bool firstLogin)
{
    if (!pPlayer)
        return;

    if (firstLogin)
    {
        //新手背包
        pPlayer->AddItem(5574, 4);
    }
    else
    {
        //军衔系统按在线时间获得(小时)
        uint16 total_player_time = pPlayer->GetTotalPlayedTime() / HOUR;
        for (int rank = 0; rank < 14; rank++)
        {
            if (total_player_time >= TIME_RANKS[rank])
                pPlayer->SetTitle(sCharTitlesStore.LookupEntry((pPlayer->GetTeam() == ALLIANCE ? ALLIANCE_TITLES : HORDE_TITLES)[rank]));
        }
    }
}

//This function is called when the player logs out   
void OnLogout(Player* /*pPlayer*/)
{

}

//This function is called when the player kills another player  
void OnPVPKill(Player* /*killer*/, Player* /*killed*/)
{

}

//This function is called when the player kills a creature
void OnCreatureKill(Player* killer, Creature* killed)
{
    if (!killer || !killed)
        return;

    bool CheckEntry = false;

    for (int i = 0; i < 129; i++)
    {
        if (CREATURE_ENTRY[i] == killed->GetEntry())
        {
            CheckEntry = true;
            break;
        }
    }

    if(!CheckEntry)
        return;


    uint32 itemId = 0;
    uint32 RandValue = 0;

    ////////////////////////////////////////////////////  副本坐骑挑战卡  //////////////////////////////////////////////////////////////

    RandValue = 1 + rand() % 100;
    if (RandValue <= 5)
    { 
        if (killer->HasItemCount(90100, 1))
        {
            itemId = ITEM_ENTRY_PT[rand() % 50];
            if (killer->AddItem(itemId, 1))
                killer->DestroyItemCount(90100, 1, true);
        }
    }
    else
    {
        if (killer->HasItemCount(90100, 1))
            killer->DestroyItemCount(90100, 1, true);
    }

    RandValue = 1 + rand() % 100;
    if (RandValue <= 5)
    {
        if (killer->HasItemCount(90101, 1))
        {
            itemId = ITEM_ENTRY_ZJ[rand() % 50];
            if (killer->AddItem(itemId, 1))
                killer->DestroyItemCount(90101, 1, true);
        }
    }
    else
    {
        if (killer->HasItemCount(90101, 1))
            killer->DestroyItemCount(90101, 1, true);
    }

    RandValue = 1 + rand() % 100;
    if (RandValue <= 5)
    {
        if (killer->HasItemCount(90102, 1))
        {
            itemId = ITEM_ENTRY_GJ[rand() % 50];
            if (killer->AddItem(itemId, 1))
                killer->DestroyItemCount(90102, 1, true);
        }
    }
    else
    {
        if (killer->HasItemCount(90102, 1))
            killer->DestroyItemCount(90102, 1, true);
    }

    ////////////////////////////////////////////////////  T2幻化挑战卡  //////////////////////////////////////////////////////////////

    RandValue = 1 + rand() % 100;
    if (RandValue <= 10)
    {
        if (killer->HasItemCount(90112, 1))
        {
            itemId = ITEM_TC_T2[rand() % 56];
            if (killer->AddItem(itemId, 1))
                killer->DestroyItemCount(90112, 1, true);
        }
    }
    else
    {
        if (killer->HasItemCount(90112, 1))
            killer->DestroyItemCount(90112, 1, true);
    }
}

//This function is called when the player gets killed by a creature  
void OnPlayerKilledByCreature(Creature* /*killer*/, Player* /*killed*/)
{

}

//This function is called just before the players level changes   
void OnPlayerLevelChanged(Player* /*pPlayer*/, uint8 /*oldLevel*/, uint8 /*newLevel*/)
{

}

//This function is called when the player resets his talents  
void OnPlayerTalentsReset(Player* /*pPlayer*/, bool /*no_cost*/)
{

}

void AddSC_onevents()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "scripted_on_events";
    pNewScript->pOnLogin = &OnLogin;
    pNewScript->pOnLogout = &OnLogout;
    pNewScript->pOnPVPKill = &OnPVPKill;
    pNewScript->pOnCreatureKill = &OnCreatureKill;
    pNewScript->pOnPlayerKilledByCreature = &OnPlayerKilledByCreature;
    pNewScript->pOnLevelChanged = &OnPlayerLevelChanged;
    pNewScript->pOnTalentsReset = &OnPlayerTalentsReset;
    pNewScript->RegisterSelf(false);
}