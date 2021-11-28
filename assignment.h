#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "operator.h"

/**
 * Jag jobbar utan labbpartner, vi delade på oss i oktober så jag jobbar ensam!
 */

class Assignment : public Operator
{
public:
  Assignment(Node* left_l, Node* right_l) : Operator(left_l, right_l){};

  std::string get_infix_op() const override;
  std::string get_postfix_op() const override;

protected:
  float calculate() const override;
  virtual std::string get_token() const override;
};

#endif
