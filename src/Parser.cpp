#include "Parser.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <string>

#define ASSERT_NOT_REACHED() assert(false);

/**
 * @brief This function extracts the identifier name in double quotes
 * @param str_view The view to extract from
 * @param open_quote_index is the index of the opening quote
 * @return the identifier inside the quotes
 */
std::string_view get_variable_name_in_quotes(const std::string_view);

/*!
 * \brief Gets the value after a colon
 * \param str_view The view to extract the value from
 * \return the value taken after the colon
 */
OK::Value get_value_after_colon(const std::string_view str_view);

namespace OK
{
Object Parser::parse()
{
	assert(!m_str.empty());
	// Don't allow [] JSON yet
	assert(m_str.starts_with('{'));

	Object result;
	std::string_view property_name;

	for(size_t i = 0ULL; i < m_str.size(); ++i)
	{
		switch(m_str[i])
		{
			case '\"':
			{
				const size_t next_quote = m_str.find('\"', i + 1ULL);
				if(next_quote == m_str.npos)
					ASSERT_NOT_REACHED();
				property_name = get_variable_name_in_quotes(m_str.substr(i));

				// Move forward to the closing quote
				i = next_quote;
				break;
			}
			case ':':
			{
				const auto val = get_value_after_colon(m_str.substr(i));
				const Value value_to_store = val.has_value() ? val : undefined();
				result.set(property_name, value_to_store);
				break;
			}
		}
	}

	return result;
}

std::optional<Value> Parser::parse_value(const std::string_view str_view)
{
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

	return std::nullopt;
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
	if(!str_view.starts_with('{') || !str_view.ends_with('}'))
		return std::nullopt;

	// TODO: Change Parser::parse() to actually return an optional, and call it here.
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
		// ???: I'm talking about the undefined -> empty thing here
		if(const auto value = parse_value(value_seperated_by_comma); !value)
			values.push_back(*value);	 // emplace_back with value? Copy const?
		else
			return std::nullopt;
	}

	return new Array(std::move(values));
}

}	 // namespace OK

std::string_view get_variable_name_in_quotes(const std::string_view str_view)
{
	const auto close_quote_index = str_view.find('"', 1ULL);
	return str_view.substr(1ULL, close_quote_index - 1ULL);
}

OK::Value get_value_after_colon(const std::string_view str_view)
{
	const auto comma_or_brace_index = str_view.find_first_of(",}", 1ULL);
	const std::string_view colon_value_str = str_view.substr(1ULL, comma_or_brace_index - 1ULL);
	return OK::Parser::parse_value(colon_value_str).value_or(OK::Value());
}
