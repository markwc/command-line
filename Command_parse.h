#ifndef COMMAND_PARSE_H
#define COMMAND_PARSE_H

#include "error.h"

#include <string>
#include <vector>

namespace cli
{
class Command_parse
{
public:
  /// Constructor.
  Command_parse();
  /// Destructor.
  virtual ~Command_parse();

  /// Parse a string of arguments into an arguement list.
  /// @param[in]  command The command string of arguments.
  /// @param[out] argument_list Each argument in command becomes a
  /// vector element in argument_list.
  error_result parse(const std::string& command,
                     std::vector<std::string>& argument_list);
  
  /// Parse a pointer to string arguments into an arguement list.
  /// @param[in]  argc The number of string arguments.
  /// @param[in]  argv The pointer to the string arguments.
  /// @param[out] argument_list Each argument in command becomes a
  /// vector element in argument_list.
  error_result parse(const int argc,
                     const char** argv,
                     std::vector<std::string>& argument_list);

private:
  Command_parse& operator=(const Command_parse&);
  Command_parse(const Command_parse&);

  struct Impl;
  Impl* m_p_impl;
};
}

#endif  // #define COMMAND_PARSE_H
