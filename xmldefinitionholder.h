#ifndef XMLDEFINITIONHOLDER_H
#define XMLDEFINITIONHOLDER_H

#include <QDomDocument>

class Visitor;

class XMLDefinitionHolder
{
public:
    XMLDefinitionHolder();

    void accept(Visitor *visitor);

    QDomDocument* getXml();

private:
    void readXmlDocument();

private:
    QDomDocument* xmlDoc_;
};

#endif // XMLDEFINITIONHOLDER_H
