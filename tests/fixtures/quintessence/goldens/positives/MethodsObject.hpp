#pragma once


#include <string>


class MethodsObject
{
private:
   int dummy_prop;

protected:


public:
   MethodsObject();
   virtual ~MethodsObject();

   static float static_func(float factor=1.0f);
   std::string const_func() const;
   virtual void virtual_func();
   virtual void pure_virtual_func() = 0;
   void override_func() override;
   bool guarded_func(int* value=nullptr, int threshold=10);
};



