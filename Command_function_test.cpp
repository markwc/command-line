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

TEST(Command_function, Command_function_not_specified)
{
  Command_function *cli = new Command_function();
  ASSERT_EQ(ERROR_NOT_INITIALIZED, cli->add("test", 0));
  delete cli;
}

TEST(Command_function, command_found)
{
  Command_function *cli = new Command_function();
  std::vector<std::string> argument_list;
  ASSERT_EQ(ERROR_NONE, cli->add("test", test_function));
  argument_list.push_back("test");
  ASSERT_EQ(ERROR_NONE, cli->run(argument_list));
  delete cli;
}

TEST(Command_function, command_not_found)
{
  Command_function *cli = new Command_function();
  std::vector<std::string> argument_list;
  ASSERT_EQ(ERROR_NONE, cli->add("test", test_function));
  argument_list.push_back("testy");
  ASSERT_EQ(ERROR_NOT_FOUND, cli->run(argument_list));
  delete cli;
}

