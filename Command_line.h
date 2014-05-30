#include <string>
#include <vector>

class Command_line
{
public:
  Command_line();
  ~Command_line();
  typedef int (*command_function)(const std::vector<std::string>&);
  int process_line(const std::string& line);
  int add_command(const std::string& command, const command_function function);
private:
  struct Impl;
  Impl *m_p_impl;
};
