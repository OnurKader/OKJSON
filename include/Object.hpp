#pragma once

#include "Array.hpp"
#include "Value.hpp"

#include <cassert>
#include <vector>

namespace OK
{
class Object final
{
public:
	// FIXME: Do not emplace_back, check if vector already contains it, if so update, otherwise
	// emplace_back
	void set(const std::string property_name, const Value value)
	{
		free_memory_if_pointer(property_name);
		m_values.emplace_back(property_name, value);
	}

	void set(const std::string_view property_name, const Value value)
	{
		std::string property_name_(property_name);
		free_memory_if_pointer(property_name_);
		m_values.emplace_back(property_name_, value);
	}

	void set(const std::string property_name, const std::string str)
	{
		free_memory_if_pointer(property_name);
		std::string* wow_this_code_sucks = new std::string(str);
		m_values.emplace_back(property_name, Value(wow_this_code_sucks));
	}

	void set(const std::string property_name, const Object obj)
	{
		free_memory_if_pointer(property_name);
		Object* wow_this_sucks_as_well = new Object(obj);
		m_values.emplace_back(property_name, Value(wow_this_sucks_as_well));
	}

	Value& get(const std::string& property_name);

	const Value& get(const std::string& property_name) const;

	Value& operator[](const std::string& property_name) { return get(property_name); }
	const Value& operator[](const std::string& property_name) const { return get(property_name); }

	auto begin() const { return m_values.begin(); }

	std::string to_string() const;

private:
	using ObjectType = std::vector<std::pair<std::string, Value>>;
	ObjectType m_values {};

	ObjectType::iterator find_property_in_vector(const std::string& property_name)
	{
		return std::find_if(m_values.begin(), m_values.end(), [&property_name](const auto& pair) {
			return pair.first == property_name;
		});
	}

	ObjectType::const_iterator find_property_in_vector(const std::string& property_name) const
	{
		return std::find_if(m_values.cbegin(), m_values.cend(), [&property_name](const auto& pair) {
			return pair.first == property_name;
		});
	}

	bool vector_contains_property(const std::string& property_name) const
	{
		return (find_property_in_vector(property_name) != m_values.cend());
	}

	void free_memory_if_pointer(const std::string& property_name)
	{
		if(vector_contains_property(property_name))
		{
			Value& temp = get(property_name);
			// FIXME: Actually bring back ~Value(), or have operator= overloaded to do this so if we
			// reassign a Value, it's not leaked
			switch(temp.type())
			{
				case Type::String: delete temp.value().m_string; break;
				case Type::Object: delete temp.value().m_object; break;
				case Type::Array: delete temp.value().m_array; break;
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
