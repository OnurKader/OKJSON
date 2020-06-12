#include "Object.hpp"

namespace OK
{
Value& Object::get(const std::string& property_name)
{
	const auto iter = find_property_in_vector(property_name);
	assert(("Couldn't find property in object", iter != m_values.end()));
	return iter->second;
}

const Value& Object::get(const std::string& property_name) const
{
	const auto iter = find_property_in_vector(property_name);
	assert(("Couldn't find property in object", iter != m_values.end()));
	return iter->second;
}

std::string Object::to_string() const
{
	fmt::memory_buffer buff;
	// TODO: Find a more sensible average for reserve
	buff.reserve(64ULL);

	fmt::format_to(buff, "{}\n", '{');

	for(const auto& [key, value]: m_values)
	{
		// FIXME: Object printing, somehow keep the tab info, the depth/level
		fmt::format_to(buff, "\t\"{}\": {},\n", key, value);
	}

	fmt::format_to(buff, "{}", '}');

	return fmt::to_string(buff);
}

}	 // namespace OK
