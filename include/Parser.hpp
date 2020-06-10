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

private:
	std::string_view m_str;
};
}	 // namespace OK
