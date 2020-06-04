#include "Args.hpp"

Args::Args() : options("OKJSON", "A bad JSON parser made for learning")
{
	options.add_options()("h,help", "Print this screen")("f,file", "File to parse");
	options.parse_positional({"file"});
}

cxxopts::ParseResult Args::parse(int& argc, char**& argv) { return options.parse(argc, argv); }
