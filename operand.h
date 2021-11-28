#ifndef OPERAND_H
#define OPERAND_H
#include "node.h"

/**
 * Jag jobbar utan labbpartner, vi delade på oss i oktober så jag jobbar ensam!
 */

class Operand : public Node
{
public:
  Operand(float val) : value{val}{};

protected:

  virtual std::string get_infix_op() const override;
  virtual std::string get_postfix_op() const override;
  virtual float calculate() const override;
  bool fold() override;
  Operand & operator=(Operand && rhs);

private:

  float value;
};
#endif
