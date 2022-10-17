#ifndef __L22_AST_AGAIN_NODE_H__
#define __L22_AST_AGAIN_NODE_H__

#include <cdk/ast/basic_node.h>

namespace l22
{
    /**
     * Class for describing again nodes.
     */
    class again_node : public cdk::basic_node
    {

    public:
        again_node(int lineno) : cdk::basic_node(lineno)
        {
        }

    public:
        void accept(basic_ast_visitor *sp, int level)
        {
            sp->do_again_node(this, level);
        }
    };

} // l22

#endif
