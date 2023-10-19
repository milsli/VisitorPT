#ifndef VISITOR_H
#define VISITOR_H

class XMLDefinitionHolder;

class Visitor
{
public:
    Visitor()
    {}

    virtual void visit(XMLDefinitionHolder *holder) = 0;
};

#endif // VISITOR_H
