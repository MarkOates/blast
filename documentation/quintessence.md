# Quintessence Extrapolation

Quintessence extrapolation is a technique to automatically generate code based on a more fundamental definition of the code.  The definition, called the quintessence, can be used to generate header files and source files, or generate consequential files from a preestablished design pattern.

Quintessence files have the `.q` extension and contain the meta-definition notated as a JSON structure (JSON definition files contain the full `.q.json` extension. New formats apart from JSON could be added added in the future).

**Note: This document outlines the JSON version of the quintessence extrapolation process.  Please now prefer usage of the YAML process, as it includes a much less verbose set of requirements and sensible defaults.**

## Generating (JSON)

To generate classes from a quintessence file, use the `quintessence_from_json`
program located in the Blast repository's `programs/` folder.  Once you have
built the program, you can generate class files from the quintessence by passing the name of the quintessence file as an argument:

```
> quintessence_from_json quintessence/MyProject/MyClass.q.json
```

You can pass multiple quintessence files simultaniously if you wish:

```
> quintessence_from_json quintessence/MyProject/MyClass.q.json quintessence/MyProject/MyOtherClass.q.json
```

## Complete Example

Here is a mostly complete example of a quintessence structue.

Note the filename for
this class should match the `class` and its nesting folder(s) should also match
its `namespace`(s).  So the filename for the structure below should be
`quintessence/Examples/MyExampleClass.q.json` located at the root of the project
directory.

```json
{
  "class": "MyExampleClass",
  "format": "verbose",
  "parent_classes": [
    {
      "class" : "DiceRoller",
      "init_with" : "",
      "scope" : "public"
    }
  ],
  "namespaces": [ "Examples" ],
  "functions" : [
    {
      "name" : "my_function",
      "type" : "std::string",
      "parameters" : [
        {
          "name" : "person_name"
        }
      ],
      "body" : "return std::string(\"Hello, \") + person_name + \"!\";"
    }
  ],
  "properties" : [
    {
      "type": "std::string",
      "name": "string",
      "init_with": "\"foo-default-value\"",
      "constructor_arg" : true,
      "static": false,
      "getter": false,
      "setter": false
    }
  ],
  "dependencies" : [
    {
      "symbol" : "std::string",
      "headers" : [ "string" ],
      "include_directories" : [ "foodir" ],
      "linked_libraries" : [ "foolib" ]
    },
    {
      "symbol" : "DiceRoller",
      "headers" : [ "Blast/DiceRoller.hpp" ],
      "include_directories" : [ "~/Repos/blast" ],
      "linked_libraries" : [ "foolink" ]
    }
  ]
}
```

## Empty Class

An absolute minimum example might look something like below.  The filename for
this file would be `quintessence/Examples/MyEmptyClass.q.json`.

```json
{
  "class": "MyEmptyClass",
  "format": "verbose",
  "parent_classes": [],
  "namespaces": [ "Examples" ],
  "functions" : [],
  "properties" : [],
  "dependencies" : []
}
```

Upon running the quintessence through the generator, the following two files
will be generated:

* `src/Examples/MyEmptyClass.cpp`
* `include/Examples/MyEmptyClass.hpp`

#### `include/Examples/MyEmptyClass.hpp`:

```cpp
#pragma once

namespace Examples
{
   class MyEmptyClass
   {
   public:
      MyEmptyClass();
      ~MyEmptyClass();
   };
}
```

#### `src/Examples/MyEmptyClass.cpp`:

```cpp
#include <Examples/MyEmptyClass.hpp>


namespace Examples
{

MyEmptyClass::MyEmptyClass()
{
}

MyEmptyClass::~MyEmptyClass()
{
}

} // namespace Examples
```


## Simple Class With a Single Property

We can add a property to our class by modifying our existing `MyEmptyClass` and
adding some `properties` (and consequently some `dependencies`).  To simplify
things, we'll rename our class to `MyClassWithAProperty`, and rename the file to
`MyClassWithAProperty.q.json`.

For clarity, we'll call our property `my_property_name` and define the property's type as a `std::string`.  We'll give it
a default value, and include it as an argument in our class's constructor.

```json
{
  "class": "MyClassWithAProperty",
  "format": "verbose",
  "parent_classes": [],
  "namespaces": [ "Examples" ],
  "functions" : [],
  "function_body_symbol_dependencies" : [],
  "properties" : [
    {
      "type": "std::string",
      "name": "my_property_name",
      "init_with": "\"my-default-value\"",
      "constructor_arg" : true,
      "static": false,
      "getter": false,
      "setter": false
    }
  ],
  "dependencies" : [
    {
      "symbol" : "std::string",
      "headers" : [ "string" ],
      "include_directories" : [],
      "linked_libraries" : []
    }
  ]
}
```


```cpp
#pragma once

#include <string>

namespace Examples
{
   class MyClassWithAProperty
   {
   private:
      std::string my_property_name;

   public:
      MyClassWithAProperty(std::string my_property_name="my-default-value");
      ~MyClassWithAProperty();
   };
}
```

```cpp
#include <Examples/MyClassWithAProperty.hpp>


namespace Examples
{


MyClassWithAProperty::MyClassWithAProperty(std::string my_property_name)
   : my_property_name(my_property_name)
{
}


MyClassWithAProperty::~MyClassWithAProperty()
{
}


} // namespace Examples
```

At this time, our new `my_property_name` is only accessible internally to the class,
and thus is designated as `private`.  Under the Blast programming conventions,
_no properties of a class are directly accessible_.  That means that if we want
to read or modify any class attribute, we need to create getters and setters (or
reference getters).  We'll do that in a second.


First, before we make that class attribute accessible, let's quickly take a look at the newly added definitions in the `dependencies` field of the
quintessence.

### Dependencies

```
  "dependencies" : [
    {
      "symbol" : "std::string",
      "headers" : [ "string" ],
      "include_directories" : [],
      "linked_libraries" : []
      "library_directories" : []
    }
  ]
```
_^ fig x: dependencies within the quintessence_

This `dependencies` field defines any external dependencies that are
required by our class.  Since our quintessence isn't able to interpret the
`type` that we just created of `std::string`, we'll need to define it. We need to tell it what (if any)
header files are associated with the dependency, what (if any) include directories are used, 
what (if any) libraries need to be linked, and the directories of where to find them.

For now, we only need to include the `symbol` name and `headers` for our `std::string`, since this dependency requires no external libraries.  This will tell the generator to `#include <string>` whenever it needs to generate code with that symbol.



