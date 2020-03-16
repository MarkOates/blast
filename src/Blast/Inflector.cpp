

#include <Blast/Inflector.hpp>
#include <Blast/RegexMatcher.hpp>
#include <vector>
#include <string>


namespace Blast
{


Inflector::Inflector(std::string word)
   : word(word)
{
}


Inflector::~Inflector()
{
}


std::string Inflector::pluralize()
{
return "quizes";

}

std::vector<std::pair<std::string, std::string>> Inflector::build_inflections_list()
{
// full list to emulate here:
// https://github.com/rails/rails/blob/f33d52c95217212cbacc8d5e44b5a8e3cdc6f5b3/activesupport/lib/active_support/inflections.rb

std::vector<std::pair<std::string, std::string>> inflections{
   //inflect.plural(/$/, "s")
   //inflect.plural(/s$/i, "s")
   //inflect.plural(/^(ax|test)is$/i, '\1es')
   //inflect.plural(/(octop|vir)us$/i, '\1i')
   //inflect.plural(/(octop|vir)i$/i, '\1i')
   //inflect.plural(/(alias|status)$/i, '\1es')
   //inflect.plural(/(bu)s$/i, '\1ses')
   //inflect.plural(/(buffal|tomat)o$/i, '\1oes')
   //inflect.plural(/([ti])um$/i, '\1a')
   //inflect.plural(/([ti])a$/i, '\1a')
   //inflect.plural(/sis$/i, "ses")
   //inflect.plural(/(?:([^f])fe|([lr])f)$/i, '\1\2ves')
   //inflect.plural(/(hive)$/i, '\1s')
   //inflect.plural(/([^aeiouy]|qu)y$/i, '\1ies')
   //inflect.plural(/(x|ch|ss|sh)$/i, '\1es')
   //inflect.plural(/(matr|vert|ind)(?:ix|ex)$/i, '\1ices')
   //inflect.plural(/^(m|l)ouse$/i, '\1ice')
   //inflect.plural(/^(m|l)ice$/i, '\1ice')
   //inflect.plural(/^(ox)$/i, '\1en')
   //inflect.plural(/^(oxen)$/i, '\1')
   //inflect.plural(/(quiz)$/i, '\1zes')
};

return inflections;

}
} // namespace Blast


