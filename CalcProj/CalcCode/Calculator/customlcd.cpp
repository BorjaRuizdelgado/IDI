#include "customlcd.h"

CustomLCD::CustomLCD(QWidget *parent):QLCDNumber(parent){
    hasToAbs = false;
    hasToAcumulate = false;
    valor1 = 0.0;
    valor2 = 0.0;
}

void CustomLCD::actualizaPrimerValor(double valor){
    this->valor1 = valor;
}
void CustomLCD::actualizaSegundoValor(double valor){
    this->valor2 = valor;
}

void CustomLCD::suma(){
    double result;

    if(hasToAbs){
        result = abs(valor1 + valor2);
        this->display(QString::number(result));
    }
    else {
        result = valor1 + valor2;
        this->display(QString::number(result));
    }
    if(hasToAcumulate){
        if(result > 99 or result < 0) std::cout << "Can't accumulate the result is rather too big or too small, mind that the calculator operates in a range of 0 to 99" << std::endl;
        else changeFirstValue(result);
    }
}

void CustomLCD::resta(){
    double result;

    if(hasToAbs){
        result = abs(valor1 - valor2);
        this->display(QString::number(result));
    }
    else {
        result = valor1 - valor2;
        this->display(QString::number(result));
    }
    if(hasToAcumulate){
        if(result > 99 or result < 0) std::cout << "Can't accumulate the result is rather too big or too small, mind that the calculator operates in a range of 0 to 99" << std::endl;
        else changeFirstValue(result);
    }
}

void CustomLCD::multiplica(){
    double result;

    if(hasToAbs){
        result = abs(valor1 * valor2);
        this->display(QString::number(result));
    }
    else {
        result = valor1 * valor2;
        this->display(QString::number(result));
    }
    if(hasToAcumulate){
        if(result > 99 or result < 0) std::cout << "Can't accumulate the result is rather too big or too small, mind that the calculator operates in a range of 0 to 99" << std::endl;
        else changeFirstValue(result);
    }
}

void CustomLCD::divide(){
    double result;
    if(valor2 != 0.0){
        if(hasToAbs){
                result = abs(valor1 / valor2);
                this->display(QString::number(result));
            }
            else {
                result = valor1 / valor2;
                this->display(QString::number(result));
            }
        if(hasToAcumulate){
            if(result > 99 or result < 0) std::cout << "Can't accumulate the result is rather too big or too small, mind that the calculator operates in a range of 0 to 99" << std::endl;
            else changeFirstValue(result);
        }
    }
    else std::cout << "cant divide by 0" << std::endl;
}

void CustomLCD::changeAbs(){
    this->hasToAbs = !this->hasToAbs;
}

void CustomLCD::changeAccumulate(){
    this->hasToAcumulate = !this->hasToAcumulate;
}
