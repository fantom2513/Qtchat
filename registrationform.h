#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include "Chat.h"

#include <QWidget>
#include <memory>

namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationForm(QWidget *parent = nullptr);
    ~RegistrationForm();
    void setChat(std::shared_ptr<Chat> chat);

signals:
    void loginRequested();
    void accept();
    void reject();

private slots:
    void on_loginBut_clicked();
    void on_okBut_clicked();
    void on_cancelBut_clicked();

private:
    Ui::RegistrationForm *ui;
    std::shared_ptr<Chat> _chat;
};

#endif // REGISTRATIONFORM_H
