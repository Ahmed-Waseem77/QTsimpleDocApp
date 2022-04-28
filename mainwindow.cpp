#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitialiseDB();
    ui->comboBox->setCurrentIndex(-1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonRegister_clicked()
{
    QString RegisterName = ui->NameRegisTxbx->toPlainText();
    QString RegisterPassword = ui->PasswordRegisTxbx->toPlainText();
    QString RegisterAge = ui->AgeRegisTxbx->toPlainText();
    QString RegisterBalance = ui->BalanceRegisTxbx->toPlainText();
    bool RegisterationCorrect = true;

    int Age = RegisterAge.toInt();
    int Bal = RegisterBalance.toInt();

    if (Bal < 10)
    {
        ui->RegisterationStateLabel->setText("Please charge at least 10$");
        RegisterationCorrect = false;
    }

    if (Age < 0 || Age > 100 )
    {
        ui->RegisterationStateLabel->setText("Pick appropiate age [0-100]");
        RegisterationCorrect = false;
    }

    if(RegisterPassword.length() < 5)
    {
        ui->RegisterationStateLabel->setText("Password must be at least 5 characters");
        RegisterationCorrect = false;
    }

    for(auto it = _patients.begin(); it != _patients.end(); it++)
    {
        if((*it)->getName() == RegisterName)
        {
            ui->RegisterationStateLabel->setText("Username not available");
            RegisterationCorrect = false;
        }
    }

    if(RegisterName == "" || RegisterPassword == "" || RegisterAge == "" || RegisterBalance == "")
    {
        ui->RegisterationStateLabel->setText("Please fill All credentials");
        RegisterationCorrect = false;
    }

    if(RegisterationCorrect)
    {
        ui->RegisterationStateLabel->setText("Registered Successfully");
        patient* Temp =  new patient(RegisterName, RegisterPassword, RegisterAge, Bal);
        _patients.push_back(Temp);
    }
}

void MainWindow::on_pushButtonLogin_clicked()
{
    QString LoginName = ui->NameLogTxbx->toPlainText();
    QString LoginPass = ui->PasswordLogTxbx->toPlainText();
    for (auto it = _patients.begin(); it != _patients.end(); it++)
    {
        if((*it)->getName() == LoginName && (*it)->getPass() == LoginPass)
        {
            int balance = (*it)->getBlance();
            QString temp = QString::number(balance);
            temp = tr("%1").arg(balance);

            ui->PasswordStateLabel->setText(ui->LoginLabel->text() + ": Logged in\n" + "Balance: " + temp);
            ui->pushButtonLogin->setEnabled(false);
            ui->NameLogTxbx->setEnabled(false);
            ui->PasswordLogTxbx->setEnabled(false);
            return;
        }
        else if((*it)->getPass() != LoginPass)
        {
            ui->PasswordStateLabel->setText(ui->LoginLabel->text() + ": Invalid Password");

        }
        else
        {
            ui->PasswordStateLabel->setText(ui->LoginLabel->text() + ": Invalid login");

        }

    }

}

void MainWindow::on_pushButtonRecharge_clicked()
{
    bool RechargeOk = true;
    auto itr = _patients.begin();

    if(ui->RechargeTxBx->toPlainText() < "/" || ui->RechargeTxBx->toPlainText() > ":") //using UNICODE Integer ranges
    {
       ui->RechargeTxBx->setPlainText("Please Enter only positive Numbers");
       RechargeOk = false;
    }

    if(ui->PasswordStateLabel->text() == "Login: Invalid Password" || ui->PasswordStateLabel->text() == "Login: Invalid login" || ui->PasswordStateLabel->text() == "" ) //7arfeyan benetsha2a
    {
        ui->RechargeTxBx->setPlainText("Please Log In first");
        RechargeOk = false;
    }

    if(RechargeOk)
    {
         for (auto it = _patients.begin(); it != _patients.end(); it++)
         {
             itr = it;
             if(ui->NameLogTxbx->toPlainText() == (*it)->getName())
             {
                break;
             }


         }

         (*itr)->setBlance((*itr)->getBlance()+ui->RechargeTxBx->toPlainText().toInt());
         int bal = (*itr)->getBlance();
         QString temp = QString::number(bal);
         temp = tr("%1").arg(bal);
         ui->PasswordStateLabel->setText(ui->LoginLabel->text() + ": Logged in\n" + "Balance: " + temp);

    }

}


void MainWindow::on_pushButtonBooking_clicked()
{
    bool BookingOk = true;
    QString Logged = ui->PasswordStateLabel->text().mid(0, 26);
    auto itr = _patients.begin();

    if(ui->comboBox->currentIndex() == -1 ) //7arfeyan benetsha2a
    {
        ui->AppointmentLabel->setText("Please Choose a doctor");
        BookingOk = false;
    }

    if((ui->radioButtonMon->isChecked() || ui->radioButtonSun->isChecked() || ui->radioButtonSat->isChecked()) == false)
    {
        ui->AppointmentLabel->setText("Please Choose a date");
        BookingOk = false;
    }

    if(Logged != (ui->LoginLabel->text() + ": Logged in\n" + "Balance: "))
    {
        ui->AppointmentLabel->setText("Sign in first");
        BookingOk = false;
    }

    for (auto it = _patients.begin(); it != _patients.end(); it++) //gets patient
    {
        itr = it;
        if(ui->NameLogTxbx->toPlainText() == (*it)->getName())
        {
           break;
        }
    }

    if((*itr)->getBlance() < ui->DrFeesLabel->text().mid(10,-1).toInt())
    {
        ui->AppointmentLabel->setText("Recharge your Balance");
        BookingOk = false;
    }

    if(BookingOk)
    {
        ui->AgeLabel->setText(ui->AgeLabel->text() + (*itr)->getAge());
        ui->PatientLabel->setText(ui->PatientLabel->text() + (*itr)->getName());
        ui->DrNameLabel->setText(ui->DrNameLabel->text() + ui->comboBox->currentText());
        if(ui->radioButtonMon->isChecked())
        {
            ui->AppointmentDayLabel->setText(ui->AppointmentDayLabel->text() + "Monday");
        }
        if(ui->radioButtonSun->isChecked())
        {
            ui->AppointmentDayLabel->setText(ui->AppointmentDayLabel->text() + "Sunday");
        }
        if(ui->radioButtonSat->isChecked())
        {
            ui->AppointmentDayLabel->setText(ui->AppointmentDayLabel->text() + "Saturday");
        }

        ui->FeesLabel->setText(ui->FeesLabel->text() + ui->DrFeesLabel->text().mid(10,-1));

        (*itr)->setBlance((*itr)->getBlance()-ui->DrFeesLabel->text().mid(10,-1).toInt());

        int balance = (*itr)->getBlance();
        QString temp = QString::number(balance);
        temp = tr("%1").arg(balance);

        ui->PasswordStateLabel->setText(ui->LoginLabel->text() + ": Logged in\n" + "Balance: " + temp);



    }


}


void MainWindow::on_comboBox_activated(int index)
{

    int fee = 0;
    QString temp = "";
    switch(index)
    {
    case 0:
        fee = _doctors[3].getfee();
        temp = QString::number(fee);
        temp = tr("%1").arg(fee);

        ui->DrFeesLabel->setText("Dr Fees: $" + temp);
        break;
    case 1:
        fee = _doctors[1].getfee();
        temp = QString::number(fee);
        temp = tr("%1").arg(fee);

        ui->DrFeesLabel->setText("Dr Fees: $" + temp);
        break;
    case 2:
        fee = _doctors[2].getfee();
        temp = QString::number(fee);
        temp = tr("%1").arg(fee);

        ui->DrFeesLabel->setText("Dr Fees: $" + temp);
        break;

    case 3:
        fee = _doctors[0].getfee();
        temp = QString::number(fee);
        temp = tr("%1").arg(fee);

        ui->DrFeesLabel->setText("Dr Fees: $" + temp);
        break;

    }
}



