#include <sstream>

#include "glsl_include_preprocessor.hpp"
#include "defs.hpp"
#include "logger.hpp"

static logger::Logger logg("glsl-include-logger");

namespace parse {

GlslIncudePreprocessor::parser_str_t GlslIncudePreprocessor::preprocess()
{
	logg.info() << "preprocessing file at " << file;

	parser_str_t out;

	while (is_contains_next_line()) {
		if (next_is("#include")) {
			logg.trace() << "found include directive at " << line;
		} else
			out += take_line();
	}

	return std::move(out);
}

};
