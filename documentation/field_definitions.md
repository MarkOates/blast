# Quintessence JSON Fields Definitions

## `class`

#### type: String
#### default: (YAML: A default value will be inferred from the basename of the filename)

Provide the base name of your class, without namespaces.  This should be in
camel case and should match the basename of the quintessence file.



## `format`

#### type: String
#### default: none (YAML: this key/value is not used)

For now, the value should always be "`verbose`".  This means that all fields should be present and
there are no defaults for missing values.



## `parent_classes`

#### type: Array of Hashes
#### default: `[]`

Defines the parent classes that this class inherits from.  Each parent class
hash

| field | type | default | description |
| --- | --- | --- | --- |
| `class` | String | required | The name of the parent class. |
| `scope` | String | required | ne of `public`, `private` or `protected`.  Defines the access scope of the inherited class. |
| `init_with` | String | required |The string to be injected into the constructor of the parent class, when initialized in the main class's initialization list.  This value you provide is _hard coded_ and is non-magical.  It is simply injected between the `()` of the parent class's construction. |



## `properties`

#### type: Array of Hashes
#### default: `[]`

The properties field represents all attributes that exist on the class.  Two
imporant things to know.  First, _all fields are not directly accessible in the
class and are scoped privately within the class_.  If you want to make the properties
accessible then you will need to set getters and setters for them.  Also, note
that each type will need to be defined in the dependencies.

| field | type | default | description |
| --- | --- | --- | --- |
| `name` | String | required | The variable name for the property. |
| `type` | String | `std::string` | Datatype for the preopty (something like `std::string`, `void`, `int`, `MyCustomType*`, `std::vector<int>`, etc.).  Note that the datatype will need to be defined in `dependencies`. |
| `init_with` | String | `""` | A hard-injected string that is placed as the default value for this property.  If the property is a constructor argument, then the value is assigned as a default argument in the constructor, otherwise the value is assigned in the initialization list. |
| `constructor_arg` | Boolean | `false` | `true` if the property will appear as an argument in the constructor, otherwise `false` |
| `static` | Boolean | `false` | A value of `true` will mark the property as a `static` property.  It's default value will be assigned in the `.cpp` source file. |
| `getter` | Boolean | `false` | A value of `true` will create a `get_*()` function for this property. |
| `getter_ref` | Boolean | `false` | A value of `true` will create a `get_*_ref()` function that returns a non-const reference to the value. |
| `setter` | Boolean | `false` | A value of `true` will create a `set_*()` function for this property. |




## `functions`

#### type: Array of Hashes
#### default: `[]`

Defines the independently-implemented functions on the class.

| field | type | default | description |
| --- | --- | --- | --- |
| `name` | String | required | The name of the function. |
| `type` | String | required | the type of the function, (e.g. `std::string`, `void`, `int`, `MyCustomType`, `std::vector<int>`).  Any type declared must be included in the quintessence's `dependencies` field. |
| `parameters` | Array of Hashes default | `[]` | Array containing definitions for each parameter in the function signature.  See below for more detail. |
| `body` | String | required | the code body of the function.  No magic happens here, the text you write in this string is simply injected verbatum into the body of the function. |
| `is_static` | Bool | `false` | If `true`, defines the function as a `static`. |
| `is_const` | Bool | `false` | If `true`, defines the function as a `const`. |
| `is_override` | Bool | `false` | If `true`, defines the function as `override`. |
| `is_virtal` | Bool | `false` | If `true`, defines function as a `static`. |
| `is_pure_virtual` | Bool | `false` | If `true`, defines the function as `static`. |



## `functions` > `parameters`

Parameters defining the elements of a function signature:

| field | type | default | description |
| --- | --- | --- | --- |
| `name` | String | required | variable name of the function parameter |
| `type` | String | required | datatype for the function parameter (default is `std::string`) |
| `default_argument` | String | required | a default argument be assigned to the value if none is present. |



## `function_body_symbol_dependencies`

#### type: Array of Strings
#### default: `[]`

A list of symbol names used in the `body` of all the defined `function`s.  The symbol names listed will need to be included in the `dependencies` list (unless the `dependencies` have default definitions in that list.)



## `dependencies`

#### type: Array of Hashes
#### default: `[]`

The definitions for each of the dependencies required by this quintessence.
Dependencies can occour 

| field | type | default | description |
| --- | --- | --- | --- |
| `symbol` | String | required | The name of the symbol.  Might be something like `std::string` or `int` or `MyCustomClass*` |
| `headers` | Array of Strings | `[]` | List of header files and their directories from the root of one of the provided include directories |
| `include_directories` | Array of Strings | `[]` | The include directories needed to locate the header file at compile-time. Note that for the standard template library, you won't need to provide include directories. This you can leave empty (e.g. `[]`) |
| `linked_libraries` | Array of Strings | `[]` | The names of the libraries as they would be linked to with `-l` at compile-time. Note that for the standard template library, you don't need any linked libraries. This you can leave empty (e.g. `[]`) |



