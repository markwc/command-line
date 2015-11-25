#include "error.h"
#include "Command_function.h"
#include "Command_parse.h"

#include <cstdlib>
#include <iostream>

//====================================================================

static bool do_a_stuff = false;
static bool do_b_stuff = false;
static int b_value = 0;

cli::error_result
    configure_function(const std::vector<std::string>& argument_list)
{
  for (std::vector<std::string>::const_iterator it = argument_list.begin();
       it != argument_list.end(); ++it)
  {
    if ('-' == it->c_str()[0])
    {
      for (size_t j = 1; j < it->size(); j++)
      {
        char option = it->c_str()[j];
        switch (option)
        {
        case 'a':
          do_a_stuff = true;
          break;
        case 'b':
          if ((it + 1) != argument_list.end())
          {
            do_b_stuff = true;
            b_value = strtol((++it)->c_str(), 0, 10);
          }
          break;
        case 'h':
          std::cerr << "usage: argument_list[0] -ab n" << std::endl;
          std::cerr << "       -a do a stuff" << std::endl;
          std::cerr << "       -b do b stuff n times"
                    << std::endl;
          break;
        default:
          std::cerr << argument_list[0] << ": unknown option \'" << option
                    << "\'" << std::endl;
          break;
        }
      }
    }
  }
  return cli::ERROR_NONE;
}

//====================================================================

int main(const int argc, const char** argv)
{
  cli::Command_function command;
  cli::Command_parse cli_parse;
  std::vector<std::string> argument_list;
  cli_parse.parse(argc, argv, argument_list);
  command.add(argument_list[0], configure_function);
  command.run(argument_list);
  if (true == do_a_stuff)
  {
    std::cerr << "doing a stuff" << std::endl;
  }
  if (true == do_b_stuff)
  {
    std::cerr << "doing b stuff " << b_value << " times" << std::endl;
  }
  return 0;
}
