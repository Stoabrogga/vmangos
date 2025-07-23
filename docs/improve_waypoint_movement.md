## Improve waypoint movement

VMaNGOS GitHub pull request: <https://github.com/vmangos/core/pull/3013>

The pull request was automatically closed because I deleted my GitLab and GitHub "Stoabrogga" accounts in favor of Codeberg. I'll not merge this because it needs to be tested with many players, but can provide the diff if anyone wants to add it manually: [`improve_waypoint_movement.diff`](improve_waypoint_movement.diff)

### Description

Adjust the algorithm for waypoint movement similar to CMaNGOS:

- Try to generate movement splines which are at least 6s long
- 1.5s before the spline is finished start a new spline

This prevents the animation resets occuring at each waypoint.

### Test

Watch different creatures which use waypoint movement, e.g.:

- Thora Feathermoon (ID 5798, GUID 15169)
- Theresa (ID 5697, GUID 41840)
- Lord Kazzak (ID 12397, GUID 156950)
- Felguard Elite (ID 8717, GUID 2791)
- Pridewing Soarer (ID 6141, GUID 32374)
- Westfall Woodworker (ID 6670, GUID 45521)
- Thomas Booker (ID 1437, GUID 9468)
- Gordo (ID 10666, GUID 28413)
- Gazelle (ID 4166, GUID 14049)
- Wooly Kodo (ID 3237, GUID 15144)
- Warpwood Tangler (ID 11464, GUID 300943)
- Grunt Gargal (ID 9086, GUID 6883)
- Sorcerer Ashcrombe (ID 3850, GUID 16262)

Also watch creature formations without waypoint movement, e.g. Emeraldon Boughguard (GUID 33246, ID 12474).

