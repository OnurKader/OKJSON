# OKJSON

A simple JSON parser written in C++20 as a learning experience
with reading from files and a better understanding at std::variant

## Usage

Just run `tup`

## Output

```bash
Read JSON as:
{
	"a": 42,
	"b": -69,
	"c": "\"Cute string\" said Onur",
	"bar": true,
	"d": 3.141592653589793,
	"e": 6.942e4,
	"foo": false,
	"hex": 0x41,
	"octal": 033,
	"simple_array": [1, 2, 3],
	"complex_array": [-1, 2.3, "OwO", true],
	"hard_array": [-2, "Hard", [1, 2, 3], false, null],
	"simple_obj": {"try": 31, "this": -6.9, "boo": false},
	"complex_obj": {"aar": [1, true, [0, -4, 5], "Yeah"]},
	"hard_obj": {
		"oof": {"oz": "Magic", "33": [-3, null]},
		"yeah": [{"a": 22, "b": false}, 2222, -99]
	}
}

Value Parsed: 42
Value Parsed: -69
Value Parsed: "\"Cute string\" said Onur"
Value Parsed: true
Value Parsed: 3.141592653589793
Value Parsed: 6.942e4
Value Parsed: false
Value Parsed: 0x41
Value Parsed: 033
Value Parsed: [1, 2, 3]
Value Parsed: 1
Value Parsed: 2
Value Parsed: 3
Value Parsed: [-1, 2.3, "OwO", true]
Value Parsed: -1
Value Parsed: 2.3
Value Parsed: "OwO"
Value Parsed: true
Value Parsed: [-2, "Hard", [1, 2, 3], false, null]
Value Parsed: -2
Value Parsed: "Hard"
Value Parsed: [1
AAAHHH! Unrecognized value! `[1`
AAAHHH! Unrecognized value! `[-2, "Hard", [1, 2, 3], false, null]`
Value Parsed: "UNIMPLEMENTED OR WRONG SYNTAX"
Value Parsed: 31
Value Parsed: -6.9
Value Parsed: false
Value Parsed: "UNIMPLEMENTED OR WRONG SYNTAX"
Value Parsed: [1, true, [0, -4, 5], "Yeah"]
Value Parsed: 1
Value Parsed: true
Value Parsed: [0
AAAHHH! Unrecognized value! `[0`
AAAHHH! Unrecognized value! `[1, true, [0, -4, 5], "Yeah"]`
Value Parsed: "UNIMPLEMENTED OR WRONG SYNTAX"
Value Parsed: "UNIMPLEMENTED OR WRONG SYNTAX"
Value Parsed: "Magic"
Value Parsed: [-3, null]
Value Parsed: -3
Value Parsed: null
Value Parsed: [{"a": 22, "b": false}, 2222, -99]
Value Parsed: {"a": 22
JSON: Parser.cpp:281: OK::Value get_value_after_colon(std::string_view):
Assertion `false' failed.
[1]    13411 abort (core dumped)  ../bin/JSON
```

