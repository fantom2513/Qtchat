#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include "Chat.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();
    void setChat(std::shared_ptr<Chat> chat);

signals:
    void registrationRequested();
    void accept();
    void reject();

private slots:
    void on_registrationBut_clicked();
    void on_okBut_clicked();
    void on_cancelBut_clicked();

private:
    Ui::LoginForm *ui;
    std::shared_ptr<Chat> _chat;
};

#endif // LOGINFORM_H
