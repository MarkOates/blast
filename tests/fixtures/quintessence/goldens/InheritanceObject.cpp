

#include <quintessences/InheritanceObject.hpp>




namespace quintessences
{


InheritanceObject::InheritanceObject()
   : PublicBase("arg1", 42)
   , ProtectedBase("arg2")
   , PrivateBase()
{
}


InheritanceObject::~InheritanceObject()
{
}




} // namespace quintessences


