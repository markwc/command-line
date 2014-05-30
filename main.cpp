#include "Command_line.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Command_line::Impl
{
  std::map<std::string, command_function> function_map;
  
  Impl();
  ~Impl();
  
  int process_command(const std::string& line);
  int process_command(const int argc, const char** argv);
  int process_command(const std::vector<std::string>& argument_list);
  int add_command(const std::string& command, const command_function);
  std::string get_word(std::string& argument_line);
  std::string get_string(std::string& argument_line);
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

int Command_line::process_command(const std::string& line)
{
  m_p_impl->process_command(line);
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

int Command_line::Impl::process_command(const std::string& line)
{
  std::cerr << __FUNCTION__ << ": \"" << line << "\"" << std::endl;
  std::vector<std::string> argument_list;
  std::string argument_line = line;
  size_t i = argument_line.find_first_not_of(white_spaces);
  argument_line.erase(0,i);
  while (false == argument_line.empty())
  {
    switch(argument_line[0])
    {
    case'\"':
      argument_list.push_back(get_string(argument_line));
      break;
    case'\'':
      argument_list.push_back(get_string(argument_line));
      break;
    default:
      argument_list.push_back(get_word(argument_line));
      break;
    }
    size_t i = argument_line.find_first_not_of(white_spaces);
    argument_line.erase(0,i);
  }
  function_map[argument_list[0]](argument_list);
  return 0;
}

int Command_line::Impl::process_command(const int argc, const char** argv)
{
  std::vector<std::string> argument_list;
  for (size_t i=0; i < argc; i++)
  {
    argument_list.push_back(argv[i]);
  }
  function_map[argument_list[0]](argument_list);
  return 0;
}

std::string Command_line::Impl::get_word(std::string& argument_line)
{
  std::cerr << "Impl::" << __FUNCTION__ << std::endl;
  size_t i = argument_line.find_first_of(white_spaces);
  std::string result = argument_line.substr(0,i);
  argument_line.erase(0,i);
  return result;
}

std::string Command_line::Impl::get_string(std::string& argument_line)
{
  char delimiter = argument_line[0];
  argument_line.erase(0,1);
  size_t i = argument_line.find_first_of(delimiter);
  std::string result = argument_line.substr(0,i);
  argument_line.erase(0,i+1);
  return result;
}
//====================================================================

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
  cli->process_command("  ls -i test -qrt blah \" more blah blah \"");
  std::cerr << __FUNCTION__ << std::endl;
  delete cli;
  return 0;
}

