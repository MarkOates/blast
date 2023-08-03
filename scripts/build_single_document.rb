
require 'json'
require 'yaml'
require 'cgi'
require_relative 'build_documentation/doc_creator.rb'
require_relative 'build_documentation/tree_builder.rb'


require 'fileutils' # for making a directory if it doesn't exist



def time_diff_milli(start, finish)
   (finish - start) * 1000.0
end



t1 = Time.now
tree_builder = TreeBuilder.new
doc_creator = DocCreator.new(yamls: tree_builder.yamls)



# Our constants
local_path = "/Users/markoates/Desktop/allegro_flare_docs/"



# Create table of contents for each URL 

index_doc_filename = local_path + 'index.htm'
index_doc_content = doc_creator.create_table_of_contents_doc(page_title: "Index of AllegroFlare Components", yamls: tree_builder.yamls)
  IO.write(index_doc_filename, index_doc_content)



# Create doc page for each yaml


tree_builder.yamls.each do |filename, yaml|
  page_title = filename
  doc_page_filename = filename.sub(/\.q\.yml$/, '') + ".html"
  final_doc_file_path = local_path + doc_page_filename
  FileUtils.mkdir_p(File.dirname(final_doc_file_path))


  # Format the page title from the filename
  page_title = filename.sub(/.*?quintessence\//, '')
  page_title = page_title.sub(/\.q\.yml$/, '')

  main_content = doc_creator.generate_doc_listing(filename: filename, yaml: yaml)
  #main_content = "Foobar"


  IO.write(final_doc_file_path, doc_creator.generate_single_component_doc(page_title: page_title, main_content: main_content)) 
end


t2 = Time.now
puts "Written in #{time_diff_milli(t1, t2)} msec."
