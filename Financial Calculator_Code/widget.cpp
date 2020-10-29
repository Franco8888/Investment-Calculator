#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    yearCounter = 1;
    int years = ui->lineEditYears->text().toInt();
    double amount = ui->lineEditAmount->text().toDouble();
    double rate = ui->lineEditInterest->text().toDouble();

    //initialize worker class
    InvestmentCalculator *worker = new InvestmentCalculator(amount, rate, years);

    QThread *thread = new QThread();    //make QThread object

    worker->moveToThread(thread); //so you say that the worker 'worker'
    //should work in the thread 'thread', i.e. connect them together

    connect(thread, SIGNAL(started()), worker, SLOT(calculateGrowth()));
    //so when u start thread it will emit started() then it will invoke the SLOT
    //calculateGrowth()

    connect(worker, SIGNAL(interestFound(double)), this, SLOT(handleInterestFound(double)));
    //connect interestFound slot which calculates interest to handleInterest() which displays the result

    thread->start();    //when you do this you make the worker do waht it does
    //inside the specified thread. So in our case it will calculate interest
    //in the specified thread.
    //this emmites a signal called started

    //cleanup:
    //----------------------------------------
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    //when worker is finsihed you want to quit the thread
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    //need to delete worker after you have quit your thread
    //deleteLater() ensures that your object is not deleted when it is not finished yet
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    //delete thread as well
    //---------------------------------------
}

void Widget::handleInterestFound(double interest)
{
    //convert to QString
    QString sInterest = QString::number(interest);
    QString sYearCounter = QString::number(yearCounter);
    //now display the result on the widget
    ui->lineEditResultAmount->setText(sInterest);
    ui->lineEditYearResult->setText(sYearCounter);
    yearCounter++;
}
