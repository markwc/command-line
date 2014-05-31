#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <string>
#include <vector>

namespace cli
{

enum error_result
{
  ERROR_NONE = 0,
  ERROR_NOT_INITIALIZED = -1,
  ERROR_NOT_FOUND = -2,
  ERROR_MALFORMED = -3
};
  
class Command_line
{
public:
  
  typedef error_result (*command_function_t)(const std::vector<std::string>&);
  
  Command_line();
  virtual ~Command_line();

  error_result process_command(const std::string& line);
  error_result process_command(const int argc, const char** argv);
  error_result process_command(const std::vector<std::string>& argument_list);
  error_result add_command(const std::string &command,
                           const command_function_t function);

private:
  
  Command_line& operator=(const Command_line&);
  Command_line(const Command_line&);
  
  struct Impl;
  Impl *m_p_impl;
};

}

#endif // #define COMMAND_LINE_H
