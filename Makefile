CCC = g++
CFLAGS = -std=c++17

kalkaylator: expression.cpp node.cpp operator.cpp operand.cpp Calculator.cc MyCalculator.cc assignment.cpp variable.cpp infix_to_postfix.cc
	$(CCC) $(CFLAGS) expression.cpp node.cpp operator.cpp operand.cpp Calculator.cc MyCalculator.cc assignment.cpp variable.cpp infix_to_postfix.cc

main: main.cpp
	$(CCC) $(CFLAGS) main.cpp

clean:
	\rm *.o kalkylator.out