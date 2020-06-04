#pragma once

#include "cxxopts.hpp"

struct Args final
{
	Args();
	cxxopts::ParseResult parse(int& argc, char**& argv);

	cxxopts::Options options;
};
