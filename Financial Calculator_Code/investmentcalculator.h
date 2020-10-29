#ifndef INVESTMENTCALCULATOR_H
#define INVESTMENTCALCULATOR_H

#include <QtMath>
#include <QObject>
#include <QDebug>
#include <QThread>

//worker class of threading
class InvestmentCalculator: public QObject
{
    Q_OBJECT

public:
    InvestmentCalculator(double a, double ir, int y);

signals:
    void finished();    //emitted when worker is finished
    void interestFound(double);   //emitted whenever we have calculated interest
    //when we find interest send it to the SLOT
    //you need to send the slot what you have found, in our case interest

private slots:
    void calculateGrowth();  //this will calculate the interest

private:
    double amount;
    double interestRate;
    int years;

};

#endif // INVESTMENTCALCULATOR_H
