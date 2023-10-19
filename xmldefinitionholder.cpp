#include "xmldefinitionholder.h"
#include "createwidgetvisitor.h"

#include <QFile>

XMLDefinitionHolder::XMLDefinitionHolder()
{
    readXmlDocument();
}

void XMLDefinitionHolder::accept(Visitor *visitor)
{
    CreateWidgetVisitor *cwVisitor = static_cast<CreateWidgetVisitor*>(visitor);
    cwVisitor->visit(this);
}

QDomDocument *XMLDefinitionHolder::getXml()
{
    return xmlDoc_;
}

void XMLDefinitionHolder::readXmlDocument()
{
    xmlDoc_ = new QDomDocument("widget");
    QFile file("../widgets.xml");
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!xmlDoc_->setContent(&file)) {
        file.close();
        return;
    }
    file.close();
}
