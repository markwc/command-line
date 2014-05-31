#include "error.h"
#include "Command_function.h"
#include "Command_parse.h"

#include <iostream>


//====================================================================

static bool do_a_stuff = false;

cli::error_result configure_function(
  const std::vector<std::string> &argument_list)
{
  for (size_t i = 0; i < argument_list.size(); i++)
  {
    if ('-' == argument_list[i][0])
    {
      for (size_t j = 1; j < argument_list[i].size(); j++)
      {
        switch(argument_list[i][j])
        {
        case 'a':
          do_a_stuff = true;
          break;
        default:
          std::cerr << argument_list[0] << ": unknown option \'"
                    << argument_list[i][j] << "\'" << std::endl;
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
  return 0;
}
