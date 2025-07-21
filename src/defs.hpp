#ifndef _defs_hpp
#define _defs_hpp

#include <cstdint>
#include <sstream>
#include <string>
#include <string_view>

using char_t = char;

using str_t       = std::basic_string<char_t>;
using str_view_t  = std::basic_string_view<char_t>;
using strstream_t = std::basic_stringstream<char_t>;

using uint_t = std::uint64_t;

#endif
