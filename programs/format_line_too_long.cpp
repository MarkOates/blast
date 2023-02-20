#include <allegro5/allegro.h>

#include <iostream>
#include <string>
#include <vector>

std::string format_long_line(const std::string& long_line, int indentation_level) {
    // Initialize variables to hold the argument names and default values
    std::vector<std::string> arg_names;
    std::vector<std::string> arg_defaults;
    
    // Parse the long line to extract the argument names and default values
    size_t start_pos = long_line.find("(") + 1;
    size_t end_pos = long_line.find(")");
    std::string args_str = long_line.substr(start_pos, end_pos - start_pos);
    size_t comma_pos = 0;
    size_t prev_comma_pos = 0;
    do {
        comma_pos = args_str.find(",", prev_comma_pos);
        if (comma_pos == std::string::npos) {
            comma_pos = args_str.length();
        }
        std::string arg_str = args_str.substr(prev_comma_pos, comma_pos - prev_comma_pos);
        size_t equals_pos = arg_str.find("=");
        if (equals_pos == std::string::npos) {
            arg_names.push_back(arg_str);
            arg_defaults.push_back("");
        } else {
            arg_names.push_back(arg_str.substr(0, equals_pos));
            arg_defaults.push_back(arg_str.substr(equals_pos + 1));
        }
        prev_comma_pos = comma_pos + 1;
    } while (comma_pos < args_str.length());
    
    // Construct the formatted code with each argument on a new line
    std::string formatted_code = long_line.substr(0, start_pos);
    formatted_code += "\n";
    for (size_t i = 0; i < arg_names.size(); i++) {
        formatted_code += std::string(indentation_level, ' ');
        formatted_code += arg_names[i];
        if (!arg_defaults[i].empty()) {
            formatted_code += " = " + arg_defaults[i];
        }
        if (i < arg_names.size() - 1) {
            formatted_code += ",\n";
        } else {
            formatted_code += "\n";
        }
    }
    formatted_code += std::string(indentation_level - 4, ' ');
    formatted_code += ");\n";
    
    return formatted_code;
}

int main(int argc, char **argv)
{
    std::string long_line = "void my_function(std::string type=\"std::string\", std::string name=\"unnamed_parameter\", std::string default_value=\"\\\"\\\"\", std::vector<std::string> default_value_dependency_symbols={});";
    std::string formatted_code = format_long_line(long_line, 4);
    std::cout << formatted_code;
    
    return 0;
}

