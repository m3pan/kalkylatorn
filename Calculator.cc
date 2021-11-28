/*
 * Calculator.cc
 */
#include "Calculator.h"
#include "expression.h"
#include "infix_to_postfix.h"
#include <iostream>
#include <iomanip>


const std::string Calculator::valid_cmds("?HUBPFIX");
const std::string Calculator::arg_cmds{"BPTIARL"};

/**
 * run: Huvudfunktionen för kalkylatorn. Skriver ut hjälpinformation
 * och läser sedan sedan in ett kommando i taget och utför det.
 */
void
Calculator::
run()
{
    std::cout << "Välkommen till Kalkylatorn!\n\n";
    print_help();

    do
    {
        try
        {
            get_command();
            if (valid_command()) {
                execute_command();
            }
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << '\n';
        }
        // Oförutsedda undantag avbryter programkörningen, via main().
    } while (command_ != 'X');
}

/**
 * print_help: Skriver ut kommandorepertoaren.
 */
void
Calculator::
print_help()
{
    std::cout << R"(
H, ?  Skriv ut denna hjälpinformation
U     Mata in nytt uttryck
B     Beräkna aktuellt uttryck
P     Visa aktuellt uttryck som postfix
F     Foldar aktuellt uttryck
I     Visa aktuellt uttryck som infix
X     Avsluta kalkylatorn)";
}

/**
 * get_command: Läser ett kommando (ett tecken), gör om till versal och lagrar
 * kommandot i medlemmen command_, för vidare behandling av andra operationer.
 * Ingen kontroll görs om det skrivits mer, i så fall skräp, på kommandoraden.
 */
void
Calculator::
get_command()
{
    arg_n = 0;
    std::cout << ">> ";
    std::cin >> command_;
    command_ = toupper(command_);
}

/**
 * valid_command: Kontrollerar om kommandot som finns i medlemmen command_
 * tillhör den tillåtna kommandorepertoraren och returnerar antingen true
 * (giltigt kommando) eller false (ogiltigt kommando).
 */
bool
Calculator::
valid_command() const
{
    if (valid_cmds.find(command_) == std::string::npos)
    {
        std::cout << "Otillåtet kommando: " << command_ << std::endl;
        return false;
    }
    return true;
}

/**
 * execute_command: Utför kommandot som finns i medlemmen command_. Kommandot
 * förutsätts ha kontrollerats med valid_command() och alltså är ett giltigt
 * kommando.
 */
void
Calculator::
execute_command()
{
    if (command_ == 'H' || command_ == '?')
        print_help();
    else if (command_ == 'U')
        {
          read_expression(std::cin);
        }
    else if (command_ == 'B')
    {
      std::cout << current->evaluate() << std::endl;
    }
      //ATT GÖRA: Skriv ut det aktuella uttryckets värde
    else if (command_ == 'P')
    {
      std::cout << current->get_postfix() << std::endl;
    }
    else if (command_ == 'F')
    {
      current->fold();
    }
      //ATT GÖRA: Skriv ut det aktuella uttrycket i postfix-format
    else if (command_ == 'I')
    {
      std::cout << current->get_infix() << std::endl;
    }
      //ATT GÖRA: Skriv ut det aktuella uttrycket i infix-format
    else if (command_ == 'X')
        std::cout << "Kalkylatorn avlutas, välkommen åter!" << std::endl;
    else
        std::cout << "Detta ska inte hända!" << std::endl;
}

/**
 * read_expression: läser ett infixuttryck från inströmmen is och ger detta
 * till funktionen make_expression() som returnerar ett objekt av typen
 * Expression, vilket lagras som "aktuellt uttryck" i current_expression_.
 */
void
Calculator::
read_expression(std::istream &is)
{
    std::string infix;

    is >> std::ws;

    if (getline(is, infix))
    {
      /* ATT GÖRA: Skapa ett uttryck med hjälp av funktionen make_expression()
       * som tar en infix-sträng som parameter. Spara sedan uttrycket
       * så att detta kan arbetas på.
       */
       std::string postfix = make_postfix(infix);
       if (current != nullptr)
       {
         delete current;
       }

       current = new Expression{postfix, &variable_value};
       //float *variable_value = nullptr;
    } else
    {
        std::cout << "Felaktig inmatning!" << std::endl;
    }
}
