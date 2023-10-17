#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "Chat.h"
#include "User.h"

#include <QDialog>
#include <memory>

namespace Ui {
class StartScreen;
}

class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(std::shared_ptr<Chat> chat = nullptr, QWidget *parent = nullptr);
    ~StartScreen();
    void setLoginForm();
    void setRegistrationForm();
    void setDatabase();
    std::shared_ptr<User> getActiveUser();
    QStringList getConnectParams();
    static bool _wasOpenedOnce;

private:
    Ui::StartScreen *ui;
    std::shared_ptr<Chat> _chat;
    QStringList _connectParams;
};

#endif // STARTSCREEN_H
