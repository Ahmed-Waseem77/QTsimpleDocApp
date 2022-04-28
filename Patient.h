#ifndef PATIENT_H
#define PATIENT_H
#include <QApplication>

#endif // PATIENT_H

class patient{
private:
    QString _name = " ";
    QString _password = " ";
    QString _age = " ";
    int _balance = 0;
public:
    patient(){
        _name = " ";
        _password = " ";
        _age = " ";
        int balance = 0;
    }

    patient(QString N, QString P, QString A, int B){
        _name = N;
        _password = P;
        _age = A;
        _balance = B;
    }

    QString getName(){
        return _name;
    }

    void setName(QString N){
        _name =N;
    }

    QString getPass(){
        return _password;
    }

    void setPassword(QString P){
        _password=P;
    }
    int getBlance(){
        return _balance;
    }
    void setBlance(int B){
        _balance=B;
    }

    QString getAge(){
        return _age;
    }

    void setAge(QString s){
        _age = s;
    }

    };
