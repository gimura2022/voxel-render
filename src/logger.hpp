#ifndef _logger_hpp
#define _logger_hpp

#include <filesystem>
#include <fstream>
#include <sstream>

#include "colors.hpp"
#include "defs.hpp"

namespace logger {

enum class LogLevel {
	Trace,
	Debug,
	Info,
	Warn,
	Error,
};

class Logger;

class LogMessage {
public:
	inline LogMessage(Logger* logger, LogLevel level)
		: logger(logger), level(level) {}
	~LogMessage();

	template<typename T>
	inline LogMessage& operator <<(const T& value)
	{
		ss << value;
		return *this;
	}

private:
	Logger* logger;
	LogLevel level;

	std::stringstream ss;
};

class Logger {
public:
	static inline constexpr auto TIME_FMT = "%d-%m-%Y %H-%M-%S";

	static inline constexpr auto BACKETS_COLOR = colors::bright_grey;
	static inline constexpr auto CONTENT_COLOR = colors::white;

	static inline constexpr auto TRACE_COLOR = colors::cyan;
	static inline constexpr auto DEBUG_COLOR = colors::bright_blue;
	static inline constexpr auto INFO_COLOR  = colors::bright_green;
	static inline constexpr auto WARN_COLOR  = colors::bright_yellow;
	static inline constexpr auto ERROR_COLOR = colors::bright_red;

	inline Logger(str_view_t name)
		: name(name) {}

	static void init(std::filesystem::path&& log_file);

	void log(LogLevel level, str_view_t msg);

	inline LogMessage trace()
	{
		return LogMessage(this, LogLevel::Trace);
	}

	inline LogMessage debug()
	{
		return LogMessage(this, LogLevel::Debug);
	}

	inline LogMessage info()
	{
		return LogMessage(this, LogLevel::Info);
	}

	inline LogMessage warn()
	{
		return LogMessage(this, LogLevel::Warn);
	}

	inline LogMessage error()
	{
		return LogMessage(this, LogLevel::Error);
	}

private:
	static std::ofstream log_file;

	str_view_t name;
};

}

#endif
