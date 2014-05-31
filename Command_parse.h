#ifndef COMMAND_PARSE_H
#define COMMAND_PARSE_H

#include "error.h"

#include <string>
#include <vector>

namespace cli
{

class command_parse
{
public:
  
  command_parse();
  virtual ~command_parse();

  error_result parse(const std::string& command,
                     std::vector<std::string>& argument_list);
  error_result parse(const int argc, const char** argv,
                     std::vector<std::string>& argument_list);

private:
  
  command_parse& operator=(const command_parse&);
  command_parse(const command_parse&);
  
  struct Impl;
  Impl *m_p_impl;
};

}

#endif // #define COMMAND_PARSE_H
