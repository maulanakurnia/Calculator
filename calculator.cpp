#include "calculator.h"
#include "ui_calculator.h"

double defaultNum = 0.0;
double firstNum;
bool userIsTypingSecondNumber = false;

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
    // Connect Unary Operation
    connect(ui->BtnPlusMinus, SIGNAL(released()), this,SLOT(unaryOperationPressed()));
    connect(ui->BtnPercent, SIGNAL(released()), this,SLOT(unaryOperationPressed()));

    // Connect Binary Operation
    connect(ui->BtnDivide, SIGNAL(released()), this,SLOT(binaryOperationPressed()));
    connect(ui->BtnMultiply, SIGNAL(released()), this,SLOT(binaryOperationPressed()));
    connect(ui->BtnSubstract, SIGNAL(released()), this,SLOT(binaryOperationPressed()));
    connect(ui->BtnAdd, SIGNAL(released()), this,SLOT(binaryOperationPressed()));

    connect(ui->BtnBackspace, SIGNAL(released()), this,SLOT(Backspace()));
    ui->BtnBackspace->setText(QString::fromUtf8("\u232B"));
    ui->BtnDivide->setCheckable(true);
    ui->BtnMultiply->setCheckable(true);
    ui->BtnSubstract->setCheckable(true);
    ui->BtnAdd->setCheckable(true);
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::DigitPressed(){
    QPushButton * button = (QPushButton*)sender();

    double dispVal;
    QString newDispVal;

    if((ui->BtnAdd->isChecked() || ui->BtnSubstract->isChecked() || ui->BtnMultiply->isChecked() || ui->BtnDivide->isChecked()) && (!userIsTypingSecondNumber))
    {
        dispVal = button->text().toDouble();
        userIsTypingSecondNumber = true;
            newDispVal = QString::number(dispVal,'g',9999);
    } else{
        if(ui->Display->text().contains('.') && button->text() == "0"){
            newDispVal = ui->Display->text() + button->text();
        } else {
            dispVal = (ui->Display->text() + button->text()).toDouble();
            newDispVal = QString::number(dispVal, 'g',9999);
        }
    }

    ui->Display->setText(newDispVal);

}

void Calculator::on_BtnDecimal_released()
{
    ui->Display->setText(ui->Display->text() + ".");
}

void Calculator::unaryOperationPressed(){
    QPushButton * button = (QPushButton*) sender();
    double dispVal;
    QString newDispVal;

    if(button->text() == "+/-"){
        dispVal = ui->Display->text().toDouble();
        dispVal *= -1;
        newDispVal = QString::number(dispVal,'g',15);
        ui->Display->setText(newDispVal);
    }
    if(button->text() == "%"){
        dispVal = ui->Display->text().toDouble();
        dispVal *= 0.01;
        newDispVal = QString::number(dispVal,'g',15);
        ui->Display->setText(newDispVal);
    }
}

void Calculator::binaryOperationPressed(){
    QPushButton * button = (QPushButton*) sender();

    firstNum = ui->Display->text().toDouble();
    button->setChecked(true);

}

void Calculator::on_BtnEquals_released()
{
    double secondNum, labelNumber;
    QString newLabel;
    secondNum = ui->Display->text().toDouble();

    if(ui->BtnAdd->isChecked()){
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber,'g',9999);
        ui->Display->setText(newLabel);
        ui->BtnAdd->setChecked(false);
    } else if(ui->BtnSubstract->isChecked()){
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber,'g',9999);
        ui->Display->setText(newLabel);
        ui->BtnSubstract->setChecked(false);
    } else if(ui->BtnMultiply->isChecked()){
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber,'g',9999);
        ui->Display->setText(newLabel);
        ui->BtnMultiply->setChecked(false);
    } else if(ui->BtnDivide->isChecked()){
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber,'g',9999);
        ui->Display->setText(newLabel);
        ui->BtnDivide->setChecked(false);
    }
    userIsTypingSecondNumber = false;
}

void Calculator::on_BtnClear_released()
{
    ui->BtnAdd->setChecked(false);
    ui->BtnSubstract->setChecked(false);
    ui->BtnMultiply->setChecked(false);
    ui->BtnDivide->setChecked(false);

    userIsTypingSecondNumber = false;
    ui->Display->setText("0");
}

void Calculator::Backspace() {
    int length = ui->Display->text().length();
    if (length) {
        char last_char = ui->Display->text().at(length - 1).toLatin1();
        if (!std::isdigit(last_char))
            userIsTypingSecondNumber = true;
        ui->Display->setText(ui->Display->text().left(length - 1));
    }
}

void Calculator::on_BtnParentheses_released()
{
    ui->Display->setText("(");
    ui->Display->setFocus(Qt::OtherFocusReason);
    ui->Display->setText(")");
}
