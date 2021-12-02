require 'json'
require 'yaml'
require 'cgi'

class TreeBuilder
  def puts_yamls
    puts yamls
  end

  def shell_yaml_find_command_results
    @shell_yaml_find_command_results ||= (`git grep "^  - name" | grep quintessence | grep q\.yml`).split("\n")
  end

  def component_basename(filename:)
    basename = `~/Repos/ncurses-art/bin/programs/project_filename_generator -x#{filename} -B`
  end

  def yamls
    result = {}
    processed_lines.map do |processed_line|
      #processed_line[:symbol]
      filename = processed_line[:filename]
      yaml = YAML.load(file_contents(filename: filename))
      result[filename] = yaml
      #(result[processed_line[:filename]] ||= []) << processed_line[:symbol]
      #processed_line[:symbol]
    end
    result
  end

  def file_contents(filename:)
    file = File.open(filename)
    file_data = file.read
    file.close
    return file_data
  end

  def rollup
    @rollup ||= begin
      result = {}
      processed_lines.each do |processed_line|
        #processed_line[:symbol]
        (result[processed_line[:filename]] ||= []) << processed_line[:symbol]
        #processed_line[:symbol]
      end
      result
    end
  end

  def processed_lines
    @processed_lines ||= begin
      shell_yaml_find_command_results.map do |shell_yaml_find_command_result|
        index = shell_yaml_find_command_result.index(": ")
        filename = shell_yaml_find_command_result[0...index]
        method = shell_yaml_find_command_result[(index + 11)..-1]
        dependents = []
        dependencies = []
        result = {
          filename: filename,
          # basename: component_basename(filename: filename),
          basename: '[not-set]',
          symbol: method,
          dependencies: dependencies,
          private_methods: [], # mostly not important, it represents a complex internal arrangement to resolve the implementation
          input_types: [],
          input_type_states: [ :requires_initialization ],
          internal_dependencies: [],
          external_dependencies: [],
          private_parent: [],
          private_static_data: [], # constants, methods that return values that will not change
        }
        #puts result
      end
    end
  end
end



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



def time_diff_milli(start, finish)
   (finish - start) * 1000.0
end



t1 = Time.now
tree_builder = TreeBuilder.new
doc_creator = DocCreator.new(yamls: tree_builder.yamls)
IO.write("documentation/index.html", doc_creator.generate_doc)
t2 = Time.now
puts "Written in #{time_diff_milli(t1, t2)} msec."
#tree_builder.puts_yamls



# make a new method with a form
# have an abstraction up/down or in/out


=begin

class ClassA
  def method_a
    command_result = `git grep "^  - name" | grep q\.yml`
    puts command_result
  end
  def method_a2
    command_result = `git grep "^  - name" | grep q\.yml`
    puts command_result
  end
  def method_a3
    command_result = `git grep "^  - name" | grep q\.yml`
    puts command_result
  end
end

class ClassB
  def method_b
    command_result = `git grep "^  - name" | grep q\.yml`
    puts command_result
  end
end

class ClassC
  def method_c
    command_result = `git grep "^  - name" | grep q\.yml`
    puts command_result
  end
end


# ///////////////////

ClassA
  - method_a
  - method_a2
  - method_a3

ClassB
  - method_b

ClassC
  - method_c

=end
