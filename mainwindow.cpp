#include "mainwindow.h"
#include "startscreen.h"
#include "ui_mainwindow.h"
#include "Chat.h"
#include "User.h"

#include <QTimer>
#include <QStringList>

int MainWindow::_instancesCount = 0;
QStringList MainWindow::_connectionParams;

MainWindow::MainWindow(User activeUser, QStringList connectParams, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      _chat(std::make_shared<Chat>()),
      _activeUser(activeUser)
{
    ui->setupUi(this);
    _chat->createDBConnection(connectParams);
    _chat->setActiveUser(std::make_shared<User>(activeUser));
    setWindowTitle(QString::fromStdString(_chat->getActiveUser()->getLogin()));
    fillComboBox();
    connect(ui->usersBox, &QComboBox::currentTextChanged, this, &MainWindow::on_usersBox_currentTextChanged);
    fillMessagesForAll();
    fillPrivateMessages();
    _instancesCount++;

    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &MainWindow::updateCharts);
    _timer->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
    _instancesCount--;
    if (_instancesCount <= 0)
        qApp->exit(0);
}

MainWindow *MainWindow::createClient(std::shared_ptr<Chat> chat)
{
    StartScreen s(chat);
    auto result = s.exec();
    if (result == QDialog::Rejected)
        return nullptr;
    if (_connectionParams.isEmpty())
        _connectionParams = s.getConnectParams();
    auto w = new MainWindow(*s.getActiveUser().get(), _connectionParams);
    w->setAttribute(Qt::WA_DeleteOnClose);
    return w;
}

void MainWindow::on_lineEditMessage_returnPressed()
{
    on_sendAllBut_clicked();
}

void MainWindow::on_sendAllBut_clicked()
{
    _chat->setActiveUser(std::make_shared<User>(_activeUser));
    _chat->writeToAll(ui->lineEditMessage->text().toStdString());
}

void MainWindow::on_sendPrivateBut_clicked()
{
    _chat->setActiveUser(std::make_shared<User>(_activeUser));
    std::string text = ui->lineEditMessage->text().toStdString();
    std::shared_ptr<User> user = _chat->getUser(ui->usersBox->currentText().toStdString());
    _chat->writeToOne(text, user);
}

void MainWindow::on_actionOpen_another_client_triggered()
{
    auto w = createClient(_chat);
    if (w)
        w->show();
}

void MainWindow::on_actionClose_this_client_triggered()
{
    _timer->stop();
    close();
}

void MainWindow::fillComboBox()
{
    ui->usersBox->addItems(_chat->getAllLogins());
}

void MainWindow::fillMessagesForAll(QStringList messages)
{
    if (messages.isEmpty())
        messages = _chat->getMessages(false);
   _countAllMessages = messages.size();
   QString txt;
   QString line = "<b>%1</b> %2<br>&nbsp;&nbsp;&nbsp;&nbsp;%3<br>";
   for(int i = 0; i < messages.size()-2; i+=3) {
       txt.append(line.arg(messages.at(i)).arg(messages.at(i+2)).arg(messages.at(i+1)));
   }
   ui->messagesForAll->setText(txt);
}

void MainWindow::fillPrivateMessages(QStringList messages)
{
    _chat->setActiveUser(std::make_shared<User>(_activeUser));
    if (messages.isEmpty())
        messages = _chat->getMessages(true, ui->usersBox->currentText());
    _countPrivateMessages = messages.size();
    QString txt;
    QString line = "<b>%1</b> %2<br>&nbsp;&nbsp;&nbsp;&nbsp;%3<br>";
    for(int i = 0; i < messages.size()-2; i+=3) {
        txt.append(line.arg(messages.at(i)).arg(messages.at(i+2)).arg(messages.at(i+1)));
    }
    ui->privateMessages->setText(txt);
}


void MainWindow::on_usersBox_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    fillPrivateMessages();
}

void MainWindow::updateCharts()
{
    _chat->setActiveUser(std::make_shared<User>(_activeUser));

    QStringList allMessages = _chat->getMessages(false);
    if (_countAllMessages != allMessages.size())
        fillMessagesForAll(allMessages);


    QStringList messages = _chat->getMessages(true, ui->usersBox->currentText());
    if (_countPrivateMessages != messages.size())
        fillPrivateMessages(messages);
}
