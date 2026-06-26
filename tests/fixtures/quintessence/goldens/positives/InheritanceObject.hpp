#pragma once


#include <PrivateBase.hpp>
#include <ProtectedBase.hpp>
#include <PublicBase.hpp>


class InheritanceObject : public PublicBase, protected ProtectedBase, private PrivateBase
{
private:

protected:


public:
   InheritanceObject();
   ~InheritanceObject();

};



