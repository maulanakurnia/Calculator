#include "calculator.h"
#include "ui_calculator.h"

double defaultNum = 0.0;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(defaultNum));
    QPushButton *numButtons[10];
    for(int i=0; i<10; ++i){
        QString btnName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(btnName);
        connect(numButtons[i], SIGNAL(released()), this,SLOT(DigitPressed()));
    }
    connect(ui->BtnPlusMinus, SIGNAL(released()), this,SLOT(unaryOperationPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::DigitPressed(){
    QPushButton * button = (QPushButton*)sender();

    QString btnVal = button->text();
    QString displayVal = ui->Display->text();

    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui->Display->setText(btnVal);
    } else {
        QString newVal = displayVal + btnVal;
        ui->Display->setText(newVal);
    }

}

void Calculator::on_BtnDecimal_released()
{
    ui->Display->setText(ui->Display->text() + ".");
}

void Calculator::unaryOperationPressed(){
    QPushButton * button = (QPushButton*) sender();
    double dispNum;
    QString newNumDisp;

    if(button->text() == "+/-"){
        dispNum = ui->Display->text().toDouble();
        dispNum *= -1;
        newNumDisp = QString::number(dispNum,'g',15);
        ui->Display->setText(newNumDisp);
    }
}
