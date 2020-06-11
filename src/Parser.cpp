#include "Parser.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <string>

#define ASSERT_NOT_REACHED assert(false);

/**
 * @brief This function extracts the identifier name in double quotes
 * @param str_view The view to extract from
 * @param open_quote_index is the index of the opening quote
 * @return the identifier inside the quotes
 */
std::string_view get_variable_name_in_quotes(const std::string_view, const size_t open_quote_index);

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
	std::string_view property_name;
	Value value_to_store;

	for(size_t i = 0ULL; i < m_str.size(); ++i)
	{
		switch(m_str[i])
		{
			case '\"':
			{
				const size_t next_quote = m_str.find('\"', i + 1ULL);
				if(next_quote == m_str.npos)
					ASSERT_NOT_REACHED;
				property_name = get_variable_name_in_quotes(m_str, i);

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

Value Parser::parse_value(const std::string_view str_view)
{
	fmt::print("Value to be parsed: \"{}\"\n", str_view);

	if(auto opt = parse_int(str_view); opt.has_value())
		return Value(opt.value());
	if(auto opt = parse_double(str_view); opt.has_value())
		return Value(opt.value());
	if(auto opt = parse_bool(str_view); opt.has_value())
		return Value(opt.value());
	if(auto opt = parse_string(str_view); opt.has_value())
		return Value(opt.value());
	if(auto opt = parse_object(str_view); opt.has_value())
		return Value(opt.value());
	if(auto opt = parse_array(str_view); opt.has_value())
		return Value(opt.value());

	fmt::print(stderr, "AAAHHH! Unrecognized value!\n");

	return undefined();
}

std::optional<int64_t> Parser::parse_int(const std::string_view str_view)
{
	assert(str_view.size() < 128ULL);
	char buff[128ULL];
	str_view.copy(buff, str_view.size());
	buff[str_view.size()] = '\0';
	char* end;
	const int64_t result = std::strtoll(buff, &end, 10);

	if(*end == 0)
		return result;
	return std::nullopt;
}

std::optional<double> Parser::parse_double(const std::string_view str_view)
{
	assert(str_view.size() < 128ULL);
	char buff[128ULL];
	str_view.copy(buff, str_view.size());
	buff[str_view.size()] = '\0';
	char* end;
	const double result = std::strtod(buff, &end);

	if(*end == 0)
		return result;
	return std::nullopt;
}

std::optional<bool> Parser::parse_bool(const std::string_view str_view)
{
	const bool truth = (str_view == "true");
	if(truth)
		return true;
	const bool fault = (str_view == "false");
	if(fault)
		return false;

	return std::nullopt;
}

std::optional<std::string*> Parser::parse_string(const std::string_view str_view)
{
	// Maybe check escape sequences \", \n etc...
	if(str_view.starts_with('\"') && str_view.ends_with('\"'))
		return new std::string(str_view);

	return std::nullopt;
}

std::optional<Object*> Parser::parse_object(const std::string_view str_view)
{
	// TODO: Maybe deal with parse_value first
	return std::nullopt;
}

std::optional<Array*> Parser::parse_array(const std::string_view str_view)
{
	if(!str_view.starts_with('[') || !str_view.ends_with(']'))
		return std::nullopt;

	// FIXME: Very bad, strings can have commas in them!
	const size_t comma_count =
		static_cast<size_t>(std::count(str_view.cbegin(), str_view.cend(), ','));
	std::vector<Value> values;
	values.reserve(comma_count + 1ULL);
	// Maybe just std::all_of() with !parse_value().is_undefined()?
	for(size_t i = 1ULL; i < str_view.size(); ++i)
	{
		const size_t seperator_index = str_view.find_first_of(",]", i + 1ULL);
		std::string_view value_seperated_by_comma = str_view.substr(i, seperator_index - 1ULL);
		// Qt Creator doesn't support this syntax
		if(const Value value = parse_value(value_seperated_by_comma); !value.is_undefined())
			values.push_back(value);	// emplace_back with value? Copy const?
		else
			return std::nullopt;
	}

	return new Array(std::move(values));
}

}	 // namespace OK

// Replace colon_index with just str_view but it's subtsringed
inline OK::Value get_value_after_colon(const std::string_view str_view, const size_t colon_index)
{
	// TODO: Add object parsing
	// return Parser::parse_value(str_view.substr(colon_index), sep_index (?));

	const auto comma_or_brace_index = str_view.find_first_of(",}", colon_index + 1ULL);
	const std::string_view colon_value_str =
		str_view.substr(colon_index + 1ULL, comma_or_brace_index - colon_index - 1ULL);
	return OK::Parser::parse_value(colon_value_str);
}

std::string_view get_variable_name_in_quotes(const std::string_view str_view,
											 const size_t open_quote_index)
{
	const auto close_quote_index = str_view.find('"', open_quote_index + 1ULL);
	return str_view.substr(open_quote_index + 1ULL, close_quote_index - open_quote_index - 1ULL);
}
