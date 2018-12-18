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




## `properties`

#### type: Array of Hashes

The properties field represents all attributes that exist on the class.  Two
imporant things to know.  First, _all fields are not directly accessible in the
class and are scoped privately within the class_.  If you want to make the properties
accessible then you will need to set getters and setters for them.  Also, note
that each type will need to be defined in the dependencies.

| field | type | description |
| --- | --- | --- |
| `name` | String | The variable name for the property. |
| `type` | String | Datatype for the preopty (something like `std::string`, `void`, `int`, `MyCustomType*`, `std::vector<int>`, etc.).  Note that the datatype will need to be defined in `dependencies`. |
| `init_with` | String | A hard-injected string that is placed as the default value for this property.  If the property is a constructor argument, then the value is assigned as a default argument in the constructor, otherwise the value is assigned in the initialization list. |
| `constructor_arg` | Boolean | `true` if the property will appear as an argument in the constructor, otherwise `false` |
| `static` | Boolean | A value of `true` will mark the property as a `static` property.  It's default value will be assigned in the `.cpp` source file. |
| `getter` | Boolean | A value of `true` will create a `get_*()` function for this property. |
| `setter` | Boolean | A value of `true` will create a `set_*()` function for this property. |




## `dependencies`

#### type: Array of Hashes

The definitions for each of the dependencies required by this quintessence.
Dependencies can occour 

| field | type | description |
| --- | --- | --- |
| `symbol` | String | The name of the symbol.  Might be something like `std::string` or `int` or `MyCustomClass*` |
| `headers` | Array of Strings | List of header files and their directories from the root of one of the provided include directories |
| `include_directories` | Array of Strings | The include directories needed to locate the header file at compile-time. Note that for the standard template library, you won't need to provide include directories. This you can leave empty (e.g. `[]`) |
| `linked_libraries` | Array of Strings | The names of the libraries as they would be linked to with `-l` at compile-time. Note that for the standard template library, you don't need any linked libraries. This you can leave empty (e.g. `[]`) |



