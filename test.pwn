#include <a_samp>
#include <brpsa-stdlib>
public OnPlayerDeath(playerid, killerid, reason) {
    GetPlayerPos(playerid, OldX, OldY, OldZ);
    va_SendClientMessage(playerid, -1, "Death Pos: %f %f %f", OldX, OldY, OldZ);
    return true;
}
