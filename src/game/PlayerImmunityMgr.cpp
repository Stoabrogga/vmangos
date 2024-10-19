/*
* Copyright (C) 2024 Stoabrogga <https://codeberg.org/Stoabrogga>
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

#include "PlayerImmunityMgr.h"
#include "Policies/Singleton.h"
#include "Database/DatabaseEnv.h"
#include "Policies/SingletonImp.h"
#include "Player.h"
#include "ProgressBar.h"

INSTANTIATE_SINGLETON_1(PlayerImmunityManager);

void PlayerImmunityManager::LoadFromDB()
{
    m_data.clear();

    sLog.Out(LOG_BASIC, LOG_LVL_MINIMAL, "> Loading table `instance_player_immunity`");
    uint32 count = 0;
    std::unique_ptr<QueryResult> result = WorldDatabase.Query("SELECT map_id, immunity_flags, enabled FROM instance_player_immunity");
    if (!result)
    {
        BarGoLink bar(1);
        bar.step();
        sLog.Out(LOG_BASIC, LOG_LVL_MINIMAL, "");
        sLog.Out(LOG_BASIC, LOG_LVL_MINIMAL, ">> Table instance_player_immunity is empty.");
    }
    else
    {
        BarGoLink bar((int)result->GetRowCount());
        do
        {
            bar.step();

            Field* fields = result->Fetch();

            uint32 mapId  = fields[0].GetUInt32();
            uint32 immunityFlags = fields[1].GetUInt32();
            bool enabled = (bool)fields[2].GetUInt8();

            ++count;

            if (enabled)
                m_data[mapId] = immunityFlags;

        } while (result->NextRow());

        sLog.Out(LOG_BASIC, LOG_LVL_MINIMAL, ">> Loaded %u entries from instance_player_immunity", count);
        sLog.Out(LOG_BASIC, LOG_LVL_MINIMAL, "");
    }
}

void PlayerImmunityManager::PlayerEnterMap(uint32 mapId, Player* pPlayer)
{
    if (!pPlayer || m_data.empty())
        return;

    auto it = m_data.find(mapId);
    uint32 immunityFlags = it != m_data.end() ? it->second : 0;
    HandleImmunities(pPlayer, immunityFlags, immunityFlags > PLAYER_IMMUNITY_PET);
}

void PlayerImmunityManager::PetEnterMap(uint32 mapId, Pet* pPet)
{
    if (!pPet || m_data.empty())
        return;

    auto it = m_data.find(mapId);
    uint32 immunityFlags = it != m_data.end() ? it->second : 0;
    HandleImmunities(pPet, immunityFlags, immunityFlags > PLAYER_IMMUNITY_PET && (immunityFlags & PLAYER_IMMUNITY_PET));
}

void PlayerImmunityManager::HandleImmunities(Unit* unit, uint32 immunityFlags, bool apply)
{
    if (apply)
    {
        // apply immunities
        ApplyImmunity(unit, immunityFlags, PLAYER_IMMUNITY_CHARM, SPELL_SRC_IMMUNITY_CHARM, IMMUNITY_MECHANIC, MECHANIC_CHARM);
        ApplyImmunity(unit, immunityFlags, PLAYER_IMMUNITY_FEAR, SPELL_SRC_IMMUNITY_FEAR, IMMUNITY_MECHANIC, MECHANIC_FEAR);
        ApplyImmunity(unit, immunityFlags, PLAYER_IMMUNITY_SILENCE, SPELL_SRC_IMMUNITY_SILENCE, IMMUNITY_MECHANIC, MECHANIC_SILENCE);
        ApplyImmunity(unit, immunityFlags, PLAYER_IMMUNITY_SLEEP, SPELL_SRC_IMMUNITY_SLEEP, IMMUNITY_MECHANIC, MECHANIC_SLEEP);
        ApplyImmunity(unit, immunityFlags, PLAYER_IMMUNITY_STUN, SPELL_SRC_IMMUNITY_STUN, IMMUNITY_MECHANIC, MECHANIC_STUN);
        ApplyImmunity(unit, immunityFlags, PLAYER_IMMUNITY_FREEZE, SPELL_SRC_IMMUNITY_FREEZE, IMMUNITY_MECHANIC, MECHANIC_FREEZE);
        ApplyImmunity(unit, immunityFlags, PLAYER_IMMUNITY_KNOCKOUT, SPELL_SRC_IMMUNITY_KNOCKOUT, IMMUNITY_MECHANIC, MECHANIC_KNOCKOUT);
        ApplyImmunity(unit, immunityFlags, PLAYER_IMMUNITY_POLYMORPH, SPELL_SRC_IMMUNITY_POLYMORPH, IMMUNITY_MECHANIC, MECHANIC_POLYMORPH);
        ApplyImmunity(unit, immunityFlags, PLAYER_IMMUNITY_HORROR, SPELL_SRC_IMMUNITY_HORROR, IMMUNITY_MECHANIC, MECHANIC_HORROR);
        ApplyImmunity(unit, immunityFlags, PLAYER_IMMUNITY_DAZE, SPELL_SRC_IMMUNITY_DAZE, IMMUNITY_MECHANIC, MECHANIC_DAZE);
        ApplyImmunity(unit, immunityFlags, PLAYER_IMMUNITY_SAPPED, SPELL_SRC_IMMUNITY_SAPPED, IMMUNITY_MECHANIC, MECHANIC_SAPPED);
        ApplyImmunity(unit, immunityFlags, PLAYER_IMMUNITY_KNOCK_BACK, SPELL_SRC_IMMUNITY_KNOCK_BACK, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK);
        ApplyImmunity(unit, immunityFlags, PLAYER_IMMUNITY_POWER_DRAIN, SPELL_SRC_IMMUNITY_POWER_DRAIN, IMMUNITY_EFFECT, SPELL_EFFECT_POWER_DRAIN);
        ApplyImmunity(unit, immunityFlags, PLAYER_IMMUNITY_AURA_MOD_CHARM, SPELL_SRC_IMMUNITY_AURA_MOD_CHARM, IMMUNITY_STATE, SPELL_AURA_MOD_CHARM);
    }
    else
    {
        // remove all immunities
        unit->ApplySpellImmune(SPELL_SRC_IMMUNITY_CHARM, IMMUNITY_MECHANIC, MECHANIC_CHARM, false);
        unit->ApplySpellImmune(SPELL_SRC_IMMUNITY_FEAR, IMMUNITY_MECHANIC, MECHANIC_FEAR, false);
        unit->ApplySpellImmune(SPELL_SRC_IMMUNITY_SILENCE, IMMUNITY_MECHANIC, MECHANIC_SILENCE, false);
        unit->ApplySpellImmune(SPELL_SRC_IMMUNITY_SLEEP, IMMUNITY_MECHANIC, MECHANIC_SLEEP, false);
        unit->ApplySpellImmune(SPELL_SRC_IMMUNITY_STUN, IMMUNITY_MECHANIC, MECHANIC_STUN, false);
        unit->ApplySpellImmune(SPELL_SRC_IMMUNITY_FREEZE, IMMUNITY_MECHANIC, MECHANIC_FREEZE, false);
        unit->ApplySpellImmune(SPELL_SRC_IMMUNITY_KNOCKOUT, IMMUNITY_MECHANIC, MECHANIC_KNOCKOUT, false);
        unit->ApplySpellImmune(SPELL_SRC_IMMUNITY_POLYMORPH, IMMUNITY_MECHANIC, MECHANIC_POLYMORPH, false);
        unit->ApplySpellImmune(SPELL_SRC_IMMUNITY_HORROR, IMMUNITY_MECHANIC, MECHANIC_HORROR, false);
        unit->ApplySpellImmune(SPELL_SRC_IMMUNITY_DAZE, IMMUNITY_MECHANIC, MECHANIC_DAZE, false);
        unit->ApplySpellImmune(SPELL_SRC_IMMUNITY_SAPPED, IMMUNITY_MECHANIC, MECHANIC_SAPPED, false);
        unit->ApplySpellImmune(SPELL_SRC_IMMUNITY_KNOCK_BACK, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, false);
        unit->ApplySpellImmune(SPELL_SRC_IMMUNITY_POWER_DRAIN, IMMUNITY_EFFECT, SPELL_EFFECT_POWER_DRAIN, false);
        unit->ApplySpellImmune(SPELL_SRC_IMMUNITY_AURA_MOD_CHARM, IMMUNITY_STATE, SPELL_AURA_MOD_CHARM, false);
    }
}

void PlayerImmunityManager::ApplyImmunity(Unit* unit, uint32 immunityFlags, uint32 playerImmunity, uint32 spellId, uint32 op, uint32 type)
{
    if (immunityFlags & playerImmunity)
        unit->ApplySpellImmune(spellId, op, type, true);
    else
        unit->ApplySpellImmune(spellId, op, type, false);
}
