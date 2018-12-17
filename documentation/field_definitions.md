# Quintessence JSON Fields Definitions

## `class`

#### type: String

Provide the base name of your class, without namespaces.  This should be in
camel case and should match the basename of the quintessence file.



## `format`

#### type: String

For now, the value should always be "`verbose`".  This means that all fields should be present and
there are no defaults for missing values.



## `parent_classes`

#### type: Array of Hashes

Defines the parent classes that this class inherits from.  Each parent class
hash

| field | type | description |
| --- | --- | --- |
| `class` | String | The name of the parent class. |
| `scope` | String | one of `public`, `private` or `protected`.  Defines the access scope of the inherited class. |
| `init_with` | String | The string to be injected into the constructor of the parent class, when initialized in the main class's initialization list.  This value you provide is _hard coded_ and is non-magical.  It is simply injected between the `()` of the parent class's construction. |



## `functions`

#### type: Array of Hashes

Defines the independently-implemented functions on the class.

| field | type | description |
| --- | --- | --- |
| `name` | String | The name of the function. |
| `type` | String | the type of the function, (e.g. `std::string`, `void`, `int`, `MyCustomType`, `std::vector<int>`).  Any type declared must be included in the quintessence's `dependencies` field. |
| `parameters` | Array of Hashes | Array containing definitions for each parameter in the function signature.  See below for more detail. |
| `body` | String | the code body of the function.  No magic happens here, the text you write in this string is simply injected verbatum into the body of the function. |


## `functions` > `parameters`

Parameters defining the elements of a function signature:

| field | type | description |
| --- | --- | --- |
| `name` | String | variable name of the function parameter |
| `type` | String | datatype for the function parameter (default is `std::string`) |
| `default_value` | String | a default argument be assigned to the value if none is present. |
