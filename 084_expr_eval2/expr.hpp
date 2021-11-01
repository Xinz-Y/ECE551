#include <sstream>
#include <string>
class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression(){};
};

class NumExpression : public Expression {
  long number;

 public:
  NumExpression(long num) : number(num){};
  virtual std::string toString() const {
    std::stringstream out;
    out << number;

    return out.str();
  }
  virtual ~NumExpression(){};
};

class OpExpression : public Expression {
  char op;
  Expression * lhs;
  Expression * rhs;

 public:
  OpExpression(char op_p, Expression * lhs_p, Expression * rhs_p) :
      op(op_p),
      lhs(lhs_p),
      rhs(rhs_p){};
  virtual std::string toString() const {
    std::stringstream out;
    out << '(' << lhs->toString() << ' ' << op << ' ' << rhs->toString() << ')';
    return out.str();
  }
  virtual ~OpExpression() {
    delete lhs;
    delete rhs;
  };
};

class PlusExpression : public OpExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OpExpression('+', lhs, rhs){};
  virtual ~PlusExpression(){};
};

class MinusExpression : public OpExpression {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : OpExpression('-', lhs, rhs){};
  virtual ~MinusExpression(){};
};

class TimesExpression : public OpExpression {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : OpExpression('-', lhs, rhs){};
  virtual ~TimesExpression(){};
};

class DivExpression : public OpExpression {
 public:
  DivExpression(Expression * lhs, Expression * rhs) : OpExpression('-', lhs, rhs){};
  virtual ~DivExpression(){};
};
