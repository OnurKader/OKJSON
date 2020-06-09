#include "Object.hpp"
#include "Utility.hpp"
#include "Value.hpp"

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fstream>
#include <string>

int main()
{
	std::ifstream test_json {"easy.json"};
	if(!test_json)
	{
		fmt::print(stderr, "Couldn't open file\n");
		return 1;
	}

	const std::string json_data {std::istream_iterator<char>(test_json),
								 std::istream_iterator<char>()};

	fmt::print("{}\n", json_data);
	OK::Object obj;
	obj.set("OwO", 12);
	obj.set("yeah", 3.141526);

	fmt::print("Obj: {}\n", obj.to_string());

	return 0;
}
