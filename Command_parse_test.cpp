#include "Command_parse.h"

#include <iostream>

#include <gtest/gtest.h>

using namespace cli;

//====================================================================

TEST(Command_parse, trim_white_space)
{
  Command_parse* cli = new Command_parse();
  std::vector<std::string> argument_list;
  ASSERT_EQ(ERROR_NONE, cli->parse("test", argument_list));
  ASSERT_EQ("test", argument_list[0]);
  ASSERT_EQ(ERROR_NONE, cli->parse(" test ", argument_list));
  ASSERT_EQ("test", argument_list[0]);
  ASSERT_EQ(ERROR_NONE, cli->parse("\ttest\t", argument_list));
  ASSERT_EQ("test", argument_list[0]);
  ASSERT_EQ(ERROR_NONE, cli->parse("\ntest\n", argument_list));
  ASSERT_EQ("test", argument_list[0]);
  ASSERT_EQ(ERROR_NONE, cli->parse("\rtest\r", argument_list));
  ASSERT_EQ("test", argument_list[0]);
  ASSERT_EQ(ERROR_NONE, cli->parse("\vtest\v", argument_list));
  ASSERT_EQ("test", argument_list[0]);
  ASSERT_EQ(ERROR_NONE, cli->parse("\ftest\f", argument_list));
  ASSERT_EQ("test", argument_list[0]);
  delete cli;
}

TEST(Command_parse, proper_string_arguments)
{
  Command_parse* cli = new Command_parse();
  std::vector<std::string> argument_list;
  ASSERT_EQ(ERROR_NONE,
            cli->parse("test \" this is my string! \"", argument_list));
  ASSERT_EQ(" this is my string! ", argument_list[1]);
  argument_list.clear();
  ASSERT_EQ(ERROR_NONE,
            cli->parse("test ' this is my string! '", argument_list));
  ASSERT_EQ(" this is my string! ", argument_list[1]);
  delete cli;
}

TEST(Command_parse, malformed_string_arguments)
{
  Command_parse* cli = new Command_parse();
  std::vector<std::string> argument_list;
  ASSERT_EQ(ERROR_MALFORMED,
            cli->parse("test \" this is my string! ", argument_list));
  ASSERT_EQ(ERROR_MALFORMED,
            cli->parse("test \' this is my string! ", argument_list));
  ASSERT_EQ(ERROR_MALFORMED,
            cli->parse("test this is my string! \"", argument_list));
  ASSERT_EQ(ERROR_MALFORMED,
            cli->parse("test this is my string! \'", argument_list));
  delete cli;
}

static int argc = 5;
static const char* argv[] = { "test", "arg1", "arg2", "arg3", "arg4" };

TEST(Command_parse, arc_argv_arguments)
{
  Command_parse* cli = new Command_parse();
  std::vector<std::string> argument_list;
  ASSERT_EQ(ERROR_NONE, cli->parse(argc, argv, argument_list));
  for (size_t i = 0; i < argc; i++)
  {
    ASSERT_EQ(argv[i], argument_list[i]);
  }
  delete cli;
}
