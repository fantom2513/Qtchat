#include "adddatabaseform.h"
#include "ui_adddatabaseform.h"

addDatabaseForm::addDatabaseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addDatabaseForm)
{
    ui->setupUi(this);
}

addDatabaseForm::~addDatabaseForm()
{
    delete ui;
}

QStringList addDatabaseForm::getResult()
{
    return _results;
}

void addDatabaseForm::on_okBut_clicked()
{
    _results.append(ui->ipEdit->text());
    _results.append(ui->portEdit->text());
    _results.append(ui->nameEdit->text());
    _results.append(ui->userEdit->text());
    _results.append(ui->passwordEdit->text());
    emit accept();
}


void addDatabaseForm::on_closeBut_clicked()
{
    emit reject();
    close();
}

