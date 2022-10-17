#ifndef __L22_AST_FUNCTION_DEFINITION_NODE_H__
#define __L22_AST_FUNCTION_DEFINITION_NODE_H__

#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include <ast/block_node.h>

namespace l22
{
    /**
     * Class for describing function definitions.
     */
    class function_definition_node : public cdk::expression_node
    {
        cdk::sequence_node *_arguments;
        l22::block_node *_block;

    public:
        function_definition_node(int lineno, cdk::sequence_node *arguments, l22::block_node *block) : cdk::expression_node(lineno), _arguments(arguments), _block(block)
        {
            type(cdk::primitive_type::create(4, cdk::TYPE_VOID));
        }

        function_definition_node(int lineno, std::shared_ptr<cdk::basic_type> funType, cdk::sequence_node *arguments, l22::block_node *block) : cdk::expression_node(lineno), _arguments(arguments), _block(block)
        {
            type(funType);
        }

    public:
        cdk::sequence_node *arguments()
        {
            return _arguments;
        }

        l22::block_node *block()
        {
            return _block;
        }

    public:
        void accept(basic_ast_visitor *sp, int level)
        {
            sp->do_function_definition_node(this, level);
        }
    };

} // l22

#endif