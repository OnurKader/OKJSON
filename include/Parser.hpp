#pragma once

#include "Object.hpp"
#include "Value.hpp"

#include <string_view>

namespace OK
{
class Parser final
{
public:
	Parser(const std::string& str) : m_str(str) {}

	Object parse();
	Value parse_value(const std::string_view);

private:
	std::string_view m_str;

	// Make these std::optional?
	static int64_t parse_int(const std::string_view);
	static double parse_double(const std::string_view);
	static bool parse_bool(const std::string_view);
	static std::string* parse_string(const std::string_view);
	static Object* parse_object(const std::string_view);
	static Array* parse_array(const std::string_view);

	static bool is_valid_int(const std::string_view);
	static bool is_valid_double(const std::string_view);
	static bool is_valid_bool(const std::string_view);
	static bool is_valid_string(const std::string_view);
	static bool is_valid_object(const std::string_view);
	static bool is_valid_array(const std::string_view);
};
}	 // namespace OK
