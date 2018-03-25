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

//This function is called when the player logs in (every login)  
void OnLogin(Player* /*pPlayer*/, bool /*firstLogin*/)
{

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