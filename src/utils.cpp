#include <fstream>
#include <string>

#include "utils.hpp"
#include "defs.hpp"

namespace utils {

str_t read_file(std::filesystem::path&& path)
{
	std::ifstream file(path);

	if (!file.is_open())
		error("can't open " + path.string());

	strstream_t ss;
	ss << file.rdbuf();

	return ss.str();
}

};

