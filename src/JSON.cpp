#include "Utility.hpp"

#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fstream>
#include <string>

int main()
{
	std::ifstream test_json {"test.json"};
	if(!test_json)
	{
		fmt::print(stderr, "Couldn't open file\n");
		return 1;
	}
	std::string json_data {std::istream_iterator<char>(test_json), std::istream_iterator<char>()};

	fmt::print("{}\n", json_data);

	return 0;
}
