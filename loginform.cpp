#include "loginform.h"
#include "BadLogin.h"
#include "BadPassword.h"
#include "ui_loginform.h"

#include <QMessageBox>

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::setChat(std::shared_ptr<Chat> chat)
{
    _chat = chat;
}

void LoginForm::on_registrationBut_clicked()
{
    emit  registrationRequested();
}


void LoginForm::on_okBut_clicked()
{
    try {
        _chat->login(ui->loginEdit->text().toStdString(), ui->passwordEdit->text().toStdString());
        emit accept();
    }
    catch (BadLogin& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
    catch (BadPassword& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}


void LoginForm::on_cancelBut_clicked()
{
    emit reject();
}

