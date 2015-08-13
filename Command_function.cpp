#include "Command_function.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace cli
{
struct Command_function::Impl
{
  std::map<std::string, command_function_t> function_map;

  Impl()
  {
  }
  ~Impl()
  {
  }

  error_result run(const std::vector<std::string>& argument_list)
  {
    error_result err = ERROR_NONE;
    if (function_map.end() != function_map.find(argument_list[0]))
    {
      function_map[argument_list[0]](argument_list);
    }
    else
    {
      err = ERROR_NOT_FOUND;
    }
    return err;
  }

  error_result add(const std::string& command,
                   const command_function_t function)
  {
    error_result err = ERROR_NONE;
    if (0 != function)
    {
      function_map[command] = function;
    }
    else
    {
      err = ERROR_NOT_INITIALIZED;
    }
    return err;
  }
};

Command_function::Command_function() : m_p_impl(new Impl)
{
}

Command_function::~Command_function()
{
  delete m_p_impl;
}

error_result
    Command_function::run(const std::vector<std::string>& argument_list)
{
  return m_p_impl->run(argument_list);
}

error_result Command_function::add(const std::string& command,
                                   const command_function_t function)
{
  return m_p_impl->add(command, function);
}
}
