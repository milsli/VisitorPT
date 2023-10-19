#ifndef GENERICDIALOG_H
#define GENERICDIALOG_H

#include "viewtree.h"
#include <QMap>
#include <QDialog>

class QBoxLayout;

class GenericDialog : public QDialog
{
    Q_OBJECT
public:
    explicit  GenericDialog(ViewTree* tree, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void setView();
    void setWidgets(QBoxLayout* layout, ViewTree* node);

private:
    ViewTree* treeRoot_;
    QMap<QWidget*, QString> widgetsMap_;

public slots:
    void onCurrentIndexChanged(int index);
};

#endif // GENERICDIALOG_H
