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
Value Parsed: 31
Value Parsed: -6.9
Value Parsed: false
Value Parsed: "Magic"
Value Parsed: 22
Value Parsed: false

Parsed Object:
{
	"a": 42,
	"b": -69,
	"c": "\"Cute string\" said Onur",
	"bar": true,
	"d": 3.141592653589793,
	"e": 69420.0,
	"foo": false,
	"hex": 65,
	"octal": 27,
	"simple_array": "UNIMPLEMENTED",
	"complex_array": "UNIMPLEMENTED",
	"hard_array": "UNIMPLEMENTED",
	"simple_obj": "UNIMPLEMENTED",
	"try": 31,
	"this": -6.9,
	"boo": false,
	"complex_obj": "UNIMPLEMENTED",
	"aar": "UNIMPLEMENTED",
	"hard_obj": "UNIMPLEMENTED",
	"oof": "UNIMPLEMENTED",
	"oz": "Magic",
	"33": "UNIMPLEMENTED",
	"yeah": "UNIMPLEMENTED",
	"a": 22,
	"b": false,
}

```

