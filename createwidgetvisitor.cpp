#include "createwidgetvisitor.h"
#include "xmldefinitionholder.h"
#include <iostream>
#include <string>

void getXmlData(const QDomElement& e, QString& name, QtType& type, QStringList& value)
{
    name = e.attribute("name", "");
    type = QtType::HorizontalLyout;
    QString tagType = e.tagName();

    if(tagType == "layout")
    {
        QString orient = e.attribute("orientation").toLower();
        if(orient == "vertical")
            type = QtType::VerticalLayout;
        else if(orient == "grid")
            type = QtType::GridLayout;
    }
    else if(tagType == "widget")
    {
        type = QtType::Widget;
    }
    else if(tagType == "label")
    {
        type = QtType::Label;
        value.append(e.attribute("value", ""));
    }
    else if(tagType == "button")
    {
        type = QtType::PushButton;
        value.append(e.attribute("value", ""));
    }
    else if(tagType == "line")
    {
        type = QtType::LineEdit;
        value.append(e.attribute("value", ""));
    }
    else if(tagType == "checkbox")
    {
        type = QtType::CheckBox;
        value.append(e.attribute("value", ""));
        value.append(e.attribute("checked", "false"));
    }
    else if(tagType == "radiobutton")
    {
        type = QtType::RadioButton;
        value.append(e.attribute("value", ""));
        value.append(e.attribute("checked", "false"));
    }
    else if(tagType == "combobox")
    {
        type = QtType::ComboBox;
        if(e.hasChildNodes())
        {
            QDomNode cbItemNode = e.firstChild();
            while(!cbItemNode.isNull())
            {
                QDomElement cbItem = cbItemNode.toElement();
                if(!cbItem.isNull())
                {
                    if(!(cbItem.tagName() == "item"))
                        throw "Nieprowadłowa struktura elementu ComboBox";

                    value.append(cbItem.text());
                }
                cbItemNode = cbItemNode.nextSibling();
            }
        }
    }
}

static uint16_t counter;
std::string tabs = "";

QString tag2String(const QtType type)
{
    switch(type)
    {
    case QtType::CheckBox:
        return "checkbox";
    case QtType::VerticalLayout:
        return "layout vertical";
    case QtType::HorizontalLyout:
        return "layout horizontal";
    case QtType::GridLayout:
        return "layout grid";
    case QtType::Label:
        return "label";
    case QtType::PushButton:
        return "pushbutton";
    case QtType::LineEdit:
        return "line";
    case QtType::ComboBox:
        return "combobox";
    case QtType::RadioButton:
        return "radiobutton";
    case QtType::Widget:
        return "widget";
    case QtType::Empty:
        return "";
    }
    return "";
}

void treeBuilder(QDomNode xmlNode, QDomNode parentNode, ViewTree *tree)
{
    ++counter;
    QDomElement element;
    QtType type;
    QString name;
    QString tag = "";
    QStringList value;
    QString values = "";

    if(!xmlNode.isNull() && xmlNode.toElement().isElement())
    {
        element = xmlNode.toElement();
        getXmlData(element, name, type, value);
        tag = tag2String(type);
        for(const QString& s : value)
            values += s + " ";
    }

    if(xmlNode.hasChildNodes() && !element.isNull())
    {
        std::cout << "\n" << counter << tabs << tag.toStdString() << " \t" << name.toStdString() << " " << values.toStdString();

        tree->setData(name, type, value);

        if(type == QtType::ComboBox)
            treeBuilder(xmlNode.nextSibling(), parentNode, tree->addSibling());
        else
        {
            tabs += "\t";
            treeBuilder(xmlNode.firstChild(), xmlNode, tree->addChild());
        }
    }
    else if(!xmlNode.isNull())
    {
        if(!element.isNull())
        {
            QString values = "";
            for(const QString& s : value)
                values += s + " ";
            std::cout << "\n" << counter << tabs << tag.toStdString() << "  \t" << name.toStdString() << values.toStdString();

            tree->setData(name, type, value);

            treeBuilder(xmlNode.nextSibling(), parentNode, tree->addSibling());
        }
    }
    else if(xmlNode.isNull() && !parentNode.isNull())
    {
        std::cout << "\n" << counter << "wychodzenie piętro wyżej  ";

        if(tabs.size() > 1)
            tabs.pop_back();

        if(!parentNode.nextSibling().isNull())
        {
            tree->removeLastParentChild();
            treeBuilder(parentNode.nextSibling(), parentNode.parentNode(), tree->addParentSibling());
        }
        else                                   // ostatni element
        {
            tree->removeLastParentChild();
            std::cout << "  ACK ";
        }

        std::cout << std::flush;
    }
}

CreateWidgetVisitor::CreateWidgetVisitor()
{

}

void CreateWidgetVisitor::visit(XMLDefinitionHolder *holder)
{
    QDomDocument* xmlDocument = holder->getXml();
    QDomElement docElem = xmlDocument->documentElement();
    if (!docElem.isNull())
    {
        ViewTree *tree = new ViewTree;
        treeBuilder(docElem, docElem, tree);

        tree_ = tree;
    }
}

ViewTree *CreateWidgetVisitor::getTree()
{
    return tree_;
}
