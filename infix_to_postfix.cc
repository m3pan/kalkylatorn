#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <stack>
#include <sstream>
#include "infix_to_postfix.h"


/*
 * Given kod för att konvertera från infix-sträng till
 * en postfix-sträng. 
 */ 


bool is_operator(const std::string &token)
{
    const std::vector<std::string> operators{"^", "*", "/", "+", "-", "="};
    return std::find(std::begin(operators), std::end(operators), token) != std::end(operators);
}

// format_infix tar en sträng med ett infixuttryck och formaterar med ett
// mellanrum mellan varje symbol; underlättar vid bearbetningen i make_postfix.
std::string format_infix(const std::string &infix)
{
    auto   bos = begin(infix);
    auto   eos = end(infix);
    std::string formatted;

    for (auto it = bos; it != eos; ++it)
    {
	std::string temp{*it}; 
	if (is_operator(temp) || *it == '(' || *it == ')')
	{
	    // Se till att det är ett mellanrum före en operator eller parentes
	    if (it != bos && *(it - 1) != ' ' && *(formatted.end() - 1) != ' ')
		formatted.append(1, ' ');
	    formatted.append(1, *it);
	    // Se till att det är ett mellanrum efter en operator eller parentes
	    if ((it + 1) != eos && *(it + 1) != ' ')
		formatted.append(1, ' ');
	}
	else
	{
	    if (*it != ' ')
		formatted.append(1, *it);
	    else if (it != bos && *(it - 1) != ' ')
		formatted.append(1, *it);
	}
    }
    return formatted;
}



std::string make_postfix(const std::string &infix)
{
  using std::stack;
  using std::string;
  using std::istringstream;
  using std::find;

  using priority_table = std::map<std::string, int>;

  const priority_table input_priority{{"^", 8},
    {"*", 5},
    {"/", 5},
    {"+", 3},
    {"-", 3},
    {"=", 2}};
  const priority_table stack_priority{{"^", 7},
    {"*", 6},
    {"/", 6},
    {"+", 4},
    {"-", 4},
    {"=", 1}};

  stack<std::string> operator_stack;
  string        token;
  string        previous_token;
  bool          last_was_operand{false};
  bool          assignment{false};
  int           paren_count{0};

  istringstream is{format_infix(infix)};
  string        postfix;

  while (is >> token)
  {
    if (is_operator(token))
    {
      if (!last_was_operand || postfix.empty() || previous_token == "(")
      {
	throw Expression_Error{"operator där operand förväntades"};
      }

      if (token == "=")
      {
	if (assignment)
	{
	  throw Expression_Error{"multipel tilldelning"};
	}
	else
	{
	  assignment = true;
	}
      }

      while (!operator_stack.empty() && operator_stack.top() != "(" &&
	     input_priority.find(token)->second <=
	     stack_priority.find(operator_stack.top())->second)
      {
	postfix += operator_stack.top() + ' ';
	operator_stack.pop();
      }
      operator_stack.push(token);
      last_was_operand = false;
    }
    else if (token == "(")
    {
      operator_stack.push(token);
      ++paren_count;
    }
    else if (token == ")")
    {
      if (paren_count == 0)
      {
	throw Expression_Error{"vänsterparentes saknas"};
      }

      if (previous_token == "(" && !postfix.empty())
      {
	throw Expression_Error{"tom parentes"};
      }

      while (!operator_stack.empty() && operator_stack.top() != "(")
      {
	postfix += operator_stack.top() + ' ';
	operator_stack.pop();
      }

      if (operator_stack.empty())
      {
	throw Expression_Error{"högerparentes saknar matchande vänsterparentes"};
      }
      // Det finns en vänsterparentes på stacken
      operator_stack.pop();
      --paren_count;
    }
    else
    {
      if (last_was_operand || previous_token == ")")
      {
	throw Expression_Error{"operand där operator förväntades"};
      }

      postfix += token + ' ';
      last_was_operand = true;
    }
    /*else
    {
      throw Expression_Error{"otillåten symbol"};
      }*/

    previous_token = token;
  }

  if (postfix == "")
  {
    throw Expression_Error{"tomt infixuttryck!"};
  }

  if (!last_was_operand && !postfix.empty())
  {
    throw Expression_Error{"operator avslutar"};
  }

  if (paren_count > 0)
  {
    throw Expression_Error{"högerparentes saknas"};
  }

  while (!operator_stack.empty())
  {
    postfix += operator_stack.top() + ' ';
    operator_stack.pop();
  }

  if (!postfix.empty())
  {
    postfix.erase(postfix.size() - 1);
  }

  return postfix;
}
