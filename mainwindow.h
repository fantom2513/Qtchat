#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Chat.h"
#include "User.h"

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(User activeUser, QStringList connectParams, QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* createClient(std::shared_ptr<Chat> chat = nullptr);
    static int _instancesCount;
    static QStringList _connectionParams;

private slots:
    void on_lineEditMessage_returnPressed();
    void on_sendAllBut_clicked();
    void on_sendPrivateBut_clicked();
    void on_actionOpen_another_client_triggered();
    void on_actionClose_this_client_triggered();
    void on_usersBox_currentTextChanged(const QString &arg1);
    void updateCharts();

private:
    void fillComboBox();
    void fillMessagesForAll(QStringList messages = QStringList());
    void fillPrivateMessages(QStringList messages = QStringList());

    Ui::MainWindow *ui;
    std::shared_ptr<Chat> _chat;
    User _activeUser;
    int _countAllMessages;
    int _countPrivateMessages;
    QTimer* _timer;
};
#endif // MAINWINDOW_H
