#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include "error.h"

#include <string>
#include <vector>

namespace cli
{

class Command_line
{
public:
  
  typedef error_result (*command_function_t)(const std::vector<std::string>&);
  
  Command_line();
  virtual ~Command_line();

  error_result run(const std::vector<std::string>& argument_list);
  error_result add(const std::string &command,
                   const command_function_t function);

private:
  
  Command_line& operator=(const Command_line&);
  Command_line(const Command_line&);
  
  struct Impl;
  Impl *m_p_impl;
};

}

#endif // #define COMMAND_LINE_H
