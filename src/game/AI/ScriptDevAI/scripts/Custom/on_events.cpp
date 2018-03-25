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
void OnCreatureKill(Player* /*killer*/, Creature* /*killed*/)
{

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