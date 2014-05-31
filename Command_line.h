#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <string>
#include <vector>

class Command_line
{
public:
  
  enum result
  {
    ERROR_NONE = 0,
    ERROR_NOT_INITIALIZED = -1,
    ERROR_NOT_FOUND = -2
  };
  
  typedef int (*command_function)(const std::vector<std::string>&);
  
  Command_line();
  virtual ~Command_line();
  
  int process_command(const std::string& line);
  int process_command(const int argc, const char** argv);
  int process_command(const std::vector<std::string>& argument_list);
  int add_command(const std::string &command, const command_function function);

private:
  
  Command_line& operator=(const Command_line&);
  Command_line(const Command_line&);
  
  struct Impl;
  Impl *m_p_impl;
};

#endif // #define COMMAND_LINE_H
