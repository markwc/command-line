#include "Command_parse.h"

#include <iostream>

#include <gtest/gtest.h>

using namespace cli;

class Command_parse_test : public ::testing::Test
{
public:
  // gnu_radio_test constructor.
  Command_parse_test()
  {
  }
  // gnu_radio_test destructor.
  virtual ~Command_parse_test()
  {
  }

protected:
  Command_parse* m_p_test_component;
  // GTest setup function called for each TEST_F
  virtual void SetUp()
  {
    m_p_test_component = new Command_parse();
  }
  // GTest teardown function called after each TEST_F
  virtual void TearDown()
  {
    delete m_p_test_component;
  }
};

//====================================================================

TEST_F(Command_parse_test, trim_white_space)
{
  std::vector<std::string> argument_list;
  ASSERT_EQ(ERROR_NONE, m_p_test_component->parse("test", argument_list));
  ASSERT_EQ("test", argument_list[0]);
  ASSERT_EQ(ERROR_NONE, m_p_test_component->parse(" test ", argument_list));
  ASSERT_EQ("test", argument_list[0]);
  ASSERT_EQ(ERROR_NONE, m_p_test_component->parse("\ttest\t", argument_list));
  ASSERT_EQ("test", argument_list[0]);
  ASSERT_EQ(ERROR_NONE, m_p_test_component->parse("\ntest\n", argument_list));
  ASSERT_EQ("test", argument_list[0]);
  ASSERT_EQ(ERROR_NONE, m_p_test_component->parse("\rtest\r", argument_list));
  ASSERT_EQ("test", argument_list[0]);
  ASSERT_EQ(ERROR_NONE, m_p_test_component->parse("\vtest\v", argument_list));
  ASSERT_EQ("test", argument_list[0]);
  ASSERT_EQ(ERROR_NONE, m_p_test_component->parse("\ftest\f", argument_list));
  ASSERT_EQ("test", argument_list[0]);
}

TEST_F(Command_parse_test, proper_string_arguments)
{
  std::vector<std::string> argument_list;
  ASSERT_EQ(ERROR_NONE, m_p_test_component->parse(
                            "test \" this is my string! \"", argument_list));
  ASSERT_EQ(" this is my string! ", argument_list[1]);
  argument_list.clear();
  ASSERT_EQ(ERROR_NONE, m_p_test_component->parse("test ' this is my string! '",
                                                  argument_list));
  ASSERT_EQ(" this is my string! ", argument_list[1]);
}

TEST_F(Command_parse_test, malformed_string_arguments)
{
  std::vector<std::string> argument_list;
  ASSERT_EQ(ERROR_MALFORMED, m_p_test_component->parse(
                                 "test \" this is my string! ", argument_list));
  ASSERT_EQ(ERROR_MALFORMED, m_p_test_component->parse(
                                 "test \' this is my string! ", argument_list));
  ASSERT_EQ(ERROR_MALFORMED, m_p_test_component->parse(
                                 "test this is my string! \"", argument_list));
  ASSERT_EQ(ERROR_MALFORMED, m_p_test_component->parse(
                                 "test this is my string! \'", argument_list));
}

static int argc = 5;
static const char* argv[] = { "test", "arg1", "arg2", "arg3", "arg4" };

TEST_F(Command_parse_test, arc_argv_arguments)
{
  std::vector<std::string> argument_list;
  ASSERT_EQ(ERROR_NONE, m_p_test_component->parse(argc, argv, argument_list));
  for (size_t i = 0; i < argc; i++)
  {
    ASSERT_EQ(argv[i], argument_list[i]);
  }
}
