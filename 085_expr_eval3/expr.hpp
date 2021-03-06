#include <sstream>
#include <string>
class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression(){};
  virtual long evaluate() const = 0;
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
  virtual long evaluate() const {
    long ans = number;
    return ans;
  };
  virtual ~NumExpression(){};
};
// opExpression is an abstract class
class OpExpression : public Expression {
 protected:
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
  virtual long evaluate() const = 0;
};

class PlusExpression : public OpExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OpExpression('+', lhs, rhs){};
  virtual ~PlusExpression(){};
  virtual long evaluate() const {
    long ans = lhs->evaluate() + rhs->evaluate();
    return ans;
  }
};

class MinusExpression : public OpExpression {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : OpExpression('-', lhs, rhs){};
  virtual ~MinusExpression(){};
  virtual long evaluate() const {
    long ans = lhs->evaluate() - rhs->evaluate();
    return ans;
  }
};

class TimesExpression : public OpExpression {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : OpExpression('*', lhs, rhs){};
  virtual ~TimesExpression(){};
  virtual long evaluate() const {
    long ans = lhs->evaluate() * rhs->evaluate();
    return ans;
  }
};

class DivExpression : public OpExpression {
 public:
  DivExpression(Expression * lhs, Expression * rhs) : OpExpression('/', lhs, rhs){};
  virtual ~DivExpression(){};
  virtual long evaluate() const {
    long ans = lhs->evaluate() / rhs->evaluate();
    return ans;
  }
};
