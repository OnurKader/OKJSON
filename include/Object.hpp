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
	// FIXME: delete all the shit you've allocated when setting
	void set(const Property property_name, const Value value)
	{
		free_memory_if_pointer(property_name);
		m_value_map[property_name] = value;
	}

	void set(const Property property_name, const std::string str)
	{
		free_memory_if_pointer(property_name);
		std::string* wow_this_code_sucks = new std::string(str);
		m_value_map[property_name] = Value(wow_this_code_sucks);
	}

	void set(const Property property_name, const Object obj)
	{
		free_memory_if_pointer(property_name);
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

	void free_memory_if_pointer(const Property property_name)
	{
		if(m_value_map.contains(property_name))
		{
			Value& temp = m_value_map[property_name];
			switch(temp.type())
			{
				case Type::String: delete temp.value().m_string; break;
				case Type::Object: delete temp.value().m_object; break;
				default: break;
			}
		}
	}
};
}	 // namespace OK

template<>
struct fmt::formatter<OK::Object>
{
	constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const OK::Object& obj, FormatContext& fc)
	{
		return format_to(fc.out(), "{}", obj.to_string());
	}
};
