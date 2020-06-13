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

	for(size_t i = 0ULL; i < m_values.size() - 1ULL; ++i)
	{
		const auto& [key, value] = m_values[i];
		fmt::format_to(buff, "\t\"{}\": {},\n", key, value);
	}

	const auto& [last_key, last_value] = m_values.back();
	fmt::format_to(buff, "\t\"{}\": {}\n{}", last_key, last_value, '}');

	return fmt::to_string(buff);
}

}	 // namespace OK
