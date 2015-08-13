#ifndef COMMAND_FUNCTION_H
#define COMMAND_FUNCTION_H

#include "error.h"

#include <string>
#include <vector>

namespace cli
{
class Command_function
{
public:
  typedef error_result (*command_function_t)(const std::vector<std::string>&);

  Command_function();
  virtual ~Command_function();

  error_result run(const std::vector<std::string>& argument_list);
  error_result add(const std::string& command,
                   const command_function_t function);

private:
  Command_function& operator=(const Command_function&);
  Command_function(const Command_function&);

  struct Impl;
  Impl* m_p_impl;
};
}

#endif  // #define COMMAND_FUNCTION_H
