#ifndef _utils_hpp
#define _utils_hpp

#include <cstdlib>
#include <filesystem>
#include <iostream>

#include "defs.hpp"
#include "logger.hpp"

namespace utils {

inline void error(str_view_t string)
{
	static logger::Logger logger("error-logger");

	logger.error() << string;
	std::exit(-1);
}

str_t read_file(std::filesystem::path&& path);

};

#endif
