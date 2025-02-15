## Table `instance_player_immunity`

This table can be used to apply immunities to the players for each map. Structure:

| Field            | Type             | Null | Key |
|------------------|------------------|------|-----|
| `map_id`         | int(10) unsigned | NO   | PRI |
| `immunity_flags` | int(10) unsigned | NO   |     |
| `enabled`        | tinyint(1)       | NO   |     |
| `comment`        | varchar(256)     | NO   |     |

It is possible to override the immunities temporarily until the next map change using this command:<br>`modify immunities <immunity_flags>`

The immunities are specified as bitmask in column `immunity_flags`:

| Name                             | Flag  | Hex        | Comment |
|----------------------------------|-------|------------|---------|
| `PLAYER_IMMUNITY_PET`            |     1 | 0x00000001 | if set, also apply immunities to player pets |
| `PLAYER_IMMUNITY_CHARM`          |     2 | 0x00000002 | |
| `PLAYER_IMMUNITY_FEAR`           |     4 | 0x00000004 | |
| `PLAYER_IMMUNITY_SILENCE`        |     8 | 0x00000008 | |
| `PLAYER_IMMUNITY_SLEEP`          |    16 | 0x00000010 | |
| `PLAYER_IMMUNITY_STUN`           |    32 | 0x00000020 | |
| `PLAYER_IMMUNITY_FREEZE`         |    64 | 0x00000040 | |
| `PLAYER_IMMUNITY_KNOCKOUT`       |   128 | 0x00000080 | |
| `PLAYER_IMMUNITY_POLYMORPH`      |   256 | 0x00000100 | |
| `PLAYER_IMMUNITY_HORROR`         |   512 | 0x00000200 | |
| `PLAYER_IMMUNITY_DAZE`           |  1024 | 0x00000400 | |
| `PLAYER_IMMUNITY_SAPPED`         |  2048 | 0x00000800 | |
| `PLAYER_IMMUNITY_KNOCK_BACK`     |  4096 | 0x00001000 | |
| `PLAYER_IMMUNITY_POWER_DRAIN`    |  8192 | 0x00002000 | |
| `PLAYER_IMMUNITY_AURA_MOD_CHARM` | 16384 | 0x00004000 | |

In order to not interfere with scripts (source spell ID 0) or custom spells very high spell IDs where chosen to identify the source of the immunities for removal:

```
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
```

