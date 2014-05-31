#include "Command_line.h"

#include <iostream>

#include <gtest/gtest.h>

//====================================================================

static std::vector<std::string> last_arguments;

static int test_function(const std::vector<std::string> &arguments)
{
  last_arguments.clear();
  last_arguments = arguments;
  return 0;
}

//====================================================================

TEST(Command_line, command_found_or_not)
{
  Command_line *cli = new Command_line();

  ASSERT_EQ(0, cli->add_command("test", test_function));
  ASSERT_EQ(-1, cli->process_command("testy"));
  ASSERT_EQ(0, cli->process_command("test"));
  delete cli;
}

TEST(Command_line, trime_white_space)
{
  Command_line *cli = new Command_line();

  ASSERT_EQ(0, cli->add_command("test", test_function));
  ASSERT_EQ(0, cli->process_command("test"));
  ASSERT_EQ(0, cli->process_command(" test "));
  ASSERT_EQ(0, cli->process_command("\ttest\t"));
  ASSERT_EQ(0, cli->process_command("\ntest\n"));
  ASSERT_EQ(0, cli->process_command("\rtest\r"));
  ASSERT_EQ(0, cli->process_command("\vtest\v"));
  ASSERT_EQ(0, cli->process_command("\ftest\f"));
  delete cli;
}

TEST(Command_line, string_arguments)
{
  Command_line *cli = new Command_line();
  ASSERT_EQ(0, cli->add_command("test", test_function));
  ASSERT_EQ(0, cli->process_command("test \" this is my string! \""));
  ASSERT_EQ(" this is my string! ", last_arguments[1]);
  ASSERT_EQ(0, cli->process_command("test ' this is my string! '"));
  ASSERT_EQ(" this is my string! ", last_arguments[1]);
  delete cli;
}
