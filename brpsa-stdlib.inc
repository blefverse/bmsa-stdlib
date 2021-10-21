/* ---------------------------------------------------------------------------- */
/*      Blefonix RolePlay Standard Library                                      */
/* ---------------------------------------------------------------------------- */

#if !defined _samp_included
	#error "Include a_samp before brpsa-stdlib"
#endif

#if !defined STREAMER_TYPE_OBJECT
	#error "Include streamer before brpsa-stdlib"
#endif

// built-in include guard removal, just in case if the
// user has a local dependency with the same file name
#if defined _inc_brpsa_stdlib
	#undef _inc_brpsa_stdlib
#endif

// custom include-guard to
// ensure we don't duplicate
#if defined _brpsa_stdlib_included
	#endinput
#endif
#define _brpsa_stdlib_included

/* ---------------------------------------------------------------------------- */
/*      https://github.com/brpsamp/brpsa-stdlib                                 */
/* ---------------------------------------------------------------------------- */

#include <a_samp>
#include <logger>
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_va>

/*
 *  DEFINES
*/

#if !defined TP_WAIT_TIME
	#define TP_WAIT_TIME 1000
#endif

/*
 *  VARIABLES
*/

#include <stdlib-vars>

static
    TP_AwaitingTime[MAX_PLAYERS],
    Float:TP_AwaitingPos[MAX_PLAYERS][3];

static Float:TP_GetDistanceFromAwaiting(playerid) {
    new Float:pX, Float:pY, Float:pZ;
    GetPlayerPos(playerid, pX, pY, pZ);
    return (floatsqroot(floatpower(pX - TP_AwaitingPos[playerid][0], 2.0) + floatpower(pY - TP_AwaitingPos[playerid][1], 2.0) + floatpower(pZ - TP_AwaitingPos[playerid][2], 2.0)));
}

/*
 *  PUBLICS
*/

hook OnScriptInit() {
    #if !defined BRPSA_NO_LOG
        Logger_ToggleDebug("brpsa-stdlib", true);
    #endif
    #if !defined BRPSA_NO_INFO
        print("\nOnScriptInit |> brpsa-stdlib 0.0.1");
    #endif
    return true;
}

hook OnPlayerConnect(playerid) {
    TP_AwaitingPos[playerid][0] = -1.0;
    return true;
}

hook OnPlayerUpdate(playerid) {
    if (TP_AwaitingTime[playerid] != 0) {
        if ((NetStats_GetConnectedTime(playerid) > TP_AwaitingTime[playerid]) || (TP_GetDistanceFromAwaiting(playerid) < 0.2)) {
            TogglePlayerControllable(playerid, true);
            Streamer_ToggleItemUpdate(playerid, STREAMER_TYPE_OBJECT, true);
            TP_AwaitingPos[playerid][0] = -1.0;
            TP_AwaitingTime[playerid] = 0;
        }
    }
    return true;
}

/*
 *  STOCKS
*/

stock bool:IsPlayerTeleporting(playerid) return (TP_AwaitingTime[playerid] != 0);

stock SetPlayerPosComp(playerid, Float:X, Float:Y, Float:Z, wait_time = TP_WAIT_TIME, world = -1, interior = -1) {
    if (!IsPlayerConnected(playerid)) return 0;

    TP_AwaitingPos[playerid][0] = X;
    TP_AwaitingPos[playerid][1] = Y;
    TP_AwaitingPos[playerid][2] = Z;

    new conn_time = NetStats_GetConnectedTime(playerid);
    TP_AwaitingTime[playerid] = ((wait_time > 0) ? (conn_time + wait_time) : conn_time);

    TogglePlayerControllable(playerid, false);
    Streamer_ToggleItemUpdate(playerid, STREAMER_TYPE_OBJECT, false);
    Streamer_UpdateEx(playerid, X, Y, Z, world, interior, STREAMER_TYPE_OBJECT);

    if (interior != -1) SetPlayerInterior(playerid, interior);
    if (world != -1) SetPlayerVirtualWorld(playerid, world);

    return SetPlayerPos(playerid, X, Y, Z - 0.3);
}
