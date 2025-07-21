#ifndef _glsl_include_preprocessor_hpp
#define _glsl_include_preprocessor_hpp

#include <filesystem>

#include "basic_parser.hpp"

namespace parse {

class GlslIncudePreprocessor : public BasicParser<> {
public:
	inline GlslIncudePreprocessor(std::filesystem::path&& file, parser_str_view_t source)
		: BasicParser<>(source), file(file) {}

	parser_str_t preprocess();

private:
	std::filesystem::path file;
};

};

#endif
