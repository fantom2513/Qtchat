#include "registrationform.h"
#include "ui_registrationform.h"
#include "BadLogin.h"

#include <QMessageBox>

RegistrationForm::RegistrationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::setChat(std::shared_ptr<Chat> chat)
{
    _chat = chat;
}

void RegistrationForm::on_loginBut_clicked()
{
    emit loginRequested();
}


void RegistrationForm::on_okBut_clicked()
{
    if (ui->passwordEdit->text() != ui->passwordConfirm->text()) {
        QMessageBox::critical(this, "Error", "Passwords not match");
        return;
    }
    try {
        _chat->createNewUser(ui->nameEdit->text().toStdString(), ui->LoginEdit->text().toStdString(), ui->passwordEdit->text().toStdString());
        emit accept();
    }    catch (BadLogin& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}


void RegistrationForm::on_cancelBut_clicked()
{
    emit reject();
}

