#ifndef __L22_TARGETS_TYPE_CHECKER_H__
#define __L22_TARGETS_TYPE_CHECKER_H__

#include <sstream>
#include "targets/basic_ast_visitor.h"
#include <cdk/types/reference_type.h>
#include <cdk/types/functional_type.h>
#include <cdk/types/primitive_type.h>

namespace l22
{

  /**
   * Print nodes as XML elements to the output stream.
   */
  class type_checker : public basic_ast_visitor
  {
    cdk::symbol_table<l22::symbol> &_symtab;

    std::shared_ptr<l22::symbol> _function;
    basic_ast_visitor *_parent;
    int _lbl;
    std::shared_ptr<cdk::basic_type> _inBlockReturnType = nullptr;

  public:
    type_checker(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<l22::symbol> &symtab, std::shared_ptr<l22::symbol> function, basic_ast_visitor *parent) : basic_ast_visitor(compiler), _symtab(symtab), _function(function), _parent(parent), _lbl(0)
    {
    }

  public:
    ~type_checker()
    {
      os().flush();
    }

  protected:
    void processScalarIntOnlyExpression(cdk::binary_operation_node *const node, int lvl);
    void processLogicalIntOnlyExpression(cdk::binary_operation_node *const node, int lvl);
    void processScalarPIDExpression(cdk::binary_operation_node *const node, int lvl);
    void processScalarIDExpression(cdk::binary_operation_node *const node, int lvl);
    void processScalarLogicalExpression(cdk::binary_operation_node *const node, int lvl);
    void processGeneralLogicalExpression(cdk::binary_operation_node *const node, int lvl);
    void processUnaryExpression(cdk::unary_operation_node *const node, int lvl);

    void check_pointer_types(std::shared_ptr<cdk::reference_type> pointer1, std::shared_ptr<cdk::reference_type> pointer2);
    void check_functional_types(std::shared_ptr<cdk::functional_type> fun_type1, std::shared_ptr<cdk::functional_type> fun_type2);

    template <typename T>
    void process_literal(cdk::literal_node<T> *const node, int lvl)
    {
    }

  public:
    // do not edit these lines
#define __IN_VISITOR_HEADER__
#include ".auto/visitor_decls.h" // automatically generated
#undef __IN_VISITOR_HEADER__
    // do not edit these lines: end
  };

} // l22

//---------------------------------------------------------------------------
//     HELPER MACRO FOR TYPE CHECKING
//---------------------------------------------------------------------------

#define CHECK_TYPES(compiler, symtab, function, node)                \
  {                                                                  \
    try                                                              \
    {                                                                \
      l22::type_checker checker(compiler, symtab, function, this);   \
      (node)->accept(&checker, 0);                                   \
    }                                                                \
    catch (const std::string &problem)                               \
    {                                                                \
      std::cerr << (node)->lineno() << ": " << problem << std::endl; \
      return;                                                        \
    }                                                                \
  }

#define ASSERT_SAFE_EXPRESSIONS CHECK_TYPES(_compiler, _symtab, _function, node)

#endif
