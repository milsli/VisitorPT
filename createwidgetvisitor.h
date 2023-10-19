#ifndef CREATEWIDGETVISITOR_H
#define CREATEWIDGETVISITOR_H

#include "visitor.h"
#include "viewtree.h"

class CreateWidgetVisitor : public Visitor
{
public:
    CreateWidgetVisitor();
    void visit(XMLDefinitionHolder *holder);

    ViewTree* getTree();

private:
    ViewTree *tree_;
};

#endif // CREATEWIDGETVISITOR_H
