#ifndef NODE_H
#define NODE_H
#include <string>

/**
 * Jag jobbar utan labbpartner, vi delade på oss i oktober så jag jobbar ensam!
 */

class Node
{
public:
  virtual ~Node() = default;
  virtual std::string get_infix_op() const = 0;
  virtual std::string get_postfix_op() const = 0;
  virtual float calculate() const = 0;
  virtual bool fold() = 0;
};
#endif
