#include "operand.h"
#include <iomanip>
#include <sstream>
#include <iostream>

/**
 * Jag jobbar utan labbpartner, vi delade på oss i oktober så jag jobbar ensam!
 */

float Operand::calculate() const
{
  return value;
}

std::string Operand::get_infix_op() const
{
  std::ostringstream out;
  out << value;
  std::string text = out.str();
  return text;
}

std::string Operand::get_postfix_op() const
{
  std::ostringstream out;
  out << value;
  std::string text = out.str();
  return text;
}

bool Operand::fold()
{
  return false;
}
