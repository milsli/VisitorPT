#ifndef GENERICDIALOG_H
#define GENERICDIALOG_H

#include "viewtree.h"
#include <QObject>
#include <QDialog>

class QBoxLayout;

class GenericDialog : public QDialog
{
    Q_OBJECT
public:
    GenericDialog(ViewTree* tree, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void setView();
    void setWidgets(QBoxLayout* layout, ViewTree* node);

private:
    ViewTree* treeRoot_;

public slots:
    void onComboChoice(int index);
};

#endif // GENERICDIALOG_H
