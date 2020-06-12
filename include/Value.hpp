#pragma once

#include "Utility.hpp"

#include <fmt/core.h>
#include <string>

namespace OK
{
class Object;
class Array;

// Maybe get rid of Empty, and just start everything with Undefined
enum class Type : uint8_t
{
	Empty,
	Undefined,
	Null,
	Integer,
	Double,
	Boolean,
	String,
	Object,
	Array
};

class Value final
{
public:
	using ValueType = union {
		int64_t m_integer;
		double m_double;
		bool m_boolean;
		// Maybe shared_ptr?
		std::string* m_string;
		Object* m_object;
		Array* m_array;
	};

	Value() : m_type(Type::Empty) {}

	// Setters
	Value(const long long value) : m_type(Type::Integer) { m_value.m_integer = value; }
	Value(const int64_t value) : m_type(Type::Integer) { m_value.m_integer = value; }
	Value(const unsigned long long value) : m_type(Type::Integer)
	{
		m_value.m_integer = static_cast<int64_t>(value);
	}
	Value(const uint64_t value) : m_type(Type::Integer)
	{
		m_value.m_integer = static_cast<int64_t>(value);
	}

	Value(const int32_t value) : m_type(Type::Integer) { m_value.m_integer = value; }
	Value(const uint32_t value) : m_type(Type::Integer)
	{
		m_value.m_integer = static_cast<int64_t>(value);
	}
	Value(const int16_t value) : m_type(Type::Integer) { m_value.m_integer = value; }
	Value(const uint16_t value) : m_type(Type::Integer)
	{
		m_value.m_integer = static_cast<int64_t>(value);
	}

	Value(const float value) : m_type(Type::Double) { m_value.m_double = value; }
	Value(const double value) : m_type(Type::Double) { m_value.m_double = value; }

	Value(const bool value) : m_type(Type::Boolean) { m_value.m_boolean = value; }

	Value(std::string* value) : m_type(Type::String) { m_value.m_string = value; }

	Value(Object* value) : m_type(Type::Object) { m_value.m_object = value; }

	Value(Array* value) : m_type(Type::Array) { m_value.m_array = value; }

	Value(const Type type) : m_type(type) {}

	// Getters
	Type type() const { return m_type; }

	ValueType& value() { return m_value; }
	const ValueType& value() const { return m_value; }

	int64_t as_int() const { return m_value.m_integer; }
	double as_double() const { return m_value.m_double; }
	bool as_bool() const { return m_value.m_boolean; }
	std::string& as_string() { return *m_value.m_string; }
	const std::string& as_string() const { return *m_value.m_string; }
	Object& as_object() { return *m_value.m_object; }
	const Object& as_object() const { return *m_value.m_object; }
	Array& as_array() { return *m_value.m_array; }
	const Array& as_array() const { return *m_value.m_array; }

	// TODO: Make everything noexcept
	// Inline these?
	bool is_empty() const { return m_type == Type::Empty; }
	bool has_value() const { return m_type != Type::Empty; }

	bool is_null() const { return m_type == Type::Null; }
	bool is_undefined() const { return m_type == Type::Undefined; }
	bool is_number() const { return (m_type == Type::Integer || m_type == Type::Double); }
	bool is_bool() const { return m_type == Type::Boolean; }
	bool is_string() const { return m_type == Type::String; }
	bool is_object() const { return m_type == Type::Object; }
	bool is_array() const { return m_type == Type::Array; }

	Value value_or(const Value other)
	{
		if(is_empty())
			return other;
		return *this;
	}

	bool to_bool() const
	{
		switch(m_type)
		{
			// using enum Type;
			case Type::Boolean: return m_value.m_boolean;
			case Type::Null: [[fallthrough]];
			case Type::Undefined: [[fallthrough]];
			case Type::Empty: return false;
			case Type::Integer: return m_value.m_integer != 0LL;
			case Type::Double: return feq(m_value.m_double, 0.0);
			case Type::String:
			{
				return [this]() -> bool {
					if(!m_value.m_string || m_value.m_string->empty())
						return false;
					return true;
				}();
			}
			case Type::Object: /* TODO: Do a proper check maybe? */
			{
				return m_value.m_object != nullptr;
			}
			case Type::Array:
				// FIXME: Both Object and Array should also check if they're empty
				return m_value.m_array != nullptr;
			default:
				// LOL What? Why are you here? Maybe assert()?
				break;
		}
	}

	std::string to_string() const;

private:
	Type m_type {Type::Empty};

	ValueType m_value;
};

Value from_string(const std::string& str);

Value from_object(const Object& obj);

Value from_array(const Array& arr);

inline Value undefined() { return Value(Type::Undefined); }

inline Value null() { return Value(Type::Null); }

}	 // namespace OK

template<>
struct fmt::formatter<OK::Value>
{
	constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const OK::Value& val, FormatContext& fc)
	{
		return format_to(fc.out(), "{}", val.to_string());
	}
};
