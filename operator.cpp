#include "operator.h"
#include "operand.h"
#include "variable.h"

#include <iomanip>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>

/**
 * Jag jobbar utan labbpartner, vi delade på oss i oktober så jag jobbar ensam!
 */

float Addition::calculate() const
{
  return left_leg->calculate() + right_leg->calculate();
}


float Subtraction::calculate() const
{
  return left_leg->calculate() - right_leg->calculate();
}


float Multiplication::calculate() const
{
  return left_leg->calculate() * right_leg->calculate();
}

float Division::calculate() const
{
  return left_leg->calculate() / right_leg->calculate();
}

float Exponent::calculate() const
{
  return pow(left_leg->calculate(), right_leg->calculate());
}

std::string Addition::get_token() const
{
  return " + ";
}

std::string Subtraction::get_token() const
{
  return " - ";
}

std::string Multiplication::get_token() const
{
  return " * ";
}

std::string Division::get_token() const
{
  return " / ";
}

std::string Exponent::get_token() const
{
  return " ^ ";
}


std::string Addition::get_infix_op() const
{
  return "(" + left_leg->get_infix_op() + " + " + right_leg->get_infix_op() + ")";
}

std::string Subtraction::get_infix_op() const
{
  return "(" + left_leg->get_infix_op() + " - " + right_leg->get_infix_op() + ")";
}

std::string Multiplication::get_infix_op() const
{
  return "(" + left_leg->get_infix_op() + " * " + right_leg->get_infix_op() + ")";
}

std::string Division::get_infix_op() const
{
  return left_leg->get_infix_op() + " / " + right_leg->get_infix_op();
}

std::string Exponent::get_infix_op() const
{
  return left_leg->get_infix_op() + " ^ " + right_leg->get_infix_op();
}

std::string Addition::get_postfix_op() const
{
  return left_leg->get_postfix_op() + " " + right_leg->get_postfix_op() + " +" ;
}

std::string Subtraction::get_postfix_op() const
{
  return left_leg->get_postfix_op() + " " + right_leg->get_postfix_op() + " -" ;
}

std::string Multiplication::get_postfix_op() const
{
  return left_leg->get_postfix_op() + " " + right_leg->get_postfix_op() + " *" ;
}

std::string Division::get_postfix_op() const
{
  return left_leg->get_postfix_op() + " " + right_leg->get_postfix_op() + " /" ;
}

std::string Exponent::get_postfix_op() const
{
  return left_leg->get_postfix_op() + " " + right_leg->get_postfix_op() + " ^" ;
}

bool Operator::fold()
{
  if(left_leg->fold())
  /*Om vänsterbenet i fold returnerar true betyder det att vänsterbenet vill
  "folda" och vi ska nu ta fram den nya noden och sätta som vänsterben, samt
  ta bort det gamla vänsterbenet. */
  {
    float result = left_leg->calculate();
    Operand* new_leg = new Operand{result};
    delete left_leg;
    left_leg = new_leg;
  }

  if(right_leg->fold())
  {
    float result = right_leg->calculate();
    Operand* new_leg = new Operand{result};
    delete right_leg;
    right_leg = new_leg;
  }

    Variable* left_variable = dynamic_cast<Variable*>(left_leg);
    Variable* right_variable = dynamic_cast<Variable*>(right_leg);

    Operator* left_operator = dynamic_cast<Operator*>(left_leg);
    Operator* right_operator = dynamic_cast<Operator*>(right_leg);

    if(left_variable != nullptr || right_variable != nullptr)
    {
      return false;
    }
    else if (left_operator == nullptr && right_operator == nullptr)
    /*Om båda benen är siffer-operander så vill vi förenkla det uttrycket och
    returnerar därför upp true*/
    {
      return true;
    }
}
