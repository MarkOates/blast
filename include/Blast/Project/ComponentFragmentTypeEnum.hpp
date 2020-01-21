#pragma once

namespace Blast
{
   namespace Project
   {
      enum component_fragment_t
      {
         COMPONENT_FRAGMENT_TYPE_UNDEFINED = 0,
         COMPONENT_FRAGMENT_TYPE_HEADER,
         COMPONENT_FRAGMENT_TYPE_SOURCE,
         COMPONENT_FRAGMENT_TYPE_EXAMPLE,
         COMPONENT_FRAGMENT_TYPE_TEST,
         COMPONENT_FRAGMENT_TYPE_QUINTESSENCE,
      };
   }
}

