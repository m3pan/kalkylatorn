#include "assignment.h"
#include "variable.h"

#include <iostream>
#include <string>

/**
 * Jag jobbar utan labbpartner, vi delade på oss i oktober så jag jobbar ensam!
 */

std::string Assignment::get_token() const
{
  return " = ";
}

std::string Assignment::get_infix_op() const
{
  std::string left_string = left_leg->get_infix_op();
  std::string right_string = right_leg->get_infix_op();

  if (right_string[0] == '(' || right_string[0] ==  ')' )
  {
    right_string.erase(0,1);
    right_string.pop_back();
  }

  return left_string + " = " + right_string;
}

float Assignment::calculate() const
{
  double result = right_leg->calculate();
  Variable* our_variable = dynamic_cast<Variable*>(left_leg);
  if (our_variable != nullptr)
  {
    our_variable->set_value(result);
  }

  return (float) result;
}

std::string Assignment::get_postfix_op() const
{
  std::string left_string = left_leg->get_postfix_op();

  std::string right_string = right_leg->get_postfix_op();

  if (right_string[0] == '(' || right_string[0] == ')' )
  {
    right_string.erase(0,1);
    right_string.pop_back();
  }
  
  return left_string + " " + right_string + " =" ;
}
