#include "Object.hpp"
#include "Parser.hpp"
#include "Utility.hpp"

#include <fmt/format.h>
#include <fstream>
#include <string>

int main()
{
	std::ifstream json_file {"easy.json"};
	if(!json_file)
	{
		fmt::print(stderr, "Couldn't open file\n");
		return 1;
	}

	// FIXME: Get rid of whitespace some other way, this also affects strings
	const std::string json_data {std::istream_iterator<char>(json_file),
								 std::istream_iterator<char>()};

	fmt::print("{}\n", json_data);

	OK::Parser parser(json_data);

	OK::Object json_object = parser.parse();
	fmt::print("Parsed Object:\n{}\n", json_object);

	return 0;
}
