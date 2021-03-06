#include "Array.hpp"

namespace OK
{
Array::Array(const std::initializer_list<Value> init_list) : m_values {init_list} {}

Array::Array(std::vector<Value>&& vec) : m_values(vec) {}

void Array::push(const Value value) { m_values.push_back(value); }
void Array::push(Value&& value) { m_values.push_back(value); }

Value Array::pop()
{
	Value temp = m_values.back();
	m_values.pop_back();
	return temp;
}

std::vector<Value>& Array::vector() { return m_values; }
const std::vector<Value>& Array::vector() const { return m_values; }

void Array::clear() { m_values.clear(); }

Value& Array::operator[](const size_t index) { return m_values[index]; }
const Value& Array::operator[](const size_t index) const { return m_values[index]; }

std::string Array::to_string() const
{
	// TODO: Array printing
	fmt::memory_buffer buff;
	buff.reserve(64ULL);

	fmt::format_to(buff, "[");

	for(size_t i = 0ULL; i < m_values.size() - 1ULL; ++i)
		fmt::format_to(buff, "{}, ", m_values[i]);

	fmt::format_to(buff, "{}]", m_values.back());
	return fmt::to_string(buff);
}

}	 // namespace OK
