#include "Command_function.h"

#include <iostream>

#include <gtest/gtest.h>

//====================================================================

static std::vector<std::string> last_arguments;

using namespace cli;

static error_result test_function(const std::vector<std::string>& arguments)
{
  last_arguments.clear();
  last_arguments = arguments;
  return cli::ERROR_NONE;
}

class Command_function_test : public ::testing::Test
{
public:
  // gnu_radio_test constructor.
  Command_function_test()
  {
  }
  // gnu_radio_test destructor.
  virtual ~Command_function_test()
  {
  }

protected:
  Command_function* m_p_test_component;
  // GTest setup function called for each TEST_F
  virtual void SetUp()
  {
    m_p_test_component = new Command_function();
  }
  // GTest teardown function called after each TEST_F
  virtual void TearDown()
  {
    delete m_p_test_component;
  }
};

//====================================================================

TEST_F(Command_function_test, not_initialized)
{
  ASSERT_EQ(ERROR_NOT_INITIALIZED, m_p_test_component->add("test", 0));
}

TEST_F(Command_function_test, command_found)
{
  std::vector<std::string> argument_list;
  ASSERT_EQ(ERROR_NONE, m_p_test_component->add("test", test_function));
  argument_list.push_back("test");
  ASSERT_EQ(ERROR_NONE, m_p_test_component->run(argument_list));
}

TEST_F(Command_function_test, command_not_found)
{
  std::vector<std::string> argument_list;
  ASSERT_EQ(ERROR_NONE, m_p_test_component->add("test", test_function));
  argument_list.push_back("testy");
  ASSERT_EQ(ERROR_NOT_FOUND, m_p_test_component->run(argument_list));
}
