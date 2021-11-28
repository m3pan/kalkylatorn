#include "Calculator.h"
#include "expression.h"
#include "operand.h"
#include "operator.h"
#include "assignment.h"
#include "variable.h"

#include <string>
#include <sstream>
#include <stack>
#include <typeinfo>

#include <iostream>

/**
 * Jag jobbar utan labbpartner, vi delade på oss i oktober så jag jobbar ensam!
 */

Node* Expression::build_tree(std::string input_expression, double* & variable_value)
/*Expression::build_tree bygger ett binärt träd genom att utnyttja en stack där
Node-pekare lagras. När funktionen är klar så är trädet byggt och endast pekaren
till trädets rot ligger på stacken. Pekaren till roten returneras sedan.*/
{
  std::vector <std::string> input_vector = vectorize(input_expression);
  std::stack <Node*> mystack;
  for (int i = 0; i < input_vector.size(); i++)
  /*Vi itererar genom varje token från inströmmen*/
  {
    char character = (char) input_vector[i][0];

    if (isdigit(character) || isalpha(character))
    /*Om token är en operand skapas en Operand-instans och pekaren till den
    läggs på stacken*/
    {
      if(isdigit(character))
      {
        float our_number{};
        std::stringstream intValue(input_vector[i]);
        intValue >> our_number;

        Operand* op1 = new Operand{our_number};
        mystack.push(op1);
      }
      else
      /*Om token är en bokstav så är det en variabel och isåfall skapas
      en variabel-instans som sedan läggs på stacken.*/
      {
        Variable* n7 = new Variable{111, variable_value, character};
        mystack.push(n7);
      }
    }
    else
    /*Om token är en operator skapas två Node-pekare till operatorns två
    ben. Beroende på vilken operator vi har så skapas en instans med de två
    benen. Pekaren till den nya instansen läggs sedan på stacken.
    */
    {
      Node* r_leg{mystack.top()};
      mystack.pop();
      Node* l_leg{mystack.top()};
      mystack.pop();

      switch (character)
      {
        Operator* n1;

        case '+':
        n1 = new Addition{l_leg, r_leg};
        mystack.push(n1);
        break;

        case '-':
        n1 = new Subtraction{l_leg, r_leg};
        mystack.push(n1);
        break;

        case '*':
        n1 = new Multiplication{l_leg, r_leg};
        mystack.push(n1);
        break;

        case '/':
        n1 = new Division{l_leg, r_leg};
        mystack.push(n1);
        break;

        case '^':
        n1 = new Exponent{l_leg, r_leg};
        mystack.push(n1);
        break;

        case '=':
        n1 = new Assignment{l_leg, r_leg};
        mystack.push(n1);
        break;

        default:
        std::cout << "Ogiltigt tecken!" << std::endl;
        break;
      }
    }
  }
  Node* our_root = mystack.top();
  return our_root;
}


std::vector <std::string> Expression::vectorize(std::string input_string) const
{
  std::string words;
  std::vector <std::string> input_vector;

  std::istringstream iss_string(input_string);
  while (iss_string >> words)
  {
    input_vector.push_back(words);
  }
  return input_vector;
}


float Expression::evaluate() const
{
  return root->calculate();
}

std::string Expression::get_postfix() const
{
  return root->get_postfix_op();
}

std::string Expression::get_infix() const
{
  return root->get_infix_op();

}

bool Expression::empty() const
{
  if (root == nullptr)
      return true;
  else
      return false;
}

void Expression::swap(Expression & expr_swap)
{
  Expression temporary_expression = *this;
  root = expr_swap.root;
  expr_swap.root = temporary_expression.root;
}

//Kopieringskonstruktorn
  Expression::Expression(Expression & rhs)
  {
    root = rhs.root;
    delete rhs.root;
    rhs.root = nullptr;
  }

//Kopieringstilldelningsoperatorn
Expression & Expression::operator=(Expression & rhs)
  {
    root = rhs.root;
    delete rhs.root;
    rhs.root = nullptr;
    return *this;
  }


//Flyttkonstruktorn
Expression::Expression(Expression&& rhs)
{
  root = rhs.root;
  rhs.root = nullptr;
}


//Flytttilldelningsoperatorn
Expression & Expression::operator=(Expression && rhs)
{
  root = rhs.root;
  rhs.root = nullptr;
  return *this;
}



void Expression::fold()
{
  if(root->fold())
  /*Om fold returnerar true betyder det att rootbenet vill
  "folda" och vi ska nu ta fram den nya noden och sätta som root, samt
  ta bort det gamla rootbenet. */
  {
    float result = root->calculate();
    Operand* new_leg = new Operand{result};
    delete root;
    root = new_leg;
  }
}
