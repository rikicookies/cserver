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

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "lib/di/container.hpp"

LogWithSpdLog::LogWithSpdLog() {
	// Async thread pool: 8192 queue slots, 1 background writer thread
	spdlog::init_thread_pool(8192, 1);

	auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	auto async_logger = std::make_shared<spdlog::async_logger>(
		"async_default",
		stdout_sink,
		spdlog::thread_pool(),
		spdlog::async_overflow_policy::overrun_oldest
	);
	spdlog::set_default_logger(async_logger);

	setLevel("info");
	spdlog::set_pattern("[%Y-%d-%m %H:%M:%S.%e] [%^%l%$] %v ");
	spdlog::flush_on(spdlog::level::warn);
	spdlog::flush_every(std::chrono::seconds(3));

#ifdef DEBUG_LOG
	spdlog::set_pattern("[%Y-%d-%m %H:%M:%S.%e] [thread %t] [%^%l%$] %v ");
#endif
}

Logger &LogWithSpdLog::getInstance() {
	return inject<Logger>();
}

void LogWithSpdLog::setLevel(const std::string &name) const {
	debug("Setting log level to: {}.", name);
	const auto level = spdlog::level::from_str(name);
	spdlog::set_level(level);
}

std::string LogWithSpdLog::getLevel() const {
	const auto level = spdlog::level::to_string_view(spdlog::get_level());
	return std::string { level.begin(), level.end() };
}

void LogWithSpdLog::info(const std::string &msg) const {
	SPDLOG_INFO(msg);
}

void LogWithSpdLog::warn(const std::string &msg) const {
	SPDLOG_WARN(msg);
}

void LogWithSpdLog::error(const std::string &msg) const {
	SPDLOG_ERROR(msg);
}

void LogWithSpdLog::critical(const std::string &msg) const {
	SPDLOG_CRITICAL(msg);
}

#if defined(DEBUG_LOG)
void LogWithSpdLog::debug(const std::string &msg) const {
	SPDLOG_DEBUG(msg);
}

void LogWithSpdLog::trace(const std::string &msg) const {
	SPDLOG_TRACE(msg);
}
#endif
