#include "Object.hpp"

namespace OK
{
std::string Object::to_string() const
{
	fmt::memory_buffer buff;
	// TODO: Find a more sensible average for reserve
	buff.reserve(64ULL);

	fmt::format_to(buff, "{}\n", '{');

	for(const auto& [key, value]: m_value_map)
	{
		// FIXME: Object printing, somehow keep the tab info, the depth/level
		fmt::format_to(buff, "\t\"{}\": {},\n", key, value);
	}

	fmt::format_to(buff, "{}", '}');

	return fmt::to_string(buff);
}

}	 // namespace OK
