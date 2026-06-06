# Quintessence Field Definitions


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

The `properties` field represents the members of the class - variables, constants.  Two
imporant things to know.  First, _all members are not directly accessible in the
class and are scoped to `private` within the class_.  If you want to make the members
accessible then you will need to add `getter: true` and/or `setter: true` for them.  Alternatively, for POD (plain-old-data) style classes, you can use the `exposed: true` qualifier on the member, which will make the member public (as well as prevent any getters or setters from being present by blocking compile if they are there). Also, note
that all of the member's types (not including some defaults) will need to be defined in the dependencies.

| field | type | default | description |
| --- | --- | --- | --- |
| `name` | String | required | The variable name for the member. |
| `type` | String | required | Datatype for the preopty (something like `std::string`, `void`, `int`, `MyCustomType*`, `std::vector<int>`, etc.).  Note that the datatype will need to be defined in `dependencies`. |
| `init_with` | String | required | A hard-injected string that is placed as the default value for this member.  If the member is a constructor argument, then the value is assigned as a default argument in the constructor (and thus appears in the header file), otherwise the value is assigned in the initialization list (and thus appears in the source file). |
| `const` | Boolean | `false` | A value of `true` will make this a `const` variable. |
| `static` | Boolean | `false` | A value of `true` will mark the member as a `static` member.  It's default value will be assigned in the `.cpp` source file. |
| `constexpr` | Boolean | `false` | A value of `true` will make this a `constexpr` variable. |
| `constructor_arg` | Boolean | `false` | `true` if the member will appear as an argument in the constructor, otherwise `false` |
| `getter` | Boolean | `false` | A value of `true` will auto-generate a `get_*() const` function for this member. The returned value is thus a copy. |
| `getter_ref` | Boolean | `false` | A value of `true` will auto-generate a `get_*_ref()` function that returns a non-const reference to the value. |
| `setter` | Boolean | `false` | A value of `true` will auto-generate a `set_*()` function for this member. |
| `exposed` | Boolean | `false` | A value of `true` will make the member public. This should only be used for POD (plain-old-data) types of classes.|



## `enums`

#### type: Array of Hashes
#### default: `[]`

Defines enum classes or regular enums.

| field | type | default | description |
| --- | --- | --- | --- |
| `name` | String | | The name of the enum. Cannot be used if `class` is present. |
| `class` | String | | The name of the enum class. Cannot be used if `name` is present. If used, the enum is defined as an `enum class`. |
| `scope` | String | `public` | Defines the access scope of the enum (e.g., `public`, `protected`, `private`). |
| `type` | String | | The underlying type for the enum. Valid values include `int`, `int16_t`, `uint16_t`, `int32_t`, `uint32_t`, `int64_t`, `uint64_t`, or empty (default). |
| `start_from` | String/Int | `0` | The value to start the first enumerator from. Supports integers and hex strings (e.g., `"0x04"`). |
| `bitwise` | Boolean | `false` | If `true`, the enumerators are treated as bitwise flags. If `true`, `start_from` must be a power of two. |
| `enumerators` | Array of Strings | required | A list of the enumerator names. |
| `to_string` | Boolean/String/Hash | `false` | Configuration for a `to_string` method. |
| `from_string` | Boolean/String/Hash | `false` | Configuration for a `from_string` method. |


## `enums` > `to_string` / `from_string`

The `to_string` and `from_string` fields can be a Boolean (`true` to use defaults), a String (to specify the method name), or a Hash for more control:

| field | type | default | description |
| --- | --- | --- | --- |
| `method_name` | String | | The name of the generated method. |
| `remove_prefix` | String | | A prefix to remove from the enumerator names when converting to/from strings. |



## `methods`

#### type: Array of Hashes
#### default: `[]`

Defines the independently-implemented methods (not auto-generated) on the class.

| field | type | default | description |
| --- | --- | --- | --- |
| `name` | String | required | The name of the method. |
| `type` | String | `void` | the type of the method, (e.g. `std::string`, `void`, `int`, `MyCustomType`, `std::vector<int>`).  Any type declared must be included in the quintessence's `dependencies` field. |
| `parameters` | Array of Hashes default | `[]` | Array containing definitions for each parameter in the method signature.  See below for more detail. |
| `static` | Bool | `false` | If `true`, defines the method as a `static`. |
| `const` | Boolean | `false` | A value of `true` will make this a const method. |
| `virtal` | Bool | `false` | If `true`, defines method as a `static`. |
| `pure_virtal` | Bool | `false` | If `true`, defines method as a pure virtual function, meaning the method is deleted (`virtual void method_name() = 0;`) in the declaration.  Pure virtual methods must also be marked as `virtual: true` as well or they are invalid. |
| `override` | Bool | `false` | If `true`, defines the method as `override`. Any method that overrides a virtual should be marked as such. |
| `guards` | Array of strings | `[]` | Individual C++ statements that will be placed in `if (your_condition)` blocks at the top of the method's body. An exception to be thrown if they are evaluated to `false` at runtime. | 
| `body` | String | required | the code body of the method.  No magic happens here, the text you write in this string is simply injected verbatum into the body of the method (though it is indented by 3 spaces, so this could affect heredocs or multiline strings). |
| `body_dependency_symbols` | Array of Strings | `[]` | A list of symbol names used in the `body` of all the defined `method`s.  The symbol names listed will need to be included in the `dependencies` list (unless the `dependencies` have default definitions in that list). |

TODO: Look into the codebase to see if `pure_virtual:` and `const:` are included, which I believe they are.


## `methods` > `parameters`

Parameters defining the elements of a method signature. All parameters are required to have default arguments. 

> Note that this technique requires all parameters to have default arguments. This is an intentional design decision and is part of the design philosophy of this system. The priority here is to enable developers to "race to green" easily in iterative development (in this case, racing to an error-free compile), without having to fulfill a potentially insurmountable set of dependencies. References are not used as arguments, rather pointers are, and `nullptr` is used as a default. The `guards` on the method should check for valid arguments at runtime.

| field | type | default | description |
| --- | --- | --- | --- |
| `name` | String | required | variable name of the method parameter |
| `type` | String | required | datatype for the method parameter |
| `default_argument` | String | required | a default argument be assigned to the value if none is present. |
| `default_argument_dependency_symbols` | Array of strings | `[]` | Any dependencies that appear in the default argument (and thus need to be known at the level of the header file). |


## `dependencies`

#### type: Array of Hashes
#### default: `[]`

The names for each of the dependencies required by this quintessence, as well as their header files (the part included inside the `<>` of a `#include` directive).

| field | type | default | description |
| --- | --- | --- | --- |
| `symbol` | String | required | The name of the symbol.  Might be something like `std::string` or `int` or `MyCustomClass*` |
| `headers` | Array of Strings | `[]` | List of header files and their directories from the root of one of the provided include directories |


