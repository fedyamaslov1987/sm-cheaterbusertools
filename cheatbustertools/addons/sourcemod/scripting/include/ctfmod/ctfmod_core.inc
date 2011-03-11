#if defined _ctfmod_core_included_
  #endinput
#endif
#define _ctfmod_core_included_

#define BOTH_TEAMS 0
#define RED 2
#define BLU 3

#define MAXCVARLEN 128
#define DMAXOBJECTS 32
#define MAXTEAMS 4

/**
 * @section Bitwise values definitions for type flags.
 */
 #define CTFTYPE_MUST_ALIVE				(1<<0)		/**< Touching client must be alive, check only on Touch*/
 #define CTFTYPE_ALLOWTOUCH_TEAM		(1<<1)		/**< Allow touch by clients in object team */
 #define CTFTYPE_ALLOWTOUCH_OTHERTEAM	(1<<2)		/**< Allow touch by clients in other team than object */
 #define CTFTYPE_ALLOWTAKE_TEAM			(1<<3)		/**< Allow take by clients in object team */
 #define CTFTYPE_ALLOWTAKE_OTHERTEAM	(1<<4)		/**< Allow take by clients in other team than object */
 #define CTFTYPE_CAPTURE_TEAM			(1<<5)		/**< Object Capture objects with same team */
 #define CTFTYPE_CAPTURE_OTHERTEAM		(1<<6)		/**< Object Capture objects with other team */
 #define CTFTYPE_ALLOWCAPTURE			(1<<7)		/**< Allow to capture this object*/
 #define CTFTYPE_ALLOWTAKE_MORE			(1<<8)		/**< Allow to take if client have other object*/
 /**
 * @endsection
 */

#if 1 // ############################################## Natives ##################################### //

/**
 * Get CTFMod Core state
 *
 * @noparam
 * @return true on Enabled, flase on disabled
 */
native bool:CTF_GetCoreState();

/**
 * Get Max Objects (flags/bases) count
 *
 * @noparam
 * @return The max objects count in int
 */
native CTF_GetMaxObjects();

/**
 * Get current Objects (flags/bases) count
 *
 * @noparam
 * @return The current objects count in int
 */
native CTF_GetObjectsCount();

/**
 * Set current Objects (flags/bases) count
 *
 * @param count Set current Objects count to this number
 * @return bool True if success, false if higher than MAXOBJECTS or less than 0
 */
native bool:CTF_SetObjectsCount(count);

/**
 * Set current Objects (flags/bases) type, team, positions. Angles from defaults
 * Use CTF_SetObjectAng for Angles setup
 *
 * With CTF_GetObjectsCount & CTF_SetObjectsCount can be used as Add Objects Function
 *
 * @param objectnr	Object ID
 * @param type		Object type, FLAG or BASE
 * @param team		Object team, RED or BLU
 * @param pos		Array with coordinates
 * @param ang		Array with angles when standing
 * @param plrang	Array with angles when carred by player
 * @return bool True if success.
 */
native bool:CTF_SetObjectParam(objectnr, type, team, Float:pos[3], Float:ang[3], Float:plrpos[3],Float:plrang[3], String:Model[], String:Attach, String:Animation);

#endif

#if 1 // ############################################## Global Forwards ################################################//

/**
 * Called when CTFmod is turning on, ET_Event
 * 
 * @return bool True if success.
 */
forward OnCTFTurnOn();

/**
 * Called when CTFmod is turning off, ET_Event
 * 
 * @return bool True if success.
 */
forward OnCTFTurnOff();

#endif

#if 1 // ############################################## Hook Natives ################################################//
functag  OnObjectCapture Action:public(&client, &CapturedObj, &CapturingObj);

native bool:CTFHookObjectCapture(OnObjectCapture:func);
native bool:CTFUnHookObjectCapture(OnObjectCapture:func);

//Param_CellByRef, Param_CellByRef, Param_String, Param_FloatByRef);
functag  OnObjectTouch Action:public(&TouchedObj, &TouchedBy, String:output[], &delay);

native bool:CTFHookObjectTouch(OnObjectTouch:func);
native bool:CTFUnHookObjectTouch(OnObjectTouch:func);

functag OnObjectTake Action:public(&client, &TakenObj);

native bool:CTFHookObjectTake(OnObjectTake:func);
native bool:CTFUnHookObjectTake(OnObjectTake:func);

functag OnObjectDrop Action:public(&DropedObj, &client);

native bool:CTFHookObjectDrop(OnObjectDrop:func);
native bool:CTFUnHookObjectDrop(OnObjectDrop:func);


#endif

#if 1 // ############################################## Stock ################################################//
stock CopyVector(Float:vec_to[3], const Float:vec_from[3])
{
	vec_to[0] = vec_from[0];
	vec_to[1] = vec_from[1];
	vec_to[2] = vec_from[2];
}
#endif