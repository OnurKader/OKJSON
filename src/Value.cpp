#include "Value.hpp"

#include "Array.hpp"
#include "Object.hpp"

namespace OK
{
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
		case Type::Array: return m_value.m_array->to_string();
		case Type::Null: return "null";
		case Type::Undefined: return "undefined";
		case Type::Empty: return "EMPTY!";
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

Value from_array(const Array& arr)
{
	Array* temp = new Array(arr);
	return Value(temp);
}

}	 // namespace OK
