#ifndef ADDDATABASEFORM_H
#define ADDDATABASEFORM_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class addDatabaseForm;
}

class addDatabaseForm : public QWidget
{
    Q_OBJECT

public:
    explicit addDatabaseForm(QWidget *parent = nullptr);
    ~addDatabaseForm();
    QStringList getResult();

signals:
    void accept();
    void reject();

private slots:
    void on_okBut_clicked();
    void on_closeBut_clicked();

private:
    Ui::addDatabaseForm *ui;
    QStringList _results;
};

#endif // ADDDATABASEFORM_H
