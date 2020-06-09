#pragma once

#include <array>
#include <cstddef>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <limits>
#include <vector>

template<typename T, size_t S>
struct fmt::formatter<std::array<T, S>>
{
	constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const std::array<T, S>& arr, FormatContext& fc)
	{
		format_to(fc.out(), "[");
		for(size_t i = 0ULL; i < arr.size() - 1ULL; ++i)
			format_to(fc.out(), "{}, ", arr[i]);
		return format_to(fc.out(), "{}]", arr.back());
	}
};

template<typename T>
struct fmt::formatter<std::vector<T>>
{
	constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const std::vector<T>& vec, FormatContext& fc)
	{
		format_to(fc.out(), "[");
		for(size_t i = 0ULL; i < vec.size() - 1ULL; ++i)
			format_to(fc.out(), "{}, ", vec[i]);
		if(vec.size())
			return format_to(fc.out(), "{}]", vec.back());
		return format_to(fc.out(), "]");
	}
};

template<typename T1, typename T2>
struct fmt::formatter<std::pair<T1, T2>>
{
	constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const std::pair<T1, T2>& pair, FormatContext& fc)
	{
		return format_to(fc.out(), "({}, {})", pair.first, pair.second);
	}
};

template<typename FloatingPoint>
constexpr FloatingPoint abs(
	FloatingPoint x,
	typename std::enable_if<std::is_floating_point<FloatingPoint>::value>::type* = nullptr)
{
	return x >= 0 ? x : x < 0 ? -x : std::numeric_limits<FloatingPoint>::infinity();
}

template<typename T>
constexpr bool feq(const T x, const T y)
{
	return abs(x - y) <= std::numeric_limits<T>::epsilon();
}
