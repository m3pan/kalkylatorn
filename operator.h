#ifndef OPERATOR_H
#define OPERATOR_H
#include "node.h"

/**
 * Jag jobbar utan labbpartner, vi delade på oss i oktober så jag jobbar ensam!
 */

class Operator : public Node
{
public:
  Operator(Node* left_l, Node* right_l) : left_leg{left_l}, right_leg{right_l}{};
  ~Operator()
  {
    if (left_leg != nullptr && right_leg != nullptr)
    {
      delete left_leg;
      delete right_leg;
    }
  }

  bool fold() override;



protected:
  Node* left_leg;
  Node* right_leg;

  virtual std::string get_token() const = 0;

};


class Addition : public Operator
{
public:
  Addition(Node* left_l, Node* right_l): Operator(left_l, right_l){};

  std::string get_infix_op() const override;
  std::string get_postfix_op() const override;

protected:
  float calculate() const override;
  virtual std::string get_token() const override;


};


class Subtraction : public Operator
{
public:
  Subtraction(Node* left_l, Node* right_l) : Operator(left_l, right_l){};

  std::string get_infix_op() const override;
  std::string get_postfix_op() const override;

protected:
  float calculate() const override;
  virtual std::string get_token() const override;
};


//Vår multiplikationsklass
class Multiplication : public Operator
{
public:
  Multiplication(Node* left_l, Node* right_l) : Operator(left_l, right_l){};

  std::string get_infix_op() const override;
  std::string get_postfix_op() const override;

protected:
  float calculate() const override;
  virtual std::string get_token() const override;
};


//Vår divisionsklass
class Division : public Operator
{
public:
  Division(Node* left_l, Node* right_l) : Operator(left_l, right_l){};

  std::string get_infix_op() const override;
  std::string get_postfix_op() const override;


protected:
  float calculate() const override;
  virtual std::string get_token() const override;
};


//Vår exponentklass
class Exponent : public Operator
{
public:
  Exponent(Node* left_l, Node* right_l) : Operator(left_l, right_l){};

  std::string get_infix_op() const override;
  std::string get_postfix_op() const override;

protected:
  float calculate() const override;
  virtual std::string get_token() const override;

};

#endif
