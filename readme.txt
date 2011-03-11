Cheater Buster Tools (old Admin ESP)

Make sure you deleted old adminesp.smx !!

Info:
Plugin show players positions through walls and other objects but only if observer is dead or spectate.
Also provide sv_cheats for admins only.

Now plugin should work on other games than CS:S, SDKHooks Extension is optional but Admin ESP don't work without it.

Admin ESP Feature:
Commands:
sm_adminesp - toggle esp
sm_adminesp <1 or 0> - sets esp to defined state
sm_adminesp <1 or 0> <#userid|nick|partofnick|team|@all|etc...> - set esp for other player(s)
sm_adminesp_teamspr <Team Index or team name> <path to sprite in models dir> - Adds esp sprite for team.
Cvars:
sm_adminesp_addtodt - default: 1 - if 1 sprites will be added to downloadtable.

Demo: http://www.youtube.com/watch?v=eUKxuM6ihvU

ESP Feature Notes:
1) SDKHooks Extenstion 1.3 or higher - Download (but plugin can work without it)
2) Demos recorded by user of this feature will include sprites (but read point 3 )
3) I recommend to use non-standard sprites or standard with different name, this will allow viewer of recorded demos to turn off/on dots by removing/adding sprite files. (zip package contain sprites from CS:S with different name).
4) Attachment Detection is feature that detects models without "forward" attachment, if model don't have this attachment sprite will be teleported to zone around waist. (i'm planning to add alternative attachments).

Admin Cheats Feature:
Commands:
sm_admincheats - synatx like in sm_adminesp - allow to use use game build client side cheats after death (read notes)
Cvars:
sm_admincheat_config - default "1" - if 1 execute admincheats_*. configs (read admin cheats notes)

Admin Cheats Notes:
1) Between death and spawn users of that command will have sv_cheats 1 so they can use client side cheats like r_drawothermodels 2)
2) Every death client must to re-enable client-side cheat cvars, plugin can't set them back.
3) Some server-side anti-cheats (like KAC) can ban users of this command, that is because it changes sv_cheats only for specific client's not whole server.
4) To make this function even possibly to use with anti-cheats i have added 2 configs:
sourcemod/admincheats_on.cfg - executed when first sv_cheats 1 is send (first person is using sv_cheats 1)
sourcemod/admincheats_off.cfg - executed when last sv_cheats 0 is send (there is nobody with sv_cheats 1)
in this configs you can add commands/cvars to temporary disable whole anti-cheat or some part of it only when its required.
Example for KAC & r_drawothermodels attached.
5) This function is using much less server CPU than sm_adminesp.

Installation:
1) Unpack package to servers game folder (cstrike, tf, ...)
2) Configure cfg/sourcemod/cheatbustertools.cfg
3) If you disabled Sprites downloading place materials from package to your game folder
4) Update cfg/sourcemod/admincheats_on.cfg and admincheats_off.cfg for your needs. (Read Admin Cheats Notes)

Overall Notes:
1) If you want to change required flag for commands use Overriding Command Access (SourceMod)
2) When you will find some bug please post output of this commands
meta list
sm plugins list
sm exts list
sm_cb_table when using adminesp and bug occurred.
with bug description and something about server config.

ChangeLog:
1.2.1 11.03.11
* Fixed custom sprites not being added to download table
+ Added changing sprites model when player change his team

1.2 - 9.03.11
+ Fixed sprites showing up to all players (i hope)
+ Admin ESP is available only when SDKHooks exist but rest of plugin can work without it.
+ Maked plugin more game independent, but i didn't test in on other games than CS:S
+ Added Attachment Detection (currently only for CS:S linux servers), require LookupAttachment signature in cheatbuster.gamedata.txt. Plugin can still work without this sig.
+ Added sm_adminesp_teamspr
* Improved ObserverTarget functions
* Changed sm_adminesp_table to sm_cb_table
- Removed hard coded sprites

1.1.0 - 26.08.10
+ Added command sm_admincheat that allows to use use game build client side cheats after death (read notes)
1.0.3 - 08.07.10 (adminesp_1_0_3.*)
* Fixed (maybe) unwanted ESP for all & alive players
+ Added Autoupdate function (require Plugin Autoupdate & sm_adminesp_autoupdate 1)
1.0.2 - 07.02.10
- removed debug messages,
+ now plugin is active only if someone is using it,

Todo:
- attachment alternative with more position control
- sv_showimpatcs client side
- everything to better performance ;P
- don't show teammates cvar, 2x less cpu usage (maybe)

To compile you must have sdkhooks.inc and SMLIB