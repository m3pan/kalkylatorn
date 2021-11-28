  #include "variable.h"
#include <iostream>
#include <string>

/**
 * Jag jobbar utan labbpartner, vi delade på oss i oktober så jag jobbar ensam!
 */

void Variable::set_value(double double_value)
{
  *variable_value = double_value;
}

float Variable::calculate() const
{
  return *variable_value;
}

std::string Variable::get_infix_op() const
{
  std::string char_string(1,character);
  return char_string;
}

std::string Variable::get_postfix_op() const
{
  std::string char_string(1,character);
  return char_string;
}

// bool Variable::fold()
// {
//   return false;
// }
