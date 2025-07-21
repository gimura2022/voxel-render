#ifndef _basic_parser_hpp
#define _basic_parser_hpp

#include <string>
#include <sys/types.h>

#include "defs.hpp"
#include "utils.hpp"

namespace parse {

template<typename char_t = char_t>
class BasicParser {
protected:
	using parser_str_t       = std::basic_string<char_t>;
	using parser_str_view_t  = std::basic_string_view<char_t>;
	using parser_strstream_t = std::basic_stringstream<char_t>;

public:
	explicit inline BasicParser(parser_str_view_t source)
		: source(source) {}

protected:
	char_t peek()
	{
		return source[glob_pos];
	}

	parser_str_view_t peek(uint_t n)
	{
		return source.substr(glob_pos, n);
	}

	void skip(uint_t n)
	{
		for (auto i = 0; i < n; i++) {
			glob_pos++;

			char_t c = peek();

			if (c == '\n') {
				pos = 0;
				line++;
			} else if (c == '\0')
				return;
			else
				pos++;
		}
	}

	void skip()
	{
		skip(1);
	}
	
	void skip_line()
	{
		char_t c;

		while ((c = take()) != '\n');
	}

	char_t take()
	{
		char_t c = peek();
		skip();

		return c;
	}

	parser_str_view_t take(uint_t n)
	{
		parser_str_view_t s = peek(n);
		skip(n);

		return s;
	}

	char_t next()
	{
		return source[glob_pos + 1];
	}

	parser_str_view_t next(uint_t n)
	{
		return source.substr(glob_pos + 1, n);
	}

	bool next_is(char_t c)
	{
		return next() == c;
	}

	bool next_is(parser_str_view_t s)
	{
		return next(s.length()) == s;
	}

	template<typename T>
	void except(T v)
	{
		if (!next_is(v))
			utils::error("unexepted input");
	}

	uint_t get_line_length()
	{
		uint_t size = 0;
		char_t c;

		while ((c = take()) != '\n')
			size++;

		return size;
	}

	parser_str_view_t peek_line()
	{
		return peek(get_line_length());
	}

	parser_str_view_t take_line()
	{
		parser_str_view_t s = peek_line();
		skip_line();

		return s;
	}

	bool is_contains_next_line()
	{
		for (uint_t i = glob_pos; ; i++) {
			if (source[i] == '\n')
				return true;

			if (source[i] == '\0')
				return false;
		}
	}

	parser_str_view_t source;
	uint_t glob_pos, pos, line;
};

};

#endif
