#include "investmentcalculator.h"

InvestmentCalculator::InvestmentCalculator(double a, double ir, int y)
{
    amount = a;
    years = y;
    interestRate = ir;
}

void InvestmentCalculator::calculateGrowth()
{
    //emit needs to be in a loop so we can calculate it c number of times
    int y = 1;
    double interest;
    while(y<=years)
    {
        QThread::sleep(2);

        interest = amount * pow((1+interestRate*0.01),y);

        //console output=======
        qDebug() << "year:" << y;
        qDebug() << "interest:" << interest;
        qDebug() << "===========";
        //=====================

        emit interestFound(interest);
        y++;
    }
    emit finished();    //this is to say it has reached the end of execution
}


