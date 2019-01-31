#ifndef CUSTOMLCD_H
#define CUSTOMLCD_H

#include <QLCDNumber>
#include <QDoubleSpinBox>
#include <iostream>

class CustomLCD: public QLCDNumber
{
Q_OBJECT
public:
    CustomLCD(QWidget *parent);
public slots:
    void actualizaPrimerValor(double valor);
    void actualizaSegundoValor(double valor);
    void suma();
    void resta();
    void multiplica();
    void divide();
    void changeAccumulate();
    void changeAbs();
signals:
    void changeFirstValue(double);

private:
    double valor1;
    double valor2;
    bool hasToAbs;
    bool hasToAcumulate;

};

#endif // CUSTOMLCD_H
