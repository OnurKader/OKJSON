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

	const std::string json_data {std::istream_iterator<char>(json_file),
								 std::istream_iterator<char>()};

	fmt::print("{}\n", json_data);

	OK::Parser parser(json_data);

	OK::Object json_object = parser.parse();
	fmt::print("Parsed Object:\n{}\n", json_object);

	/*
	OK::Object obj;
	obj.set("OwO", 12);
	obj.set("yeah", 3.141526);

	fmt::print("Obj:\n{}\n", obj.to_string());
	*/

	return 0;
}
