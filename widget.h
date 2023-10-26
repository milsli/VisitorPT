#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>

class CreateWidgetVisitor;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    void setView();

private slots:
    void onStartBrain();
    void onStartGui();

private:
    CreateWidgetVisitor* visitor_;
    QPushButton *startBrainButton_;
    QPushButton *startGuiButton_;
};
#endif // WIDGET_H
