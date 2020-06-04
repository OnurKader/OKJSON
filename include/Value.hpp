#pragma once

#include <fmt/core.h>
#include <string>

namespace OK
{
class Object;

enum class Type : uint8_t
{
	Empty,
	Undefined,
	Null,
	Integer,
	Double,
	String,
	Object,
	Boolean
};

class Value final
{
public:
	Value() : m_type(Type::Empty) {}

	// Setters
	explicit Value(const int64_t value) : m_type(Type::Integer) { m_value.m_integer = value; }
	explicit Value(const uint64_t value) : m_type(Type::Integer)
	{
		m_value.m_integer = static_cast<int64_t>(value);
	}
	explicit Value(const int32_t value) : m_type(Type::Integer) { m_value.m_integer = value; }
	explicit Value(const uint32_t value) : m_type(Type::Integer)
	{
		m_value.m_integer = static_cast<int64_t>(value);
	}
	explicit Value(const int16_t value) : m_type(Type::Integer) { m_value.m_integer = value; }
	explicit Value(const uint16_t value) : m_type(Type::Integer)
	{
		m_value.m_integer = static_cast<int64_t>(value);
	}

	explicit Value(const float value) : m_type(Type::Double) { m_value.m_double = value; }
	explicit Value(const double value) : m_type(Type::Double) { m_value.m_double = value; }

	explicit Value(const bool value) : m_type(Type::Boolean) { m_value.m_boolean = value; }

	explicit Value(std::string* value) : m_type(Type::String) { m_value.m_string = value; }

	explicit Value(Object* value) : m_type(Type::Object) { m_value.m_object = value; }

	explicit Value(const Type type) : m_type(type) {}

	// Getters
	Type type() const { return m_type; }

	int64_t as_int() const { return m_value.m_integer; }
	double as_double() const { return m_value.m_double; }
	bool as_bool() const { return m_value.m_boolean; }
	std::string& as_string() { return *m_value.m_string; }
	const std::string& as_string() const { return *m_value.m_string; }
	Object& as_object() { return *m_value.m_object; }
	const Object& as_object() const { return *m_value.m_object; }

	bool empty() const { return m_type == Type::Empty; }
	bool has_value() const { return m_type == Type::Empty; }

	Value value_or(const Value other)
	{
		if(empty())
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
			case Type::Double: return m_value.m_double != 0.0;
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
			default:
				// LOL What? Why are you here? Maybe assert()?
				break;
		}
	}

	/*
	int64_t to_int() const {
	}	 // TODO: What about Object? Or what return value if null or smth? -INT64_MAX?
	*/

	std::string to_string() const
	{
		switch(m_type)
		{
			case Type::Integer: return fmt::format("{}", m_value.m_integer);
			case Type::Double: return fmt::format("{}", m_value.m_double);
			case Type::Boolean: return fmt::format("{}", m_value.m_boolean);
			case Type::String: return fmt::format("{}", *m_value.m_string);
			case Type::Object:
				return "Object";	// FIXME: Do the actual printing by calling
									// m_value.m_object.dump() or .to_string()
			case Type::Null: return "null";
			case Type::Undefined: return "undefined";
			default: return {};
		}
	}

private:
	Type m_type {Type::Empty};
	union {
		int64_t m_integer;
		double m_double;
		bool m_boolean;
		// Maybe shared_ptr?
		std::string* m_string;
		Object* m_object;
	} m_value;
};

Value undefined() { return Value(Type::Undefined); }
Value null() { return Value(Type::Null); }

}	 // namespace OK

// TODO: fmt formatter for value
