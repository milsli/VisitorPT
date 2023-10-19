#include "viewtree.h"

ViewTree::ViewTree(ViewTree *parent) :
    parent_{parent}
{
}

QString ViewTree::getName() const
{
    return name_;
}

QtType ViewTree::getType() const
{
    return type_;
}

QStringList ViewTree::getValue() const
{
    return value_;
}

QVector<ViewTree *> ViewTree::getChildren() const
{
    return child_;
}

ViewTree* ViewTree::addSibling()
{
    if(parent_== nullptr)
        throw "Brak rodzica";

    return parent_->addChild();
}

ViewTree* ViewTree::addChild()
{
    ViewTree *node  = new ViewTree(this);
    child_.append(node);
    return node;
}

ViewTree *ViewTree::addParentSibling()
{
    if(parent_== nullptr)
        throw "Brak rodzica";

    return parent_->addSibling();
}

void ViewTree::setData(const QString name, const QtType type, QStringList value)
{
    name_ = name;
    type_ = type;
    value_ = value;
}

void ViewTree::removeLastParentChild()
{
    parent_->child_.removeLast();
}
