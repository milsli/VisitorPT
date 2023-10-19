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
    void onStart();

private:
    CreateWidgetVisitor* visitor_;
    QPushButton *startButton_;
};
#endif // WIDGET_H
