#pragma once

#include "Value.hpp"

#include <vector>

namespace OK
{
// Inherits from Object?
class Array final
{
public:
private:
	std::vector<Value> m_values;
};

}	 // namespace OK
