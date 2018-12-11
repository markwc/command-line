/// @file Command_function.h

#ifndef COMMAND_FUNCTION_H
#define COMMAND_FUNCTION_H

#include "error.h"

#include <string>
#include <vector>

namespace cli
{
class Command_function
{
public:
  /// Used as a function type for run list.
  typedef error_result (*command_function_t)(const std::vector<std::string>&);

  /// Constructor.
  Command_function();

  /// Destructor.
  virtual ~Command_function();

  /// Run a function with arguments.
  /// @param[in] argument_list a vector of string arguments.
  error_result run(const std::vector<std::string>& argument_list);

  /// Add function with key value of command to run list.
  /// @param[in] command  The command name.
  /// @param[in] function Pointer of type comand_function_t.
  error_result add(const std::string& command,
                   const command_function_t function);

private:
  /// Forward declaration of the private implementation struct.
  struct Impl;
  /// Service private implementation pointer.
  Impl* m_p_impl;
  /// Private implementation of the assignment operator to restrict
  /// copying of the instance of this class to avoid double free
  /// errors.
  Command_function& operator=(const Command_function&);
  /// Private copy constructor to restrict copying of the instance
  /// of this class to avoid double free errors.
  Command_function(const Command_function&);
};
}

#endif  // #define COMMAND_FUNCTION_H
