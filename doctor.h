#ifndef DOCTOR_H
#define DOCTOR_H
#include <QApplication>
#endif // DOCTOR_H

class doctor
{
private:

    QString _name;
    int _fee;
public:

    doctor(QString N, int F)
    {
        _name = N;
        _fee = F;
    }
    doctor()
    {
      _name = "";
      _fee = 0;
    }
    QString getname()
    {
      return _name;
    }
    int getfee()
    {
        return _fee;
    }
    void setname(QString m)
    {
        _name = m;
    }
    void setfee(int f)
    {
        _fee = f;
    }

};
