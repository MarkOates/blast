class DocCreator
  attr_reader :yamls, :dependents, :doc

  def initialize(yamls:)
    @yamls = yamls
    @dependents = {}
  end

  def clubcatt_insert_content_options
    [
      'Visit CLUBCATT for <a href="https://clubcatt.com">cat shirts, cat mugs, cat puzzles, and more</a>.',
      'Check out <a href="https://clubcatt.com/collections/cat-shirts">cat shirts</a> available from CLUBCATT.',
      'CLUBCATT has <a href="https://clubcatt.com">cat shirts, mugs, games and puzzles</a> you\'ll love',
      'Learn about cats at the <a href="https://clubcatt.com/blogs/cat-encyclopedia">Cat Encyclopedia</a>',
      'Grab cute <a href="https://clubcatt.com/collections/cat-stickers">Cat stickers</a> for your laptop at CLUBCATT',
      'Get the best designed <a href="https://clubcatt.com">cat shirts</a> at clubatt.com',
      'Look no further than <a href="https://clubcatt.com">CLUBCATT</a> for cat shirts, cat mugs, and all kinds of cat-fancy stuff.',
    ]
  end

  def build_doc_listing_url_from_yaml_filename(yaml_filename:)
    # Format the page title from the filename
    page_title = yaml_filename.sub(/.*?quintessence\//, '')
    page_title = page_title.sub(/\.q\.yml$/, '')
    page_title
  end

  def build_parameters_string(parameters:)
    return "" if parameters.nil?
    results = [];
    parameters.each do |parameter|
      type = CGI::escapeHTML(parameter['type'])
      default_argument = CGI::escapeHTML(parameter['default_argument'].to_s)

      results << (type + " " + parameter['name'] + "=" + default_argument)
    end
    results.join(", ")
  end

  def create_table_of_contents_doc(page_title:, yamls:)
    template = File.read("/Users/markoates/Repos/blast/scripts/build_documentation/templates/layouts/primary_layout.template.htm")

    # page title
    template.gsub!("[page_title]", page_title)

    # main content
    main_content = generate_table_of_contents(yamls: yamls)
    primary_page_html_content = "<h1>#{page_title}</h1>" + main_content
    template.gsub!("[main_content]", primary_page_html_content);

    # clubcatt insert content
    sponsor_header = "    <h2>Sponsor</h2>\n"
    clubatt_insert_content = sponsor_header + "<p>" + clubcatt_insert_content_options.sample + "</p>"
    template.gsub!("[main_content_clubcatt_insert]", clubatt_insert_content)

    # main content
    footer_content = 'AllegroFlare - Visit us on <a href="https://github.com/allegroflare/allegro_flare">GitHub</a>'
    template.gsub!("[footer_content]", footer_content);

    template
  end

  def generate_table_of_contents(yamls:)
    result = ""
    result += "<h2>Components</h2>\n"
    result += "<div id=\"components_index_list\">\n"
    result += "<ul>\n"
    yamls.each do |filename, yaml|
      doc_listing_url = build_doc_listing_url_from_yaml_filename(yaml_filename: filename)
      component_name = doc_listing_url
      result += "  <li><a rel=\"nofollow\" href=\"/docs/#{doc_listing_url}\">#{component_name}</a></li>\n"
    end
    result += "</ul>\n"
    result += "</div>\n"
  end

  def generate_single_component_doc(page_title:, main_content:)
    github_component_url_prefix = "https://github.com/allegroflare/allegro_flare/blob/master/"
    template = File.read("/Users/markoates/Repos/blast/scripts/build_documentation/templates/layouts/primary_layout.template.htm")
    #page_title = "Inserted Page Title"


    # page title
    template.gsub!("[page_title]", page_title)
 

    # path files
    cpp_github_url = github_component_url_prefix + "src/" + page_title + ".cpp"
    hpp_github_url = github_component_url_prefix + "include/" + page_title + ".hpp"
    quintessence_github_url = github_component_url_prefix + "quintessence/" + page_title + ".q.yml"
    test_github_url = github_component_url_prefix + "tests/" + page_title + "Test.cpp"

    # main content
    primary_page_html_content = "<h1>#{page_title}</h1>"
    primary_page_html_content += "<p>view source (<a href='#{cpp_github_url}'>cpp</a>, <a href='#{hpp_github_url}'>hpp</a>, <a href='#{quintessence_github_url}'>quintessence</a>) &bull; view tests (<a href='#{test_github_url}'>test file</a>)</p>"
    primary_page_html_content += main_content
    template.gsub!("[main_content]", primary_page_html_content);


    # clubcatt insert content
    sponsor_header = "    <h3>Sponsor</h3>\n"
    clubatt_insert_content = sponsor_header + "<p>" + clubcatt_insert_content_options.sample + "</p>"
    template.gsub!("[main_content_clubcatt_insert]", clubatt_insert_content)


    # main content
    footer_content = 'AllegroFlare - Visit us on <a href="https://github.com/allegroflare/allegro_flare">GitHub</a>'
    template.gsub!("[footer_content]", footer_content);



    template
  end

  def generate_doc_listing(filename:, yaml:)
    result = ""
    result += "<ul>\n"
    result += "  <div class=\"component\">\n"
    result += "    <h3 id=\"#{filename}\">#{filename}</h3>\n"
    result += "    <h4>Overview<h4>\n"

    result += "    <h3>Properties</h3>\n"

      properties = yaml['properties']
      if properties.nil?
        result += "<p>This class contains no properties</p>"
      else
        result += "<div class=\"property-box properties\">"
        result += "     <table>\n"
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
        result += "    </table>\n"
        result += "</div>"
      end


      # Methods

      result += "    <h3>Methods</h3>\n"

      functions = yaml['functions'] ||= []
      methods = yaml['methods'] ||= []

      methods.concat(functions);

      if methods.nil?
        result += "<p>This class contains no methods</p>"
      else
        result += "<div class=\"property-box methods\">"
        result += "     <table>\n"
        methods.each do |method|
          result += "<tr>\n"
          method_name = escape_html_chars(method['name'])
          #num_method_parameters = method['parameters']&.count
          method_parameters = build_parameters_string(parameters: method['parameters'])
          method_is_private = method['private']

          css_class = method_is_private ? 'private_method' : 'method'
          result += "  <td class=\"#{css_class}\">#{method_name}(#{method_parameters})</td>\n"
          result += "</tr>\n"
        end
        result += "    </table>\n"
        result += "</div>"
      end

      result += "    <h3>Dependencies</h3>\n"
    # result += "</ul>\n"
    # result += "<ul>\n"
      dependencies = yaml['dependencies']
      if dependencies.nil?
        result += "<p>This class contains no dependencies</p>"
      else
        result += "<div class=\"property-box dependencies\">"
        result += "     <table>\n"
        dependencies.each do |dependency|
          result += "<tr>\n"
          dependency_symbol = dependency['symbol']
          sanitized_dependency_symbol = dependency_symbol.to_s.gsub("::", "/").gsub("*", "")
          (dependents[sanitized_dependency_symbol] ||= []) << (filename.gsub("quintessence/", "").gsub(".q.yml", ""))
          ##dependency_is_private = dependency['private']
          full_dependency_json_string = escape_html_chars(dependency.to_s)

          ##css_class = dependency_is_private ? 'private_dependency' : 'dependency'
          result += "  <td class=\"dependency\">#{full_dependency_json_string}</td>\n"
          result += "</tr>\n"
        end
        result += "    </table>\n"
        result += "</div>"
      end


    result += "  </div>\n"
    result += "</ul>\n"
    result
  end

  def generate_doc
    result =  "<!DOCTYPE html>\n"
    result += "<head>\n"
    result += generate_css
    result += "</head>\n"
    result += "<body>\n"

    result += "<h1>Table of Contents</h1>\n"
    result += "<ul>\n"
    yamls.each do |filename, yaml|
      result += "  <li><a href=\"\##{filename}\">#{filename}</a></li>\n"
    end
    result += "</ul>\n"

    result += "<h1>Components</h1>\n"
    yamls.each do |filename, yaml|
      result += generate_doc_listing(filename: filename, yaml: yaml)
    end



    result += "<h1>Dependents</h1>\n"
    result += "<pre>\n"
    result += JSON.pretty_generate(dependents) + "\n"
    result += "</pre>\n"


    result += "</body>"
    result
  end

 

  def generate_dependents_json
    JSON.pretty_generate(dependents)
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
