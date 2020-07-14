#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
private slots:
    void DigitPressed();
    void on_BtnDecimal_released();
    void unaryOperationPressed();
    void binaryOperationPressed();
    void on_BtnEquals_released();
    void on_BtnClear_released();
};
#endif // CALCULATOR_H
