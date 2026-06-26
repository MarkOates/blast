#pragma once


#include <PrivateBase.hpp>
#include <ProtectedBase.hpp>
#include <PublicBase.hpp>


namespace quintessences
{
   class InheritanceObject : public PublicBase, protected ProtectedBase, private PrivateBase
   {
   private:

   protected:


   public:
      InheritanceObject();
      ~InheritanceObject();

   };
}



