#pragma once

#include "Property.hpp"
#include "Value.hpp"

#include <unordered_map>
#include <vector>

namespace OK
{
class Object final
{
public:
	void set(const Property property_name, const Value value)
	{
		m_value_map[property_name] = value;
	}

	void set(const Property property_name, const std::string str)
	{
		std::string* wow_this_code_sucks = new std::string(str);
		m_value_map[property_name] = Value(wow_this_code_sucks);
	}

	void set(const Property property_name, const Object obj)
	{
		Object* wow_this_sucks_as_well = new Object(obj);
		m_value_map[property_name] = Value(wow_this_sucks_as_well);
	}

	Value& get(const Property property_name) { return m_value_map.at(property_name); }
	const Value& get(const Property property_name) const { return m_value_map.at(property_name); }

	Value& operator[](const Property property_name) { return get(property_name); }
	const Value& operator[](const Property property_name) const { return get(property_name); }

	std::string to_string() const;

private:
	std::unordered_map<Property, Value> m_value_map {};
};
}	 // namespace OK
