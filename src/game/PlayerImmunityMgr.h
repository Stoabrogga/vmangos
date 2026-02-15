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

#ifndef PLAYER_IMMUNITY_MGR
#define PLAYER_IMMUNITY_MGR

#include "Common.h"
#include "Policies/Singleton.h"
#include "Pet.h"

enum PlayerImmunity
{
    PLAYER_IMMUNITY_PET               = 0x00000001, // if set, also apply immunities to player pets
    PLAYER_IMMUNITY_CHARM             = 0x00000002,
    PLAYER_IMMUNITY_FEAR              = 0x00000004,
    PLAYER_IMMUNITY_SILENCE           = 0x00000008,
    PLAYER_IMMUNITY_SLEEP             = 0x00000010,
    PLAYER_IMMUNITY_STUN              = 0x00000020,
    PLAYER_IMMUNITY_FREEZE            = 0x00000040,
    PLAYER_IMMUNITY_KNOCKOUT          = 0x00000080,
    PLAYER_IMMUNITY_POLYMORPH         = 0x00000100,
    PLAYER_IMMUNITY_HORROR            = 0x00000200,
    PLAYER_IMMUNITY_DAZE              = 0x00000400,
    PLAYER_IMMUNITY_SAPPED            = 0x00000800,
    PLAYER_IMMUNITY_KNOCK_BACK        = 0x00001000,
    PLAYER_IMMUNITY_POWER_DRAIN       = 0x00002000,
    PLAYER_IMMUNITY_AURA_MOD_CHARM    = 0x00004000,

    SPELL_SRC_IMMUNITY_CHARM          = 0xFFFF0000,
    SPELL_SRC_IMMUNITY_FEAR           = 0xFFFF0001,
    SPELL_SRC_IMMUNITY_SILENCE        = 0xFFFF0002,
    SPELL_SRC_IMMUNITY_SLEEP          = 0xFFFF0003,
    SPELL_SRC_IMMUNITY_STUN           = 0xFFFF0004,
    SPELL_SRC_IMMUNITY_FREEZE         = 0xFFFF0005,
    SPELL_SRC_IMMUNITY_KNOCKOUT       = 0xFFFF0006,
    SPELL_SRC_IMMUNITY_POLYMORPH      = 0xFFFF0007,
    SPELL_SRC_IMMUNITY_HORROR         = 0xFFFF0008,
    SPELL_SRC_IMMUNITY_DAZE           = 0xFFFF0009,
    SPELL_SRC_IMMUNITY_SAPPED         = 0xFFFF000A,
    SPELL_SRC_IMMUNITY_KNOCK_BACK     = 0xFFFF000B,
    SPELL_SRC_IMMUNITY_POWER_DRAIN    = 0xFFFF000C,
    SPELL_SRC_IMMUNITY_AURA_MOD_CHARM = 0xFFFF000D,
};

class Player;

// Handles applying player immunities on map changes, based on
// definitions in world-db table instance_player_immunity
class PlayerImmunityManager
{
public:
    PlayerImmunityManager() {}

public:
    void LoadFromDB();
    void PlayerEnterMap(uint32 mapId, Player* pPlayer);
    void PetEnterMap(uint32 mapId, Pet* pPet);
    static void HandleImmunities(Unit* unit, uint32 immunityFlags, bool apply);
    static void ApplyImmunity(Unit* unit, uint32 immunityFlags, uint32 playerImmunity, uint32 spellId, uint32 op, uint32 type);

    // <map ID, immunity flags>
    std::unordered_map<uint32, uint32> m_data;
};

#define sPlayerImmunityMgr MaNGOS::Singleton<PlayerImmunityManager>::Instance()

#endif
