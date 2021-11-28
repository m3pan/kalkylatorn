/*
 * infix_to_postfix.h
 */

#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H

#include <string>
#include <stdexcept>

class Expression_Error : public std::logic_error
{
    using std::logic_error::logic_error;
};

bool is_operator(const std::string &token);
std::string make_postfix(const std::string &infix);



#endif
