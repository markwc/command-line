#include "Command_line.cpp"

#include <iostream>

#include <gtest/gtest.h>

//====================================================================

static std::string ls_command = "ls";
static std::string set_command = "set";
static std::vector<std::string> last_arguments;

static int ls_function(const std::vector<std::string> &arguments)
{
  last_arguments = arguments;
  for (size_t i = 0; i < arguments.size(); i++)
  {
    std::cerr << __FUNCTION__ << ": argument_list[" << i << "] = \""
              << arguments[i] << "\"" << std::endl;
  }
  return 0;
}

static int set_function(const std::vector<std::string> &arguments)
{
  for (size_t i = 0; i < arguments.size(); i++) {
    std::cerr << __FUNCTION__ << ": argument_list[" << i << "] = \""
              << arguments[i] << "\"" << std::endl;
  }
  return 0;
}

//====================================================================

int main(int argc, char **argv)
{
  Command_line *cli = new Command_line();

  cli->add_command(ls_command, ls_function);
  cli->add_command(set_command, set_function);

  cli->process_command("  ls -i test -qrt blah \" more blah blah \"");
  ASSERT_EQ("ls", last_arguments[0]);
  cli->process_command("set this=30");

  delete cli;
  return 0;
}
