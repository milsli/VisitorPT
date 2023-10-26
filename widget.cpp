#include "widget.h"
#include "xmldefinitionholder.h"
#include "createwidgetvisitor.h"
#include <QVBoxLayout>
#include <iostream>
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
    startBrainButton_ = new QPushButton("START BRAIN");
    startGuiButton_ = new QPushButton("START GUI");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(startBrainButton_);
    mainLayout->addWidget(startGuiButton_);

    setLayout(mainLayout);
    connect(startBrainButton_, &QPushButton::clicked, this, &Widget::onStartBrain);
    connect(startGuiButton_, &QPushButton::clicked, this, &Widget::onStartGui);
}

void Widget::onStartBrain()
{

}

void Widget::onStartGui()
{
    visitor_ = new CreateWidgetVisitor;
    XMLDefinitionHolder xmlHolder;
    xmlHolder.accept(visitor_);

    ViewTree  *t = visitor_->getTree();

    GenericDialog *dialog = new GenericDialog(t, this);
    dialog->exec();
}

