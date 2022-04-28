#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Patient.h"
#include "doctor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QVector<doctor> getVdoctors(){
        return _doctors;
    }
    QVector<patient*> getVpatients(){
        return _patients;
    }

    void setVdoctors(QVector<doctor> d){
        _doctors = d;
    }
    void setVpatients(QVector<patient*> p){
        _patients = p;
    }

    void InitialiseDB()
    {
        auto it = _patients.begin();
        if (it != NULL)
        {
            return;
        }
        doctor DRAli("Ali", 120);
        doctor DRAhmed("Ahmed", 90);
        doctor DRBavly("Bavly", 930);
        doctor DRBarbary("Barbary", 2);
        patient* Patient1 = new patient("P1", "P1Password", "43", 100);
        patient* Patient2 = new patient("P2", "P2Password", "34", 1341);
        patient* Patient3 = new patient("P3", "P3Password", "53", 12441);
        patient* Patient4 = new patient("P4", "P4Password", "12", 12);

        _patients = {Patient1, Patient2, Patient3, Patient4};
        _doctors = {DRAli, DRAhmed, DRBavly, DRBarbary};
    }

private slots:
    void on_pushButtonRegister_clicked();

    void on_pushButtonLogin_clicked();

    void on_pushButtonRecharge_clicked();

    void on_pushButtonBooking_clicked();

    void on_comboBox_activated(int index);

private:

    QVector<patient*> _patients;

    QVector<doctor> _doctors;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
