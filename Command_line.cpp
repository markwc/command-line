#include "Command_line.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Command_line::Impl
{
  std::map<std::string, command_function_t> function_map;

  Impl();
  ~Impl();

  int process_command(const std::string& line);
  int process_command(const int argc, const char **argv);
  int process_command(const std::vector<std::string> &argument_list);
  int add_command(const std::string &command, const command_function_t);
  int get_word(std::string &argument_line, std::vector<std::string> &argument_listn);
  int get_string(std::string &argument_line, std::vector<std::string> &argument_list);
};

static const char* white_spaces = " \t\n\r\f\v";

// Command_line ================================================================

Command_line::Command_line() : m_p_impl(new Impl)
{
}

Command_line::~Command_line()
{
  delete m_p_impl;
}

int Command_line::process_command(const std::string &line)
{
  return m_p_impl->process_command(line);
}

int Command_line::process_command(const int argc, const char** argv)
{
  return m_p_impl->process_command(argc, argv);
}

int Command_line::process_command(const std::vector<std::string>& argument_list)
{
  return m_p_impl->process_command(argument_list);
}

int Command_line::add_command(const std::string &command,
                              const command_function_t function)
{
  return m_p_impl->add_command(command, function);
}

// Command_line::Impl ==========================================================

Command_line::Impl::Impl()
{
}

Command_line::Impl::~Impl()
{
}

int Command_line::Impl::add_command(const std::string &command,
                                    const command_function_t function)
{
  int return_value = ERROR_NONE;
  if (0 != function)
  {
    function_map[command] = function;
  }
  else
  {
    return_value = ERROR_NOT_INITIALIZED;
  }
  return return_value;
}

int Command_line::Impl::process_command(const std::string &line)
{
  int return_value = ERROR_NONE;
  std::vector<std::string> argument_list;
  std::string argument_line = line;
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
  if (ERROR_NONE == return_value)
  {
    return_value = process_command(argument_list);
  }
  return return_value;
}

int Command_line::Impl::process_command(const int argc, const char **argv)
{
  std::vector<std::string> argument_list;
  for (size_t i = 0; i < argc; i++)
  {
    argument_list.push_back(argv[i]);
  }
  return process_command(argument_list);
}

int Command_line::Impl::process_command(
    const std::vector<std::string> &argument_list)
{
  int return_value = ERROR_NONE;
  if (function_map.end() != function_map.find(argument_list[0]))
  {
    function_map[argument_list[0]](argument_list);
  }
  else
  {
    return_value = ERROR_NOT_FOUND;
  }
  return return_value;
}

int Command_line::Impl::get_word(std::string& argument_line, std::vector<std::string>& argument_list)
{
  size_t i = argument_line.find_first_of(white_spaces);
  argument_list.push_back(argument_line.substr(0, i));
  argument_line.erase(0, i);
  return ERROR_NONE;
}

int Command_line::Impl::get_string(std::string& argument_line, std::vector<std::string>& argument_list)
{
  int return_value = ERROR_NONE;
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
    return_value = ERROR_NOT_FOUND;
  }
  return return_value;
}
