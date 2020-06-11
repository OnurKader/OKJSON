#include "Object.hpp"
#include "Parser.hpp"
#include "Utility.hpp"

#include <cstdlib>
#include <fmt/format.h>
#include <fstream>
#include <string>

std::string read_file_and_strip_whitespace(const char*);

int main()
{
	const std::string json_data = read_file_and_strip_whitespace("easy.json");

	fmt::print("Read JSON as:\n{}\n", json_data);

	OK::Parser parser(json_data);

	OK::Object json_object = parser.parse();
	fmt::print("Parsed Object:\n{}\n", json_object);

	return 0;
}

std::string remove_whitespace_if_not_in_quote(const std::array<char, 128ULL>& arr,
											  const bool was_in_quotes = false)
{
	std::string result(std::strlen(arr.data()), '\0');
	for(const char chr: arr)
	{
		// TODO: Determine if in quotes, then just if(std::isspace(chr)) not push?
	}

	return result;
}

std::string read_file_and_strip_whitespace(const char* filename)
{
	/*
	 * TODO:
	 * Get filesize using seekg(0, std::ios_base::end) and tellg(), reserve space
	 * Read in a buffer or 128 or 256 maybe, push that into the string
	 * When reading the buffer, get rid of whitespace (keep a boolean so if it's the second batch
	 * -second buffer read- it knows if it's in a quoted string or not). Also keep a count of the
	 * quotes as you read
	 */
	std::ifstream json_file {filename};
	if(!json_file)
	{
		fmt::print(stderr, "Couldn't open file\n");
		std::exit(1);
	}
	json_file.seekg(0, std::ios_base::end);
	const size_t file_size = static_cast<size_t>(json_file.tellg());
	json_file.seekg(0);

	std::array<char, 128ULL> buff;
	bool was_in_quotes = false;

	while(json_file.good())
	{
		json_file.read(buff.data(), 128ULL);
	}

	std::string result(file_size, '\0');

	return result;
}
