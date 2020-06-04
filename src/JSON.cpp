#include "Args.hpp"

#include <fmt/format.h>

int main(int argc, char** argv)
{
	Args arg_parser;
	arg_parser.options.positional_help("FILE");
	const auto result = arg_parser.parse(argc, argv);
	if(result.count("help"))
		fmt::print(stderr, arg_parser.options.help());

	return 0;
}
