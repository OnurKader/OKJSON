#include "Parser.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <string>

#define ASSERT_NOT_REACHED() assert(false);

std::optional<std::string_view> extract_string_from_view(const std::string_view str_view);
std::optional<std::string_view> extract_array_from_view(const std::string_view str_view);
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
std::optional<Object> Parser::parse(const std::string_view str_view)
{
	assert(!str_view.empty());
	// Don't allow [] JSON yet
	assert(str_view.starts_with('{'));

	Object result;
	std::string_view property_name;

	for(size_t i = 0ULL; i < str_view.size(); ++i)
	{
		switch(str_view[i])
		{
			case '\"':
			{
				const size_t next_quote = str_view.find('\"', i + 1ULL);
				if(next_quote == str_view.npos)
					ASSERT_NOT_REACHED();
				property_name = get_variable_name_in_quotes(str_view.substr(i));

				// Move forward to the closing quote
				i = next_quote;
				break;
			}
			case ':':
			{
				const Value value_to_store = get_value_after_colon(str_view.substr(i));
				if(value_to_store.is_empty())
					// return std::nullopt;
					break;
				result.set(property_name, value_to_store);
				break;
			}
		}
	}

	return result;
}

std::optional<Value> Parser::parse_value(const std::string_view str_view)
{
	fmt::print("Value Parsed: {}\n", str_view);

	if(auto opt = parse_int(str_view); opt.has_value())
		return Value(opt.value());

	if(auto opt = parse_double(str_view); opt.has_value())
		return Value(opt.value());

	if(auto opt = parse_bool(str_view); opt.has_value())
		return Value(opt.value());

	if(auto opt = parse_null(str_view); opt.has_value())
		return opt.value();	   // Looks odd

	if(auto opt = parse_string(str_view); opt.has_value())
		return Value(opt.value());

	if(auto opt = parse_object(str_view); opt.has_value())
		return Value(opt.value());

	if(auto opt = parse_array(str_view); opt.has_value())
		return Value(opt.value());

	fmt::print(stderr, "AAAHHH! Unrecognized value! `{}`\n", str_view);

	return std::nullopt;
}

std::optional<int64_t> Parser::parse_int(const std::string_view str_view)
{
	assert(str_view.size() < 128ULL || !str_view.empty());
	char buff[128ULL];
	str_view.copy(buff, str_view.size());
	buff[str_view.size()] = '\0';
	char* end;
	int64_t result;
	if(str_view.starts_with("0x"))
		result = std::strtoll(buff, &end, 16);
	else if(str_view.starts_with('0'))
		result = std::strtoll(buff, &end, 8);
	else
		result = std::strtoll(buff, &end, 10);

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

std::optional<Value> Parser::parse_null(const std::string_view str_view)
{
	if(str_view == "null")
		return null();
	return std::nullopt;
}

std::optional<std::string*> Parser::parse_string(const std::string_view str_view)
{
	// MAYBE: check escape sequences \", \n etc...
	if(str_view.starts_with('\"') && str_view.ends_with('\"'))
	{
		const std::string_view temp {str_view.substr(1ULL, str_view.size() - 2ULL)};
		return new std::string(temp);
	}

	return std::nullopt;
}

std::optional<Object*> Parser::parse_object(const std::string_view str_view)
{
	if(!str_view.starts_with('{'))
		return std::nullopt;

	// BUG: str_view probably doesn't have the closing brace
	const auto obj = parse(str_view);
	if(!obj)
		return std::nullopt;

	return new Object(*obj);
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
	for(size_t i = 1ULL; i < str_view.size(); ++i)
	{
		// FIXME: Don't add ']' here just check for ',' and npos
		// FIXME: Actually ',' is wrong too like I said up there, strings can have commas
		// TODO: Make this into a function that checks whether ,] are in a string or like an
		// object(?)
		const size_t seperator_index = str_view.find_first_of(",]", i);
		const size_t first_non_whitespace_index = str_view.find_first_not_of(' ', i);
		std::string_view value_seperated_by_comma = str_view.substr(
			first_non_whitespace_index, seperator_index - first_non_whitespace_index);
		i = seperator_index;

		if(const auto value = parse_value(value_seperated_by_comma); value.has_value())
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

// FR: Add some helper functions which extract individual data like an object or an array
std::optional<std::string_view> extract_string_from_view(const std::string_view str_view)
{
	for(size_t i = 1ULL; i < str_view.size(); ++i)
	{
		switch(str_view[i])
		{
			case '\\': ++i; continue;
			case '"': return str_view.substr(0ULL, i + 1ULL);
		}
	}
	return std::nullopt;
}

std::optional<std::string_view> extract_array_from_view(const std::string_view str_view)
{
	size_t bracket_count = 0ULL;
	for(size_t i = 1ULL; i < str_view.size(); ++i)
	{
		switch(str_view[i])
		{
			case '[': ++bracket_count; break;
			case ']':
				if(bracket_count == 0ULL)
					return str_view.substr(0ULL, i + 1ULL);
				--bracket_count;
				break;
		}
	}
	return std::nullopt;
}

OK::Value get_value_after_colon(const std::string_view str_view)
{
	// NOTE: The string view here is ":\s*.+"
	// FIXME: Do some special parsing for { and [

	// BUG: This breaks objects, {"a": {"owo": 12}}
	//                                will detect ^ as the ending, but it's not

	std::string_view colon_value_str {"\"UNIMPLEMENTED OR WRONG SYNTAX\""};

	const auto first_non_space_index = str_view.find_first_not_of(" \t\n", 1ULL);
	const char first_non_space_char = str_view[first_non_space_index];
	switch(first_non_space_char)
	{
		case '"':
		{
			if(const auto string = extract_string_from_view(str_view.substr(first_non_space_index));
			   string.has_value())
				colon_value_str = *string;
			break;
		}
		case '[':
		{
			if(const auto array = extract_array_from_view(str_view.substr(first_non_space_index));
			   array.has_value())
				colon_value_str = *array;
			break;
		}
		case '{':
		{
			break;
		}
		default:
		{
			const auto comma_or_brace_index = str_view.find_first_of(",}\n", first_non_space_index);
			if(comma_or_brace_index == str_view.npos)
				ASSERT_NOT_REACHED();

			colon_value_str = str_view.substr(first_non_space_index,
											  comma_or_brace_index - first_non_space_index);
		}
	}

	return OK::Parser::parse_value(colon_value_str).value_or(OK::Value());
}
