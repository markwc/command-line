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
  
  Command_parse();
  virtual ~Command_parse();

  error_result parse(const std::string& command,
                     std::vector<std::string>& argument_list);
  error_result parse(const int argc, const char** argv,
                     std::vector<std::string>& argument_list);

private:
  
  Command_parse& operator=(const Command_parse&);
  Command_parse(const Command_parse&);
  
  struct Impl;
  Impl *m_p_impl;
};

}

#endif // #define COMMAND_PARSE_H
