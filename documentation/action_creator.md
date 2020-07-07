## ActionGenerator

### Inputs:

```yml
parent_component: Blast/Thingie
action_name_snake_case: do_important_thing
stage: Blast/Thingie/Stage
```

### Assumptions:

- the stage, unless explicitly defined is "Blast/Thingie/Stage"
- the event controller is "Blast/Thingie/EventController"

### Generated Fragments:


method declaration (goes in Blast/Thingie/Stage header):
```cpp
bool do_important_thing();
```


header file include line  (goes in Blast/Thingie/Stage source):
```cpp
#include <Blast/Thingie/Action/DoImportantThing.hpp>
```


method definition   (goes in Blast/Thingie/Stage source):
```cpp
bool Blast::Thingie::Stage::do_important_thing()
{
   Blast::Thingie::Action::DoImportantThing action(this);
   return action.execute();
}
```



in-header declaration of constant (goes in Blast/Thingie/Stage header):
```cpp
static const std::string DO_IMPORTANT_THING;
```


in-source definition of constant (goes in Blast/Thingie/Stage source):
```cpp
const std::string Blast::Thingie::Stage::DO_IMPORTANT_THING = "DO_IMPORTANT_THING";
```


event_controller mapping (goes in Blast/Thingie/EventController):
```cpp
         {
            ::Blast::Thingie::DO_IMPORTANT_THING,
            &::Blast::Thingie::do_important_thing,
         },
```

new quintessence filename:
```
quintessence/Blast/Thingie/Action/DoImportantThing.q.yml
```

new quintessence file contents:
```yml
parent_classes:


  - class: ::Action
    scope: public
    init_with: '"Blast::Thingie::Action::DoImportantThing", ActionData()"'


properties:


  - name: stage
    type: Blast::Thingie::Stage*
    init_with: nullptr
    constructor_arg: true


functions:


  - name: execute
    virtual: true
    override: true
    type: bool
    guards: [ stage ]
    body: |
      return true;


dependencies:


  - symbol: ::Action
    headers: [ Hexagon/Action.hpp ]
  - symbol: Blast::Thingie::Stage*
    headers: [ Blast/Thingie/Stage.hpp ]
```

component test file:

### Left to the Programmer:

* keyboard command mapping
* reduction of properties, parameters, and arguments in action signature and at point of invocation in the stage's method.
