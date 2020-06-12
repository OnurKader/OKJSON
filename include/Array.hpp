#pragma once

#include "Value.hpp"

#include <initializer_list>
#include <vector>

namespace OK
{
class Array final
{
public:
	// MAYBE: a variadic template?
	Array(const std::initializer_list<Value>);
	Array(std::vector<Value>&&);

	void push(const Value);
	void push(Value&&);

	Value pop();

	std::vector<Value>& vector();
	const std::vector<Value>& vector() const;

	void clear();

	Value& operator[](const size_t);
	const Value& operator[](const size_t) const;

	std::string to_string() const;

private:
	std::vector<Value> m_values;
};

}	 // namespace OK

template<>
struct fmt::formatter<OK::Array>
{
	constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const OK::Array& arr, FormatContext& fc)
	{
		return format_to(fc.out(), "{}", arr.to_string());
	}
};
