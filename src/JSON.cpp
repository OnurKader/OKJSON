#include "Parser.hpp"

#include <fmt/format.h>
#include <fstream>
#include <string>

int main()
{
	std::ifstream json_file("array.json");
	if(!json_file)
	{
		fmt::print(stderr, "Couldn't open JSON\n");
		return 1;
	}

	json_file.seekg(0, std::ios::end);
	const size_t file_size = static_cast<size_t>(json_file.tellg());
	json_file.seekg(0, std::ios::beg);

	std::string json_data(file_size, '\0');

	json_file.read(json_data.data(), static_cast<ssize_t>(file_size));

	fmt::print("Read JSON as:\n\033[36;1m{}\033[m\n", json_data);

	OK::Object json_object = OK::Parser::parse(json_data).value_or(OK::Object());
	fmt::print("\nParsed Object:\n\033[32;1m{}\033[m\n", json_object);

	return 0;
}
