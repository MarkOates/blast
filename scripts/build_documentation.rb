require 'json'
require 'yaml'
require 'cgi'
require_relative 'build_documentation/doc_creator.rb'
require_relative 'build_documentation/tree_builder.rb'




def time_diff_milli(start, finish)
   (finish - start) * 1000.0
end



t1 = Time.now
tree_builder = TreeBuilder.new
doc_creator = DocCreator.new(yamls: tree_builder.yamls)
IO.write("documentation/index.htm", doc_creator.generate_doc)
IO.write("documentation/dependents.json", doc_creator.generate_dependents_json)
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
