#include "widget.h"
#include "xmldefinitionholder.h"
#include "createwidgetvisitor.h"
#include <QVBoxLayout>
#include "genericdialog.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setView();
}

Widget::~Widget()
{
}

void Widget::setView()
{
    startButton_ = new QPushButton("S T A R T");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(startButton_);

    setLayout(mainLayout);
    connect(startButton_, &QPushButton::clicked, this, &Widget::onStart);
}

void Widget::onStart()
{
    visitor_ = new CreateWidgetVisitor;
    XMLDefinitionHolder xmlHolder;
    xmlHolder.accept(visitor_);

    ViewTree  *t = visitor_->getTree();

    GenericDialog *dialog = new GenericDialog(t, this);
    dialog->exec();
}

