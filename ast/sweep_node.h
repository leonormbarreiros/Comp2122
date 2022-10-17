#ifndef __L22_AST_SWEEP_NODE_H__
#define __L22_AST_SWEEP_NODE_H__

#include <cdk/ast/expression_node.h>

namespace l22
{

  /**
   * Class for describing with-change-cycle nodes.
   */
  class sweep_node : public cdk::basic_node
  {
    cdk::expression_node * _vector;
    cdk::expression_node * _low;
    cdk::expression_node * _high;
    cdk::expression_node * _function;
    cdk::expression_node * _condition;

  public:
    inline sweep_node(int lineno, cdk::expression_node * vector, cdk::expression_node * low, cdk::expression_node * high, cdk::expression_node * function, cdk::expression_node * condition) : basic_node(lineno), _vector(vector), _low(low), _high(high), _function(function), _condition(condition)
    {
    }

  public:
    inline cdk::expression_node * function() {
        return _function;
    }
    inline cdk::expression_node * vector() {
        return _vector;
    }
    inline cdk::expression_node * low() {
        return _low;
    }
    inline cdk::expression_node * high() {
        return _high;
    }
    inline cdk::expression_node * condition() {
        return _condition;
    }

    void accept(basic_ast_visitor *sp, int level)
    {
      sp->do_sweep_node(this, level);
    }
  };

} // l22

#endif