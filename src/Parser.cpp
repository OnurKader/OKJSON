#include "Parser.hpp"

#include <cassert>
#include <string>

#define ASSERT_NOT_REACHED assert(false);

/**
 * @brief This function extracts the identifier name in double quotes
 * @param str_view asdasdasdff
 * @param open_quote is the index of the opening quote
 * @param close_quote is the index of the closing quote
 * @return the identifier inside the quotes
 */
inline std::string get_variable_name_in_quotes(const std::string_view str_view,
											   const size_t open_quote,
											   const size_t close_quote);

/*!
 * \brief Gets the value after a colon
 * \param str_view The view to extract the value from
 * \return the value taken after the colon
 */
inline OK::Value get_value_after_colon(const std::string_view str_view, const size_t colon_index);

namespace OK
{
Object Parser::parse()
{
	assert(!m_str.empty());
	assert(m_str.starts_with('{'));

	Object result;
	std::string property_name;
	Value value_to_store;

	for(size_t i = 0ULL; i < m_str.size(); ++i)
	{
		switch(m_str[i])
		{
			case '"':
			{
				const size_t next_quote = m_str.find('"', i + 1ULL);
				if(next_quote == m_str.npos)
					ASSERT_NOT_REACHED;
				property_name = get_variable_name_in_quotes(m_str, i, next_quote);

				// Move forward to the closing quote
				i = next_quote;
				break;
			}
			case ':':
			{
				value_to_store = get_value_after_colon(m_str, i);
				result.set(property_name, value_to_store);
				break;
			}
		}
	}

	return result;
}
}	 // namespace OK

inline std::string get_variable_name_in_quotes(const std::string_view str_view,
											   const size_t open_quote,
											   const size_t close_quote)
{
	return std::string(&str_view[open_quote + 1ULL], close_quote - open_quote - 1ULL);
}

inline OK::Value get_value_after_colon(const std::string_view str_view, const size_t colon_index)
{
	// TODO: Go until a comma or }
	// TODO: Add integer, double, boolean, string, object, array parsing
	return OK::Value(1337ULL);
}
