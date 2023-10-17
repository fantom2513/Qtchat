#include "startscreen.h"
#include "ui_startscreen.h"

bool StartScreen::_wasOpenedOnce = false;

StartScreen::StartScreen(std::shared_ptr<Chat> chat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);
    if (chat)
        _chat = chat;
    else
        _chat = std::make_shared<Chat>();

    ui->loginWgt->setChat(_chat);
    ui->registrationWgt->setChat(_chat);

    connect(ui->dbform, &addDatabaseForm::accept, this, &StartScreen::setDatabase);
    connect(ui->dbform, &addDatabaseForm::reject, this, &StartScreen::reject);
    connect(ui->loginWgt, &LoginForm::registrationRequested, this, &StartScreen::setRegistrationForm);
    connect(ui->loginWgt, &LoginForm::accept, this, &StartScreen::accept);
    connect(ui->loginWgt, &LoginForm::reject, this, &StartScreen::reject);
    connect(ui->registrationWgt, &RegistrationForm::loginRequested, this, &StartScreen::setLoginForm);
    connect(ui->registrationWgt, &RegistrationForm::accept, this, &StartScreen::accept);
    connect(ui->registrationWgt, &RegistrationForm::reject, this, &StartScreen::reject);
    if (_wasOpenedOnce)
        ui->stackedWidget->setCurrentIndex(0);
    else {
        ui->stackedWidget->setCurrentIndex(2);
        _wasOpenedOnce = true;
    }
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::setLoginForm()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void StartScreen::setRegistrationForm()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void StartScreen::setDatabase()
{
    _connectParams = ui->dbform->getResult();
    _chat->createDBConnection(_connectParams);
    setLoginForm();
}

std::shared_ptr<User> StartScreen::getActiveUser()
{
    return _chat->getActiveUser();
}

QStringList StartScreen::getConnectParams()
{
    return _connectParams;
}
