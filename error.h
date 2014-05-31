#ifndef ERROR_H
#define ERROR_H

namespace cli
{

enum error_result
{
  ERROR_NONE = 0,
  ERROR_NOT_INITIALIZED = -1,
  ERROR_NOT_FOUND = -2,
  ERROR_MALFORMED = -3
};

}

#endif // #define ERROR_H
