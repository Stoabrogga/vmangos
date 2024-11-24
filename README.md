Fork of [VMaNGOS](https://github.com/vmangos/core) with a few customizations

[Build and installation tips](https://codeberg.org/Stoabrogga/docs/src/branch/root/vmangos#readme)

Customizations:

| date       | commit                                   | comment | related commits |
|------------|------------------------------------------|---------|-----------------|
| 2024-11-24 | 6200557b7a745586c7bdbb9715dda0ccd4082cd0 | Add mangosd parameter "BlackwingLair.Razorgore.EggCount" | |
| 2024-11-20 | 45820b2eaffada6c4527057ec37454614aeb94e3 | Add mangosd parameter "RaidScaling.HP" | |
| 2024-11-09 | 3e4453e65e73d4bebef89c8f0575109d6d8874ff | Add mangosd parameters "Rate.Health.Creature" & "Rate.Mana.Creature" (the parameters "Rate.Health" & "Rate.Mana" now only affect players) | |
| 2024-09-29 | 9b4c8241ba7d267a7f6be2b22f208996acf92a4d | Add `CREATURE_FAMILY_WORM`, see [`vmangos_creature_family_worm`](https://codeberg.org/Stoabrogga/bash/src/branch/root/vmangos/bin/vmangos_creature_family_worm) | |
| 2024-09-15 | e0c7c5ad2d543ec1f85c8226babfc29293a3b4fc | Add new mangosd parameters for pets | bb8d96d5f17996e80dafa7d4f10f6010e637eb12 bc892914ff48065927f5ddbc0f758e36860161d9 aab1b6b1f7a278789001a830ad881fd321ab254f f1bb9e2bce1d3c1903a8f81840ef21dac8b0e1a2 |
| 2024-09-10 | bbe19d1f9b4e5c4937028444d8929b8fe6cf4b61 | Add new table [`instance_player_immunity`](docs/instance_player_immunity.md) | 17864785b6f058be399b3faef3a46559818f45d8 1e6ff2732524273534cf5a43dd68db8329d74dcc |
| 2024-09-10 | ff36bce0b36eb8acda00a09bde7aa5d8e2c71b2b | Add mangosd parameter "Rate.Reputation.Gain.Threshold" | |
