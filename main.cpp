#include "Command_line.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Command_line::Impl
{
  Impl();
  ~Impl();
  int process_line(const std::string& line);
  int add_command(const std::string& command, const command_function);
  std::map<std::string, command_function> function_map;
};

Command_line::Command_line() : m_p_impl(new Impl)
{
}

Command_line::~Command_line()
{
  delete m_p_impl;
}

int Command_line::add_command(const std::string& command, command_function function)
{
  m_p_impl->add_command(command, function);
}

int Command_line::process_line(const std::string& line)
{
  m_p_impl->process_line(line);
}

//==============================================================================

static const char* white_spaces = " \t\n\r";

Command_line::Impl::Impl()
{
}

Command_line::Impl::~Impl()
{
}

int Command_line::Impl::add_command(const std::string& command, command_function function)
{
  function_map[command] = function;
}

int Command_line::Impl::process_line(const std::string& line)
{
  std::cerr << __FUNCTION__ << ": \"" << line << "\"" << std::endl;
  size_t begin_of_command = line.find_first_not_of(white_spaces);
  size_t i = line.substr(begin_of_command).find_first_of(white_spaces);
  std::string command = line.substr(begin_of_command,begin_of_command+i);
  i = command.find_first_of(white_spaces);
  command.erase(i);
  std::cerr << "Impl::" << __FUNCTION__ << ": command = \"" << command << "\"" << std::endl;
  i = line.substr(begin_of_command).find_first_of(white_spaces);
  std::string argument_line = line.substr(begin_of_command+i);
  i = argument_line.find_first_not_of(white_spaces);
  argument_line.erase(0,i);
  std::vector<std::string> argument_list;
  while (false == argument_line.empty())
  {
    i = argument_line.find_first_of(white_spaces);
    argument_list.push_back(argument_line.substr(0,i));
    argument_line.erase(0,i);
    i = argument_line.find_first_not_of(white_spaces);
    argument_line.erase(0,i);
  }
  function_map[command](argument_list);
}

//==============================================================================

static std::string ls_command = "ls";
static int ls_function(const std::vector<std::string>& arguments)
{
  for (size_t i = 0; i < arguments.size(); i++)
  {
    std::cerr << __FUNCTION__ << ": argument_list[" << i << "] = \"" << arguments[i] << "\"" << std::endl;
  }
  return 0;
}

int main(int argc, char** argv)
{
  Command_line* cli = new Command_line();
  cli->add_command(ls_command, ls_function);
  cli->process_line("  ls -i test -qrt blah ");
  std::cerr << __FUNCTION__ << std::endl;
  delete cli;
  return 0;
}

