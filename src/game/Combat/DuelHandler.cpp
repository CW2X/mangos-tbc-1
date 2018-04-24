/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Common.h"
#include "WorldPacket.h"
#include "Server/WorldSession.h"
#include "Log.h"
#include "Entities/Player.h"
#include "World/World.h"

void WorldSession::HandleDuelAcceptedOpcode(WorldPacket& recvPacket)
{
    ObjectGuid guid;
    recvPacket >> guid;

    // Check for own duel info first
    Player* self = GetPlayer();
    if (!self || !self->duel)
        return;

    // Check if we are not accepting our own duel request
    Player* initiator = self->duel->initiator;
    if (!initiator || self == initiator)
        return;

    // Check for opponent
    Player* opponent = self->duel->opponent;
    if (!opponent || self == opponent)
        return;

    // Check if duel is starting
    if (self->duel->startTimer != 0 || opponent->duel->startTimer != 0)
        return;

    // Check if duel is in progress
    if (self->duel->startTime != 0 || opponent->duel->startTime != 0)
        return;

    DEBUG_FILTER_LOG(LOG_FILTER_COMBAT, "WORLD: received CMSG_DUEL_ACCEPTED");
    DEBUG_FILTER_LOG(LOG_FILTER_COMBAT, "Player 1 is: %u (%s)", self->GetGUIDLow(), self->GetName());
    DEBUG_FILTER_LOG(LOG_FILTER_COMBAT, "Player 2 is: %u (%s)", opponent->GetGUIDLow(), opponent->GetName());

    time_t now = time(nullptr);
    self->duel->startTimer = now;
    opponent->duel->startTimer = now;

    self->SendDuelCountdown(3000);
    opponent->SendDuelCountdown(3000);

    if (sWorld.getConfig(CONFIG_BOOL_DUEL_RESET))
    {
        if (!self->GetMap()->IsDungeon() && !opponent->GetMap()->IsDungeon())
        {
            // remove diminishing returns
            self->ClearDiminishings();
            opponent->ClearDiminishings();

            // set health, mana to 100%
            self->SetHealth(self->GetMaxHealth());
            opponent->SetHealth(opponent->GetMaxHealth());

            //set mana to 100%
            if (self->GetPowerType() == POWER_MANA)
                self->SetPower(POWER_MANA, self->GetMaxPower(POWER_MANA));
            if (opponent->GetPowerType() == POWER_MANA)
                opponent->SetPower(POWER_MANA, opponent->GetMaxPower(POWER_MANA));

            //set Rage to 0
            if (self->GetPowerType() == POWER_RAGE)
                self->SetPower(POWER_RAGE, 0);
            if (opponent->GetPowerType() == POWER_RAGE)
                opponent->SetPower(POWER_RAGE, 0);

            // remove cooldowns < 15min
            self->RemoveArenaSpellCooldowns();
            opponent->RemoveArenaSpellCooldowns();

        }
    }
}

void WorldSession::HandleDuelCancelledOpcode(WorldPacket& recvPacket)
{
    ObjectGuid guid;
    recvPacket >> guid;

    // Check for own duel info first
    Player* self = GetPlayer();
    if (!self || !self->duel)
        return;

    // Check for opponent
    Player* opponent = self->duel->opponent;
    if (!opponent)
        return;

    DEBUG_LOG("WORLD: Received opcode CMSG_DUEL_CANCELLED");

    // If duel is in progress, then player surrendered in a duel using /forfeit
    if (self->duel->startTime != 0)
    {
        self->CombatStopWithPets(true);
        opponent->CombatStopWithPets(true);
        self->CastSpell(self, 7267, TRIGGERED_OLD_TRIGGERED);    // beg
        self->DuelComplete(DUEL_WON);
        return;
    }
    // Player either discarded the duel using the "discard button" or used "/forfeit" before countdown reached 0
    self->DuelComplete(DUEL_INTERRUPTED);
}
