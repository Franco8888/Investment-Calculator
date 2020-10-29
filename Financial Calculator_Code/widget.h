#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <investmentcalculator.h>
#include <QThread>  //need to include
#include <QString>
#include <QDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    //you want to have a SLOT that handels the responses from
    //the interest being calculated
    void handleInterestFound(double interest);  //it will display results
    //in the widget

private:
    Ui::Widget *ui;
    int yearCounter;

};

#endif // WIDGET_H
