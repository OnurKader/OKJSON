#pragma once

#include "Object.hpp"
#include "Value.hpp"

#include <optional>
#include <string_view>

namespace OK
{
class Parser final
{
public:
	Parser(const std::string& str) : m_str(str) {}

	Object parse();
	static Value parse_value(const std::string_view);

private:
	std::string_view m_str;

	static std::optional<int64_t> parse_int(const std::string_view);
	static std::optional<double> parse_double(const std::string_view);
	static std::optional<bool> parse_bool(const std::string_view);
	// I could just return nullptr for these if they are invalid but fuck it
	static std::optional<std::string*> parse_string(const std::string_view);
	static std::optional<Object*> parse_object(const std::string_view);
	static std::optional<Array*> parse_array(const std::string_view);
};
}	 // namespace OK
