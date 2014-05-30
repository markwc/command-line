#include <string>
#include <vector>

class Command_line
{
public:
  
  typedef int (*command_function)(const std::vector<std::string>&);
  
  Command_line();
  ~Command_line();
  
  int process_command(const std::string& line);
  int process_command(const int argc, const char** argv);
  int process_command(const std::vector<std::string>& argument_list);
  int add_command(const std::string& command, const command_function function);
  
private:
  
  struct Impl;
  Impl *m_p_impl;
};
