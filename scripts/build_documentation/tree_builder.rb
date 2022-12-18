class String
  # colorization
  def colorize(color_code)
    "\e[#{color_code}m#{self}\e[0m"
  end

  def red
    colorize(31)
  end

  def green
    colorize(32)
  end

  def yellow
    colorize(33)
  end

  def blue
    colorize(34)
  end

  def pink
    colorize(35)
  end

  def light_blue
    colorize(36)
  end
end


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
      begin
      yaml = YAML.load(file_contents(filename: filename))
      rescue Exception => e
        puts "[blast/build_documentation/tree_builder.rb] error: An error occurred when attempting to parse content from the file \"#{filename}\".".red
        puts "#{e.class} - #{e.message}"
        raise StandardError.new("build error.")
      end
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
