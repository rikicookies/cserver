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

#include "lua/functions/core/game/config_functions.hpp"

#include "config/configmanager.hpp"
#include "lua/functions/lua_functions_loader.hpp"

void ConfigFunctions::init(lua_State* L) {
	Lua::registerTable(L, "configManager");
	Lua::registerMethod(L, "configManager", "getString", luaConfigManagerGetString);
	Lua::registerMethod(L, "configManager", "getNumber", luaConfigManagerGetNumber);
	Lua::registerMethod(L, "configManager", "getBoolean", luaConfigManagerGetBoolean);
	Lua::registerMethod(L, "configManager", "getFloat", luaConfigManagerGetFloat);

#define registerMagicEnumIn(L, tableName, enumValue)         \
	do {                                                     \
		auto name = magic_enum::enum_name(enumValue).data(); \
		Lua::registerVariable(L, tableName, name, value);    \
	} while (0)
	Lua::registerTable(L, "configKeys");
	for (auto value : magic_enum::enum_values<ConfigKey_t>()) {
		auto enumName = magic_enum::enum_name(value).data();
		if (enumName) {
			registerMagicEnumIn(L, "configKeys", value);
			g_logger().debug("Registering ConfigManager enum name '{}' value '{}' to lua", enumName, fmt::underlying(value));
		}
	}
#undef registerMagicEnumIn

	// Bot keys can extend past magic_enum's configured range. Register the
	// remaining keys directly from the same tables used to load their values.
#define REGISTER_BOT_CONFIG_KEY(enumKey, luaKey, defaultValue)                      \
	if constexpr (magic_enum::enum_name(enumKey).empty()) {                         \
		Lua::registerVariable(L, "configKeys", #enumKey, static_cast<lua_Number>(enumKey)); \
	}
	BOT_NAV_REALISM_CONFIG_KEYS(REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY)
	BOT_ACTIVITY_CONFIG_KEYS(REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY)
	BOT_MARKET_CONFIG_KEYS(REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY)
	BOT_PARTY_TRAIL_CONFIG_KEYS(REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY)
	BOT_AMBIENT_ROAM_CONFIG_KEYS(REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY)
	BOT_CORPSE_LOOT_CONFIG_KEYS(REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY)
	BOT_ACTIVITY_PCT_CONFIG_KEYS(REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY)
	BOT_LURE_KITE_CONFIG_KEYS(REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY)
	BOT_SHRINE_CONFIG_KEYS(REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY, REGISTER_BOT_CONFIG_KEY)
#undef REGISTER_BOT_CONFIG_KEY
	// Register explicit bot option names even past the reflection limit.
	Lua::registerVariable(L, "configKeys", "BOT_ADVERTISING_INTERVAL_MAX_MS", static_cast<lua_Number>(BOT_ADVERTISING_INTERVAL_MAX_MS));
	Lua::registerVariable(L, "configKeys", "BOT_ADVERTISING_INTERVAL_MIN_MS", static_cast<lua_Number>(BOT_ADVERTISING_INTERVAL_MIN_MS));
	Lua::registerVariable(L, "configKeys", "BOT_ADV_STONE_CHEST_DUMMY_CAP_PCT", static_cast<lua_Number>(BOT_ADV_STONE_CHEST_DUMMY_CAP_PCT));
	Lua::registerVariable(L, "configKeys", "BOT_ADV_STONE_DWELL_CHEST_MAX_SEC", static_cast<lua_Number>(BOT_ADV_STONE_DWELL_CHEST_MAX_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_ADV_STONE_DWELL_CHEST_MIN_SEC", static_cast<lua_Number>(BOT_ADV_STONE_DWELL_CHEST_MIN_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_ADV_STONE_DWELL_DUMMY_MAX_SEC", static_cast<lua_Number>(BOT_ADV_STONE_DWELL_DUMMY_MAX_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_ADV_STONE_DWELL_DUMMY_MIN_SEC", static_cast<lua_Number>(BOT_ADV_STONE_DWELL_DUMMY_MIN_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_ADV_STONE_DWELL_IDLE_MAX_SEC", static_cast<lua_Number>(BOT_ADV_STONE_DWELL_IDLE_MAX_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_ADV_STONE_DWELL_IDLE_MIN_SEC", static_cast<lua_Number>(BOT_ADV_STONE_DWELL_IDLE_MIN_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_CHAT_ANTI_REPEAT_RING_SIZE", static_cast<lua_Number>(BOT_CHAT_ANTI_REPEAT_RING_SIZE));
	Lua::registerVariable(L, "configKeys", "BOT_CHAT_COOLDOWN_MAX_MS", static_cast<lua_Number>(BOT_CHAT_COOLDOWN_MAX_MS));
	Lua::registerVariable(L, "configKeys", "BOT_CHAT_COOLDOWN_MIN_MS", static_cast<lua_Number>(BOT_CHAT_COOLDOWN_MIN_MS));
	Lua::registerVariable(L, "configKeys", "BOT_CHAT_MASTER_CHANCE_PCT", static_cast<lua_Number>(BOT_CHAT_MASTER_CHANCE_PCT));
	Lua::registerVariable(L, "configKeys", "BOT_CHAT_VERBOSE_LOG", static_cast<lua_Number>(BOT_CHAT_VERBOSE_LOG));
	Lua::registerVariable(L, "configKeys", "BOT_HIBERNATED_CHAT_ENABLED", static_cast<lua_Number>(BOT_HIBERNATED_CHAT_ENABLED));
	Lua::registerVariable(L, "configKeys", "BOT_DENSITY_ANCHOR_CLUSTER_RADIUS", static_cast<lua_Number>(BOT_DENSITY_ANCHOR_CLUSTER_RADIUS));
	Lua::registerVariable(L, "configKeys", "BOT_DENSITY_CAP_ENABLED", static_cast<lua_Number>(BOT_DENSITY_CAP_ENABLED));
	Lua::registerVariable(L, "configKeys", "BOT_DENSITY_CAP_INNER_LIMIT_PCT", static_cast<lua_Number>(BOT_DENSITY_CAP_INNER_LIMIT_PCT));
	Lua::registerVariable(L, "configKeys", "BOT_DENSITY_CAP_INNER_RADIUS", static_cast<lua_Number>(BOT_DENSITY_CAP_INNER_RADIUS));
	Lua::registerVariable(L, "configKeys", "BOT_DENSITY_CAP_MID_LIMIT_PCT", static_cast<lua_Number>(BOT_DENSITY_CAP_MID_LIMIT_PCT));
	Lua::registerVariable(L, "configKeys", "BOT_DENSITY_CAP_MID_RADIUS", static_cast<lua_Number>(BOT_DENSITY_CAP_MID_RADIUS));
	Lua::registerVariable(L, "configKeys", "BOT_DENSITY_CAP_OUTER_LIMIT_PCT", static_cast<lua_Number>(BOT_DENSITY_CAP_OUTER_LIMIT_PCT));
	Lua::registerVariable(L, "configKeys", "BOT_DENSITY_CAP_OUTER_RADIUS", static_cast<lua_Number>(BOT_DENSITY_CAP_OUTER_RADIUS));
	Lua::registerVariable(L, "configKeys", "BOT_DWELL_NPC_MAX_SEC", static_cast<lua_Number>(BOT_DWELL_NPC_MAX_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_DWELL_NPC_MIN_SEC", static_cast<lua_Number>(BOT_DWELL_NPC_MIN_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_DWELL_POI_MAX_SEC", static_cast<lua_Number>(BOT_DWELL_POI_MAX_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_DWELL_POI_MIN_SEC", static_cast<lua_Number>(BOT_DWELL_POI_MIN_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_DWELL_POST_TRAVEL_SEC", static_cast<lua_Number>(BOT_DWELL_POST_TRAVEL_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_DWELL_REROLL_MAX_SEC", static_cast<lua_Number>(BOT_DWELL_REROLL_MAX_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_DWELL_REROLL_MIN_SEC", static_cast<lua_Number>(BOT_DWELL_REROLL_MIN_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_FIDGET_CHANCE_PCT", static_cast<lua_Number>(BOT_FIDGET_CHANCE_PCT));
	Lua::registerVariable(L, "configKeys", "BOT_HUNT_TIME_MAX_SEC", static_cast<lua_Number>(BOT_HUNT_TIME_MAX_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_HUNT_TIME_MIN_SEC", static_cast<lua_Number>(BOT_HUNT_TIME_MIN_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_FIDGET_INTERVAL_MAX_SEC", static_cast<lua_Number>(BOT_FIDGET_INTERVAL_MAX_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_FIDGET_INTERVAL_MIN_SEC", static_cast<lua_Number>(BOT_FIDGET_INTERVAL_MIN_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_FIDGET_MAX_ITEM_VALUE_GP", static_cast<lua_Number>(BOT_FIDGET_MAX_ITEM_VALUE_GP));
	Lua::registerVariable(L, "configKeys", "BOT_GANG_ENABLE", static_cast<lua_Number>(BOT_GANG_ENABLE));
	Lua::registerVariable(L, "configKeys", "BOT_GANG_REQUIRE_OBSERVER", static_cast<lua_Number>(BOT_GANG_REQUIRE_OBSERVER));
	Lua::registerVariable(L, "configKeys", "BOT_GANG_TARGET_PLAYERS", static_cast<lua_Number>(BOT_GANG_TARGET_PLAYERS));
	Lua::registerVariable(L, "configKeys", "BOT_GANG_MIN_SIZE", static_cast<lua_Number>(BOT_GANG_MIN_SIZE));
	Lua::registerVariable(L, "configKeys", "BOT_GANG_MAX_SIZE", static_cast<lua_Number>(BOT_GANG_MAX_SIZE));
	Lua::registerVariable(L, "configKeys", "BOT_GANG_RECRUIT_RADIUS", static_cast<lua_Number>(BOT_GANG_RECRUIT_RADIUS));
	Lua::registerVariable(L, "configKeys", "BOT_GANG_VICTIM_BAND", static_cast<lua_Number>(BOT_GANG_VICTIM_BAND));
	Lua::registerVariable(L, "configKeys", "BOT_GANG_STAGE_WINDOW_MS", static_cast<lua_Number>(BOT_GANG_STAGE_WINDOW_MS));
	Lua::registerVariable(L, "configKeys", "BOT_GANG_SCAN_COOLDOWN_MS", static_cast<lua_Number>(BOT_GANG_SCAN_COOLDOWN_MS));
	Lua::registerVariable(L, "configKeys", "BOT_GANG_ODDS_VS_PLAYER", static_cast<lua_Number>(BOT_GANG_ODDS_VS_PLAYER));
	Lua::registerVariable(L, "configKeys", "BOT_GANG_ODDS_VS_BOT", static_cast<lua_Number>(BOT_GANG_ODDS_VS_BOT));
	Lua::registerVariable(L, "configKeys", "BOT_GANG_WALL_CHANCE_PCT", static_cast<lua_Number>(BOT_GANG_WALL_CHANCE_PCT));
	Lua::registerVariable(L, "configKeys", "BOT_GANG_PARALYZE_CHANCE_PCT", static_cast<lua_Number>(BOT_GANG_PARALYZE_CHANCE_PCT));
	Lua::registerVariable(L, "configKeys", "BOT_GANG_VICTIM_COOLDOWN_SEC", static_cast<lua_Number>(BOT_GANG_VICTIM_COOLDOWN_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_PZROAM_ENABLE", static_cast<lua_Number>(BOT_PZROAM_ENABLE));
	Lua::registerVariable(L, "configKeys", "BOT_PZROAM_INTERVAL_MIN_SEC", static_cast<lua_Number>(BOT_PZROAM_INTERVAL_MIN_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_PZROAM_INTERVAL_MAX_SEC", static_cast<lua_Number>(BOT_PZROAM_INTERVAL_MAX_SEC));
	Lua::registerVariable(L, "configKeys", "BOT_PZROAM_STAY_PCT", static_cast<lua_Number>(BOT_PZROAM_STAY_PCT));
	Lua::registerVariable(L, "configKeys", "BOT_MOUNT_CHANCE_PCT", static_cast<lua_Number>(BOT_MOUNT_CHANCE_PCT));
	Lua::registerVariable(L, "configKeys", "BOT_PERSONALITY_REROLL_ON_RESTART", static_cast<lua_Number>(BOT_PERSONALITY_REROLL_ON_RESTART));
	Lua::registerVariable(L, "configKeys", "BOT_PLAYERS_ONLINE", static_cast<lua_Number>(BOT_PLAYERS_ONLINE));
	Lua::registerVariable(L, "configKeys", "BOT_PLAYERS_SHOW_AS_ONLINE", static_cast<lua_Number>(BOT_PLAYERS_SHOW_AS_ONLINE));
	Lua::registerVariable(L, "configKeys", "BOT_POI_CROWD_CAP_COUNT", static_cast<lua_Number>(BOT_POI_CROWD_CAP_COUNT));
	Lua::registerVariable(L, "configKeys", "BOT_POI_CROWD_CAP_RADIUS", static_cast<lua_Number>(BOT_POI_CROWD_CAP_RADIUS));
	Lua::registerVariable(L, "configKeys", "BOT_PROX_BASELINE_WEIGHT", static_cast<lua_Number>(BOT_PROX_BASELINE_WEIGHT));
	Lua::registerVariable(L, "configKeys", "BOT_PROX_BONUS_MID", static_cast<lua_Number>(BOT_PROX_BONUS_MID));
	Lua::registerVariable(L, "configKeys", "BOT_PROX_BONUS_NEAR", static_cast<lua_Number>(BOT_PROX_BONUS_NEAR));
	Lua::registerVariable(L, "configKeys", "BOT_PROX_MID_TILES", static_cast<lua_Number>(BOT_PROX_MID_TILES));
	Lua::registerVariable(L, "configKeys", "BOT_PROX_NEAR_TILES", static_cast<lua_Number>(BOT_PROX_NEAR_TILES));
	Lua::registerVariable(L, "configKeys", "BOT_PROX_SAMPLE_CAP", static_cast<lua_Number>(BOT_PROX_SAMPLE_CAP));
	Lua::registerVariable(L, "configKeys", "BOT_PROX_TRAVEL_CAT_BONUS", static_cast<lua_Number>(BOT_PROX_TRAVEL_CAT_BONUS));
	Lua::registerVariable(L, "configKeys", "BOT_PROX_WEIGHT_AWAKE", static_cast<lua_Number>(BOT_PROX_WEIGHT_AWAKE));
	Lua::registerVariable(L, "configKeys", "BOT_PROX_WEIGHT_ENABLED", static_cast<lua_Number>(BOT_PROX_WEIGHT_ENABLED));
	Lua::registerVariable(L, "configKeys", "BOT_TELEMETRY_ENABLED", static_cast<lua_Number>(BOT_TELEMETRY_ENABLED));
	Lua::registerVariable(L, "configKeys", "BOT_TURN_IN_PLACE_CHANCE_PCT", static_cast<lua_Number>(BOT_TURN_IN_PLACE_CHANCE_PCT));
	Lua::registerVariable(L, "configKeys", "BOT_TURN_IN_PLACE_INTERVAL_TICKS", static_cast<lua_Number>(BOT_TURN_IN_PLACE_INTERVAL_TICKS));
	Lua::registerVariable(L, "configKeys", "BOT_WALK_PAUSE_CHANCE_PCT", static_cast<lua_Number>(BOT_WALK_PAUSE_CHANCE_PCT));
	Lua::registerVariable(L, "configKeys", "BOT_WALK_PAUSE_MAX_MS", static_cast<lua_Number>(BOT_WALK_PAUSE_MAX_MS));
	Lua::registerVariable(L, "configKeys", "BOT_WALK_PAUSE_MAX_PER_ROUTE", static_cast<lua_Number>(BOT_WALK_PAUSE_MAX_PER_ROUTE));
	Lua::registerVariable(L, "configKeys", "BOT_WALK_PAUSE_MIN_MS", static_cast<lua_Number>(BOT_WALK_PAUSE_MIN_MS));
	Lua::registerVariable(L, "configKeys", "BOT_WALK_PAUSE_OBSERVED_CHANCE_PCT", static_cast<lua_Number>(BOT_WALK_PAUSE_OBSERVED_CHANCE_PCT));
	Lua::registerVariable(L, "configKeys", "BOT_WALK_PAUSE_OBSERVED_MAX_MS", static_cast<lua_Number>(BOT_WALK_PAUSE_OBSERVED_MAX_MS));
	Lua::registerVariable(L, "configKeys", "BOT_WALK_PAUSE_OBSERVED_MAX_PER_ROUTE", static_cast<lua_Number>(BOT_WALK_PAUSE_OBSERVED_MAX_PER_ROUTE));
	Lua::registerVariable(L, "configKeys", "BOT_WALK_PAUSE_OBSERVED_MIN_MS", static_cast<lua_Number>(BOT_WALK_PAUSE_OBSERVED_MIN_MS));
	Lua::registerVariable(L, "configKeys", "BOT_WORLD_CHAT_INTERVAL_MAX_MS", static_cast<lua_Number>(BOT_WORLD_CHAT_INTERVAL_MAX_MS));
	Lua::registerVariable(L, "configKeys", "BOT_WORLD_CHAT_INTERVAL_MIN_MS", static_cast<lua_Number>(BOT_WORLD_CHAT_INTERVAL_MIN_MS));
	Lua::registerVariable(L, "configKeys", "CAST_ENABLED", static_cast<lua_Number>(CAST_ENABLED));
	Lua::registerVariable(L, "configKeys", "CAST_MAX_VIEWERS", static_cast<lua_Number>(CAST_MAX_VIEWERS));
	Lua::registerVariable(L, "configKeys", "CAST_MAX_VIEWERS_PER_IP", static_cast<lua_Number>(CAST_MAX_VIEWERS_PER_IP));
	Lua::registerVariable(L, "configKeys", "CAST_OPERATOR_PASSWORD", static_cast<lua_Number>(CAST_OPERATOR_PASSWORD));

}

int ConfigFunctions::luaConfigManagerGetString(lua_State* L) {
	const auto key = Lua::getNumber<ConfigKey_t>(L, -1);
	if (!key) {
		Lua::reportErrorFunc("Wrong enum");
		return 1;
	}

	Lua::pushString(L, g_configManager().getString(Lua::getNumber<ConfigKey_t>(L, -1)));
	return 1;
}

int ConfigFunctions::luaConfigManagerGetNumber(lua_State* L) {
	const auto key = Lua::getNumber<ConfigKey_t>(L, -1);
	if (!key) {
		Lua::reportErrorFunc("Wrong enum");
		return 1;
	}

	lua_pushnumber(L, g_configManager().getNumber(Lua::getNumber<ConfigKey_t>(L, -1)));
	return 1;
}

int ConfigFunctions::luaConfigManagerGetBoolean(lua_State* L) {
	const auto key = Lua::getNumber<ConfigKey_t>(L, -1);
	if (!key) {
		Lua::reportErrorFunc("Wrong enum");
		return 1;
	}

	Lua::pushBoolean(L, g_configManager().getBoolean(Lua::getNumber<ConfigKey_t>(L, -1)));
	return 1;
}

int ConfigFunctions::luaConfigManagerGetFloat(lua_State* L) {
	// configManager.getFloat(key, shouldRound = true)

	// Ensure the first argument (key) is provided and is a valid enum
	const auto key = Lua::getNumber<ConfigKey_t>(L, 1);
	if (!key) {
		Lua::reportErrorFunc("Wrong enum");
		return 1;
	}

	// Check if the second argument (shouldRound) is provided and is a boolean; default to true if not provided
	bool shouldRound = Lua::getBoolean(L, 2, true);
	float value = g_configManager().getFloat(key);
	double finalValue = shouldRound ? static_cast<double>(std::round(value * 100.0) / 100.0) : value;

	g_logger().debug("[{}] key: {}, finalValue: {}, shouldRound: {}", __FUNCTION__, magic_enum::enum_name(key), finalValue, shouldRound);
	lua_pushnumber(L, finalValue);
	return 1;
}
