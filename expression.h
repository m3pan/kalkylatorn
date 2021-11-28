#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "node.h"
#include "operator.h"

#include <vector>
#include <string>
#include <iostream>

/**
 * Jag jobbar utan labbpartner, vi delade på oss i oktober så jag jobbar ensam!

 fixa makefil
 */

class Expression
{
public:
  Expression(std::string input_expression, double* variable_value)
  {
    root = build_tree(input_expression, variable_value);
  };
  ~Expression()
  {
    delete root;
  };

  //Kopieringskonstruktorn
  Expression(Expression &);

  //Kopieringstilldelningsoperatorn
   Expression& operator = (Expression &);

   //Flyttkonstruktorn
   Expression(Expression&&);


   //Flytttilldelningsoperatorn
   Expression& operator=(Expression &&);

   void update_variables(Expression&);


  float evaluate() const;
  std::string get_postfix() const;
  std::string get_infix() const;
  bool empty() const;
  void swap(Expression&);

  void fold();


private:
  Node* build_tree(std::string, double* &);
  Node* root;
  std::vector <std::string> vectorize(std::string) const;

};
#endif
