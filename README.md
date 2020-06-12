# OKJSON

A simple JSON parser written in C++20 as a learning experience
with reading from files and a better understanding at std::variant

## Usage

Just run `tup`

## Output

```
AAAHHH! Unrecognized value!
Read JSON as:
{
	"a": 42,
	"b": -69,
	"c": "\"Cute string\" said Onur",
	"bar": true,
	"d": 3.141592653589793,
	"e": 6.942e4,
	"foo": false,
	"simple_array": [1, 2, 3],
	"complex_array": [-1, 2.3, "OwO", true],
	"hex": 0x41,
	"octal": 033,
	"hard_array": [-2, "Hard", [1, 2, 3], false, null],
}

Value Parsed: 42
Value Parsed: -69
Value Parsed: "\"Cute string\" said Onur"
Value Parsed: true
Value Parsed: 3.141592653589793
Value Parsed: 6.942e4
Value Parsed: false
Value Parsed: [1

Parsed Object:
{
}
```
