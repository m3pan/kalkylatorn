/*
 * Calculator.h
 */
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "expression.h"
#include <iosfwd>
#include <vector>

/**
 * Calculator: klass för att läsa in, lagra och bearbeta enkla aritmetiska
 * uttryck. För att använda kalylatorn - skapa ett Calculator-objekt och
 * anropa run().
 *
 * Anm: move-konstruktorn och move-illdelningsoperatorn genereras inte om
 * en destruktor, kopieringskonstruktor eller kopieringstilldelnings-
 * operator deklareras.
 */
class Calculator
{
public:
    Calculator() = default;

    ~Calculator()
    {
      if (current != nullptr)
      {
        delete current;
      }
    };

    Calculator(const Calculator &) = delete;

    Calculator &operator=(const Calculator &) = delete;

    void run();

    double variable_value{0};

private:
    static const std::string valid_cmds;
    static const std::string arg_cmds;
    char command_;
    static void print_help();

    void get_command();

    bool valid_command() const;

    void execute_command();

    void read_expression(std::istream &);

    Expression* current{};


    int arg_n;

};

#endif
