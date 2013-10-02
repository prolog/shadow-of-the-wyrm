#pragma once
#include <string>
#include <vector>

// A class that allows access to the compiler/platform details used to
// compile Savage Lands.
class CompilationDetails
{
  public:
    std::vector<std::string> get_compilation_details() const;
    std::string get_compilation_details_string() const;

  protected:
    std::string get_platform() const;
    std::string get_compiler() const;
    std::vector<std::string> get_compile_time_options() const;
};

