#include "Command_parse.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace cli
{

struct command_parse::Impl
{
  Impl();
  ~Impl();

  error_result parse(const std::string& command,
                     std::vector<std::string>& argument_list);
  error_result parse(const int argc, const char **argv,
                     std::vector<std::string>& argument_list);
  error_result get_word(std::string &arument_line,
                        std::vector<std::string>& argument_list);
  error_result get_string(std::string &argument_line,
                          std::vector<std::string>& argument_list);
};

static const char* white_spaces = " \t\n\r\f\v";

// command_parse ================================================================

command_parse::command_parse()
  : m_p_impl(new Impl)
{
}

command_parse::~command_parse()
{
  delete m_p_impl;
}

error_result command_parse::parse(const std::string& command,
                                  std::vector<std::string>& argument_list)
{
  return m_p_impl->parse(command, argument_list);
}

error_result command_parse::parse(const int argc, const char** argv,
                                  std::vector<std::string>& argument_list)
{
  return m_p_impl->parse(argc, argv, argument_list);
}

// command_parse::Impl ==========================================================

command_parse::Impl::Impl()
{
}

command_parse::Impl::~Impl()
{
}

error_result command_parse::Impl::parse(const std::string& command,
                                        std::vector<std::string>& argument_list)
{
  error_result return_value = ERROR_NONE;
  std::string argument_line = command;
  size_t i = argument_line.find_first_not_of(white_spaces);
  argument_line.erase(0, i);
  while ((false == argument_line.empty()) && (ERROR_NONE == return_value))
  {
    switch (argument_line[0])
    {
    case '\"':
      return_value = get_string(argument_line, argument_list);
      break;
    case '\'':
      return_value = get_string(argument_line, argument_list);
      break;
    default:
      return_value = get_word(argument_line, argument_list);
      break;
    }
    size_t i = argument_line.find_first_not_of(white_spaces);
    argument_line.erase(0, i);
  }
  return return_value;
}

error_result command_parse::Impl::parse(const int argc, const char **argv,
                                        std::vector<std::string>& argument_list)
{
  error_result return_value = ERROR_NONE;
  for (size_t i = 0; i < argc; i++)
  {
    argument_list.push_back(argv[i]);
  }
  if (0 >= argc)
  {
    return_value = ERROR_NOT_FOUND;
  }
  return return_value;
}

error_result command_parse::Impl::get_word(
  std::string& argument_line, std::vector<std::string>& argument_list)
{
  size_t i = argument_line.find_first_of(white_spaces);
  argument_list.push_back(argument_line.substr(0, i));
  argument_line.erase(0, i);
  return ERROR_NONE;
}

error_result command_parse::Impl::get_string(
  std::string& argument_line, std::vector<std::string>& argument_list)
{
  error_result return_value = ERROR_NONE;
  char delimiter = argument_line[0];
  argument_line.erase(0, 1);
  size_t i = argument_line.find_first_of(delimiter);
  if (i < argument_line.size())
  {
    argument_list.push_back(argument_line.substr(0, i));
    argument_line.erase(0, i + 1);
  }
  else
  {
    return_value = ERROR_MALFORMED;
  }
  return return_value;
}

}
