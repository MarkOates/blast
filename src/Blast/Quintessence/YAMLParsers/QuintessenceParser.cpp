#include <Blast/Quintessence/YAMLParsers/QuintessenceParser.hpp>


namespace Blast
{
   namespace Quintessence
   {
      namespace YAMLParsers
      {
         QuintessenceParser::QuintessenceParser(std::string quintessence_filename, YAML::Node node)
            : quintessence_filename(quintessence_filename)
            , node(node)
         {
         }


         QuintessenceParser::~QuintessenceParser()
         {
         }


         void QuintessenceParser::set_quintessence_filename(std::string quintessence_filename)
         {
            this->quintessence_filename = quintessence_filename;
         }


         void QuintessenceParser::set_node(YAML::Node node)
         {
            this->node = node;
         }


         std::string QuintessenceParser::get_quintessence_filename() const
         {
            return quintessence_filename;
         }


         YAML::Node QuintessenceParser::get_node() const
         {
            return node;
         }


         Blast::Cpp::Class QuintessenceParser::parse()
         {
            // Stub: return a default Class object.
            Blast::Cpp::Class klass;
            return klass;
         }
      }
   }
}
