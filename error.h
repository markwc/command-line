#ifndef ERROR_H
#define ERROR_H

namespace cli
{

enum status_code_category
{
  STATUS_CODE_ERROR = 0x100
};

enum error_result
{
  ERROR_NONE = STATUS_CODE_ERROR | 0,
  ERROR_NOT_INITIALIZED = STATUS_CODE_ERROR | 1,
  ERROR_NOT_FOUND = STATUS_CODE_ERROR | 2,
  ERROR_MALFORMED = STATUS_CODE_ERROR | 3
};

}

#endif // #define ERROR_H
