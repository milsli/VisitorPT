#include "genericdialog.h"
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <iostream>

GenericDialog::GenericDialog(ViewTree* tree, QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)
{
    treeRoot_ = tree;
    setView();
}

void GenericDialog::setWidgets(QBoxLayout* layout, ViewTree* node)
{    
    QVector<ViewTree *> children = node->getChildren();

    QBoxLayout* localLayout;
    QString v;

    switch(node->getType())
    {
    case QtType::VerticalLayout:
        localLayout = new QVBoxLayout;
        layout->addLayout(localLayout);
        for(auto it = children.begin(); it != children.end(); ++it)
        {
            setWidgets(localLayout, *it);
        }
        break;
    case QtType::HorizontalLyout:
        localLayout = new QHBoxLayout;
        layout->addLayout(localLayout);
        for(auto it = children.begin(); it != children.end(); ++it)
        {
            setWidgets(localLayout, *it);
        }
        break;
    case QtType::GridLayout:
        throw "Under construction";
    case QtType::Label:
        {
            QStringList value = node->getValue();
            layout->addWidget(new QLabel(value[0]));
        }
        break;
    case QtType::PushButton:
        {
            QStringList value = node->getValue();
            layout->addWidget(new QPushButton(value[0]));
        }
        break;
    case QtType::LineEdit:
        {
            QStringList value = node->getValue();
            if(!value.empty())
                v = value[0];
            layout->addWidget(new QLineEdit(v));
        }
        break;
    case QtType::ComboBox:
        {
            QComboBox *widget = new QComboBox;
            QStringList value = node->getValue();
            for(const QString& s : value)
            {
                widget->addItem(s);
            }
            layout->addWidget(widget);
            QString method = node->getMethod();
            if(!method.isEmpty())
            {
                //connect(widget, &QComboBox::currentIndexChanged, this, &GenericDialog::onCurrentIndexChanged);
                connect(widget, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
                widgetsMap_[widget] = node->getName();
            }
        }
        break;
    case QtType::CheckBox:
        {
            bool checked = false;
            if(node->getValue().size() == 0)
                throw "Błąd w definicji CheckBoxa";

            if(node->getValue().size() == 2)
                checked = node->getValue()[1] == "true" ? true : false;

            QCheckBox *widget = new QCheckBox(node->getValue()[0]);
            widget->setChecked(checked);

            layout->addWidget(widget);
        }
        break;
    case QtType::RadioButton:
        {
            bool checked = false;
            if(node->getValue().size() == 0)
                throw "Błąd w definicji CheckBoxa";

            if(node->getValue().size() == 2)
                checked = node->getValue()[1] == "true" ? true : false;

            QRadioButton *widget = new QRadioButton(node->getValue()[0]);
            widget->setChecked(checked);

            layout->addWidget(widget);
        }
        break;
    case QtType::Widget:
    case QtType::Empty:
        break;
    }
}

void GenericDialog::onCurrentIndexChanged(int index)
{
    QWidget* obj = (QWidget*)sender();
    auto it = widgetsMap_.find(obj);

    ;

    std::cout << "\nWybrono idx " << index << " z combo " << it.value().toStdString() << std::flush;
}

void GenericDialog::setView()
{
    QBoxLayout *mainLayout;
    switch(treeRoot_->getType())
    {
    case QtType::VerticalLayout:
        mainLayout = new QVBoxLayout;
        break;
    case QtType::HorizontalLyout:
        mainLayout = new QHBoxLayout;
        break;
    case QtType::GridLayout:
        throw "Under construction";

    case QtType::Label:
    case QtType::PushButton:
    case QtType::LineEdit:
    case QtType::ComboBox:
    case QtType::CheckBox:
    case QtType::RadioButton:
    case QtType::Widget:
    case QtType::Empty:
        throw "Brak głównego layouta";
    }

    QVector<ViewTree*> children = treeRoot_->getChildren();

    for(auto it = children.begin(); it != children.end(); ++it)
    {
        setWidgets(mainLayout, *it);
    }

    setLayout(mainLayout);

}
