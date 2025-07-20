#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

#include "colors.hpp"
#include "logger.hpp"
#include "defs.hpp"
#include "utils.hpp"

namespace logger {

std::ofstream Logger::log_file;

LogMessage::~LogMessage()
{
	logger->log(level, ss.str());
}

void Logger::init(std::filesystem::path&& log_file_name)
{
	log_file = std::ofstream(log_file_name);

	if (!log_file.is_open())
		utils::error("can't initialize logger");
}

void Logger::log(LogLevel level, str_view_t msg)
{
	auto display_meta = [] (auto color, str_view_t meta) -> void {
		std::cout << BACKETS_COLOR << "[" << color << colors::italic << meta <<
			colors::reset << BACKETS_COLOR << "]";
		log_file << "[" << meta << "]";
	};

	display_meta(CONTENT_COLOR, name);

	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::stringstream ss;
	ss << std::put_time(&tm, TIME_FMT);

	display_meta(CONTENT_COLOR, ss.str());

	switch (level) {
	case LogLevel::Trace:
		display_meta(TRACE_COLOR, "trace");
		break;

	case LogLevel::Debug:
		display_meta(DEBUG_COLOR, "debug");
		break;

	case LogLevel::Info:
		display_meta(INFO_COLOR, "info");
		break;

	case LogLevel::Warn:
		display_meta(WARN_COLOR, "warn");
		break;

	case LogLevel::Error:
		display_meta(ERROR_COLOR, "error");
		break;
	}

	std::cout << " " << CONTENT_COLOR << msg << std::endl;
	log_file << " " << msg << std::endl;
}

};
