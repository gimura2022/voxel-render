#ifndef _utils_hpp
#define _utils_hpp

#include <cstdlib>
#include <iostream>
#include <string>

using str_t = std::basic_string<char>;

inline void error(str_t&& string)
{
	std::cerr << string << std::endl;
	std::exit(-1);
}

#endif
