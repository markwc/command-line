#include "Command_function.h"

#include <iostream>

#include <gtest/gtest.h>

//====================================================================

static std::vector<std::string> last_arguments;

using namespace cli;

static error_result test_function(const std::vector<std::string> &arguments)
{
  last_arguments.clear();
  last_arguments = arguments;
  return cli::ERROR_NONE;
}

//====================================================================

TEST(Command_line, command_function_not_specified)
{
  Command_line *cli = new Command_line();
  ASSERT_EQ(ERROR_NOT_INITIALIZED, cli->add("test", 0));
  delete cli;
}

TEST(Command_line, command_found)
{
  Command_line *cli = new Command_line();
  std::vector<std::string> argument_list;
  ASSERT_EQ(ERROR_NONE, cli->add("test", test_function));
  argument_list.push_back("test");
  ASSERT_EQ(ERROR_NONE, cli->run(argument_list));
  delete cli;
}

TEST(Command_line, command_not_found)
{
  Command_line *cli = new Command_line();
  std::vector<std::string> argument_list;
  ASSERT_EQ(ERROR_NONE, cli->add("test", test_function));
  argument_list.push_back("testy");
  ASSERT_EQ(ERROR_NOT_FOUND, cli->run(argument_list));
  delete cli;
}

