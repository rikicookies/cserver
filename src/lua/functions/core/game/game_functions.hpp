////////////////////////////////////////////////////////////////////////
// Crystal Server - an opensource roleplaying game
////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////

#pragma once

class GameFunctions {
public:
	static void init(lua_State* L);

private:
	static int luaGameCreateMonsterType(lua_State* L);
	static int luaGameCreateNpcType(lua_State* L);

	static int luaGameGetSpectators(lua_State* L);

	static int luaGameGetBoostedCreature(lua_State* L);
	static int luaGameGetBestiaryList(lua_State* L);

	static int luaGameGetPlayers(lua_State* L);
	static int luaGameLoadMap(lua_State* L);
	static int luaGameloadMapChunk(lua_State* L);

	static int luaGameGetExperienceForLevel(lua_State* L);
	static int luaGameGetMonsterCount(lua_State* L);

	static int luaGameReportShadowedScripts(lua_State* L);
	static int luaGameGetPlayerCount(lua_State* L);
	static int luaGameGetNpcCount(lua_State* L);
	static int luaGameGetMonsterTypes(lua_State* L);

	static int luaGameGetTowns(lua_State* L);
	static int luaGameGetHouses(lua_State* L);

	static int luaGameGetGameState(lua_State* L);
	static int luaGameSetGameState(lua_State* L);

	static int luaGameGetWorldType(lua_State* L);

	static int luaGameGetReturnMessage(lua_State* L);

	static int luaGameCreateItem(lua_State* L);
	static int luaGameCreateContainer(lua_State* L);
	static int luaGameCreateMonster(lua_State* L);
	static int luaGameCreateSoulPitMonster(lua_State* L);
	static int luaGameGenerateNpc(lua_State* L);
	static int luaGameCreateNpc(lua_State* L);
	static int luaGameCreateTile(lua_State* L);

	static int luaGameGetBestiaryCharm(lua_State* L);
	static int luaGameCreateBestiaryCharm(lua_State* L);

	static int luaGameCreateItemClassification(lua_State* L);

	static int luaGameStartRaid(lua_State* L);

	static int luaGameGetClientVersion(lua_State* L);
	static int luaGameSetImprovedRespawnZones(lua_State* L);

	static int luaGameReload(lua_State* L);

	// JITTER DIAGNOSTIC: monotonic ms timestamp accessor for Lua instrumentation.
	static int luaGameMonotonicMs(lua_State* L);

	static int luaGameGetOfflinePlayer(lua_State* L);
	static int luaGameLoadBotPlayer(lua_State* L);
	static int luaGameBotActivate(lua_State* L);
	static int luaGameBotDeactivate(lua_State* L);
	static int luaGameBotForceDeactivate(lua_State* L);
	static int luaGameBotForceDeactivateForReload(lua_State* L);
	static int luaGameBotPauseForDeath(lua_State* L);
	static int luaGameBotSetAIPaused(lua_State* L);
	static int luaGameBotSetAllAIPaused(lua_State* L);
	static int luaGameBotHibernate(lua_State* L);
	static int luaGameBotWake(lua_State* L);
	static int luaGameBotRecoverOrphanForReload(lua_State* L);
	static int luaGameGetBotHibernationStates(lua_State* L);
	static int luaGameBotHibernateAllEligible(lua_State* L);
	static int luaGameBotWakeAllHibernated(lua_State* L);

	// Bot market wrappers (see src/game/game_bot_market.cpp)
	static int luaGameBotCreateMarketOffer(lua_State* L);
	static int luaGameBotAcceptMarketOffer(lua_State* L);
	static int luaGameBotCancelMarketOffer(lua_State* L);
	static int luaGameBotReactivateForReload(lua_State* L);
	static int luaGameBotCountActive(lua_State* L);
	static int luaGameBotCommand(lua_State* L);
	static int luaGameBotReload(lua_State* L);
	static int luaGameBotReregisterAll(lua_State* L);
	static int luaGameBotStartTickLoop(lua_State* L);
	static int luaGameBotGetState(lua_State* L);
	static int luaGameBotGetStatusText(lua_State* L);
	static int luaGameBotInParty(lua_State* L);
	static int luaGameBotIsActive(lua_State* L);
	static int luaGameBotSaveStates(lua_State* L);
	static int luaGameBotRestoreStates(lua_State* L);
	static int luaGameBotClearPersistedStates(lua_State* L);
	static int luaGameGetNormalizedPlayerName(lua_State* L);
	static int luaGameGetNormalizedGuildName(lua_State* L);
	static int luaGameHasEffect(lua_State* L);
	static int luaGameHasDistanceEffect(lua_State* L);

	static int luaGameAddInfluencedMonster(lua_State* L);
	static int luaGameRemoveInfluencedMonster(lua_State* L);
	static int luaGameGetInfluencedMonsters(lua_State* L);
	static int luaGameMakeFiendishMonster(lua_State* L);
	static int luaGameRemoveFiendishMonster(lua_State* L);
	static int luaGameGetFiendishMonsters(lua_State* L);

	static int luaGameGetBoostedBoss(lua_State* L);

	static int luaGameGetLadderIds(lua_State* L);
	static int luaGameGetDummies(lua_State* L);

	static int luaGameGetTalkActions(lua_State* L);
	static int luaGameGetEventCallbacks(lua_State* L);

	static int luaGameRegisterAchievement(lua_State* L);
	static int luaGameGetAchievementInfoById(lua_State* L);
	static int luaGameGetAchievementInfoByName(lua_State* L);
	static int luaGameGetSecretAchievements(lua_State* L);
	static int luaGameGetPublicAchievements(lua_State* L);
	static int luaGameGetAchievements(lua_State* L);

	static int luaGameGetSoulCoreItems(lua_State* L);
	static int luaGameGetMonstersByRace(lua_State* L);
	static int luaGameGetMonstersByBestiaryStars(lua_State* L);

	static int luaGameGetTitleByName(lua_State* L);

	static int luaHouseGetHouseCountByAccount(lua_State* L);
	static int luaGameSetGuildMotd(lua_State* L);

	// Guild management functions
	static int luaGameDisbandGuild(lua_State* L);
	static int luaGameInvitePlayerToGuild(lua_State* L);
	static int luaGameRemovePlayerFromGuild(lua_State* L);
	static int luaGamePromotePlayer(lua_State* L);
	static int luaGameDemotePlayer(lua_State* L);
	static int luaGamePassLeadership(lua_State* L);
	static int luaGameSetPlayerGuildNick(lua_State* L);
	static int luaGameSetRankName(lua_State* L);
	static int luaGameCreateGuild(lua_State* L);
	static int luaGameJoinGuild(lua_State* L);
	static int luaGameUpdateDailyRewardLastServerSave(lua_State* L);

	static int luaGameIsDebugBuild(lua_State* L);
};
