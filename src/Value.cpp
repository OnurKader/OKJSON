#include "Value.hpp"

#include "Object.hpp"

namespace OK
{
inline Value undefined() { return Value(Type::Undefined); }
inline Value null() { return Value(Type::Null); }

std::string Value::to_string() const
{
	switch(m_type)
	{
		case Type::Integer: return fmt::format("{}", m_value.m_integer);
		case Type::Double: return fmt::format("{}", m_value.m_double);
		case Type::Boolean: return fmt::format("{}", m_value.m_boolean);
		case Type::String:
			return fmt::format("\"{}\"", *m_value.m_string);
			//		case Type::Object: return fmt::format("{}", m_value.m_object);
		case Type::Object: return m_value.m_object->to_string();
		case Type::Null: return "null";
		case Type::Undefined: return "undefined";
		default: return {};
	}
}

Value::~Value()
{
	switch(m_type)
	{
		case Type::String: delete m_value.m_string; break;
		case Type::Object: delete m_value.m_object; break;
		default: break;
	}
}

Value from_string(const std::string& str)
{
	std::string* temp = new std::string(str);
	return Value(temp);
}

Value from_object(const Object& obj)
{
	Object* temp = new Object(obj);
	return Value(temp);
}

}	 // namespace OK
