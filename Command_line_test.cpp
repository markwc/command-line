#include "Command_line.h"

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
  ASSERT_EQ(ERROR_NOT_INITIALIZED, cli->add_command("test", 0));
  delete cli;
}

TEST(Command_line, command_found_or_not)
{
  Command_line *cli = new Command_line();
  ASSERT_EQ(ERROR_NONE, cli->add_command("test", test_function));
  ASSERT_EQ(ERROR_NOT_FOUND, cli->process_command("testy"));
  ASSERT_EQ(ERROR_NONE, cli->process_command("test"));
  delete cli;
}

TEST(Command_line, trime_white_space)
{
  Command_line *cli = new Command_line();

  ASSERT_EQ(ERROR_NONE, cli->add_command("test", test_function));
  ASSERT_EQ(ERROR_NONE, cli->process_command("test"));
  ASSERT_EQ(ERROR_NONE, cli->process_command(" test "));
  ASSERT_EQ(ERROR_NONE, cli->process_command("\ttest\t"));
  ASSERT_EQ(ERROR_NONE, cli->process_command("\ntest\n"));
  ASSERT_EQ(ERROR_NONE, cli->process_command("\rtest\r"));
  ASSERT_EQ(ERROR_NONE, cli->process_command("\vtest\v"));
  ASSERT_EQ(ERROR_NONE, cli->process_command("\ftest\f"));
  delete cli;
}

TEST(Command_line, proper_string_arguments)
{
  Command_line *cli = new Command_line();
  ASSERT_EQ(ERROR_NONE, cli->add_command("test", test_function));
  ASSERT_EQ(ERROR_NONE, cli->process_command("test \" this is my string! \""));
  ASSERT_EQ(" this is my string! ", last_arguments[1]);
  ASSERT_EQ(ERROR_NONE, cli->process_command("test ' this is my string! '"));
  ASSERT_EQ(" this is my string! ", last_arguments[1]);
  delete cli;
}

TEST(Command_line, malformed_string_arguments)
{
  Command_line *cli = new Command_line();
  ASSERT_EQ(ERROR_NONE, cli->add_command("test", test_function));
  ASSERT_EQ(ERROR_MALFORMED, cli->process_command("test \" this is my string! "));
  ASSERT_EQ(ERROR_MALFORMED, cli->process_command("test \' this is my string! "));
  ASSERT_EQ(ERROR_MALFORMED, cli->process_command("test this is my string! \""));
  ASSERT_EQ(ERROR_MALFORMED, cli->process_command("test this is my string! \'"));
  delete cli;
}

static int argc = 5;
static const char* argv[] = {"test", "arg1", "arg2", "arg3", "arg4"};

TEST(Command_line, arc_argv_arguments)
{
  Command_line *cli = new Command_line();
  ASSERT_EQ(ERROR_NONE, cli->add_command("test", test_function));
  ASSERT_EQ(ERROR_NONE, cli->process_command(argc, argv));
  for (size_t i = 0; i<argc; i++)
  {
    ASSERT_EQ(argv[i], last_arguments[i]);
  }
  delete cli;
}

