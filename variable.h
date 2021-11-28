#ifndef VARIABLE_H
#define VARIABLE_H

#include "operand.h"
#include <iostream>

/**
 * Jag jobbar utan labbpartner, vi delade på oss i oktober så jag jobbar ensam!
 */

class Variable : public Operand
{
public:
Variable(float val, double* variable_val, char var_char) : Operand(val),
                          variable_value(variable_val), character(var_char){};
// ~Variable()
// {
//   delete variable_value;
// };

  void set_value(double);

protected:
  std::string get_infix_op() const override;
  std::string get_postfix_op() const override;
  float calculate() const override;
  // bool fold();

private:
  double* variable_value;
  char character;
};
#endif
