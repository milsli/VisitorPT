#ifndef VIEWTREE_H
#define VIEWTREE_H

#include <QWidget>
#include <QVector>
#include <QDomNode>

enum class QtType
{
    VerticalLayout,
    HorizontalLyout,
    GridLayout,
    Label,
    PushButton,
    LineEdit,
    ComboBox,
    CheckBox,
    RadioButton,
    Widget,
    Empty
};

class ViewTree
{
public:
    ViewTree() = default;

    QString getName() const;
    QtType getType() const;
    QStringList getValue() const;

    QVector<ViewTree*> getChildren() const;

private:
    ViewTree(ViewTree* parent);
    ViewTree *addSibling();
    ViewTree *addChild();
    ViewTree *addParentSibling();
    void setData(const QString name, const QtType type, QStringList value);
    void removeLastParentChild();

private:
    QString name_;
    QtType type_ = QtType::Empty;
    QStringList value_;
    ViewTree *parent_ = nullptr;

    QVector<ViewTree*> child_;

    friend void treeBuilder(QDomNode xmlNode, QDomNode parentNode, ViewTree *tree);
};

#endif // VIEWTREE_H
