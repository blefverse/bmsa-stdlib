#include <a_samp>
#include <streamer>

#include <brpsa-stdlib>

public OnPlayerDeath(playerid, killerid, reason) {
    GetPlayerPos(playerid, OldX, OldY, OldZ);
    va_SendClientMessage(playerid, -1, "Death Pos: %f %f %f", OldX, OldY, OldZ);
	SetPlayerPosComp(playerid, 3.5, 3.5, 5.5, 2000, 0, 0);
    return true;
}
