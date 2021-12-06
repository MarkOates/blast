class DocCreator
  attr_reader :yamls, :dependents

  def initialize(yamls:)
    @yamls = yamls
    @dependents = {}
  end

  def generate_doc
    result =  "<!DOCTYPE html>\n"
    result += "<head>\n"
    result += generate_css
    result += "</head>\n"
    result += "<body>\n"

    result += "<h1>TOC</h1>\n"
    result += "<ul>\n"
    yamls.each do |filename, yaml|
      result += "  <li><a href=\"\##{filename}\">#{filename}</a></li>\n"
    end
    result += "</ul>\n"

    result += "<h1>Components</h1>\n"
    yamls.each do |filename, yaml|
      result += "<ul>\n"
      result += "  <div class=\"component\">\n"
      result += "    <h3 id=\"#{filename}\">#{filename}</h3>\n"
      #result += "    <h4>Overview<h4>\n"

        result += "     <table>\n"
        properties = yaml['properties']
        unless properties.nil?
          properties.each do |property|
            result += "<tr>\n"
            property_name = escape_html_chars(property['name'])
            property_type = escape_html_chars(property['type'])
            property_is_private = property['private']

            css_class = property_is_private ? 'private_property' : 'property'
            result += "  <td class=\"#{css_class}\">#{property_name}</td>\n"
            result += "  <td class=\"#{css_class}\">#{property_type}</td>\n"
            result += "</tr>\n"
          end
        end
        result += "    </table>\n"

        result += "     <table>\n"
        methods = yaml['functions']
        unless methods.nil?
          methods.each do |method|
            result += "<tr>\n"
            method_name = escape_html_chars(method['name'])
            num_method_parameters = method['parameters']&.count
            method_is_private = method['private']

            css_class = method_is_private ? 'private_method' : 'method'
            result += "  <td class=\"#{css_class}\">#{method_name}(#{num_method_parameters})</td>\n"
            result += "</tr>\n"
          end
        end
        result += "    </table>\n"

      # result += "</ul>\n"
      # result += "<ul>\n"
        result += "     <table>\n"
        dependencies = yaml['dependencies']
        unless dependencies.nil?
          dependencies.each do |dependency|
            result += "<tr>\n"
            dependency_symbol = dependency['symbol']
            (dependents[dependency_symbol] ||= []) << filename
            ##dependency_is_private = dependency['private']
            full_dependency_json_string = escape_html_chars(dependency.to_s)

            ##css_class = dependency_is_private ? 'private_dependency' : 'dependency'
            result += "  <td class=\"dependency\">#{full_dependency_json_string}</td>\n"
            result += "</tr>\n"
          end
        end
        result += "    </table>\n"


      result += "  </div>\n"
      result += "</ul>\n"
    end



    result += "<h1>Dependents</h1>\n"
    result += "<pre>\n"
    result += JSON.pretty_generate(dependents) + "\n"
    result += "</pre>\n"


    result += "</body>"
    result
  end

  private

  def escape_html_chars(input)
    CGI.escapeHTML(input.to_s)
  end

  def generate_css
    result =  "<style>\n"
    result += "*\n"
    result += "{\n"
    result += "  font-family: 'Arial';\n"
    result += "  padding: 3px 20px;\n"
    result += "}\n"
    result += "table td\n"
    result += "{\n"
    result += "  padding: 3px 20px;\n"
    result += "}\n"
    result += ".property\n"
    result += "{\n"
    result += "  color: blue;\n"
    result += "}\n"
    result += ".private_property\n"
    result += "{\n"
    result += "  color: lightblue;\n"
    result += "}\n"
    result += "\n"
    result += ".method\n"
    result += "{\n"
    result += "  color: red;\n"
    result += "}\n"
    result += "\n"
    result += ".private_method\n"
    result += "{\n"
    result += "  color: pink;\n"
    result += "}\n"
    result += "\n"
    result += ".dependency\n"
    result += "{\n"
    result += "  color: green;\n"
    result += "}\n"
    result += "\n"
    result += ".component\n"
    result += "{\n"
    result += "  padding: 20 10 20 10;\n"
    result += "  margin: 20 10 20 10;\n"
    result += "  background-color: #dfdfdf;\n"
    result += "}\n"
    result += "\n"
    result += ".component h3\n"
    result += "{\n"
    result += "}\n"
    result += "</style>\n"
    result
  end
end
