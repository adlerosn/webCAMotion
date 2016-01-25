#ifndef SELECTSOMETHING_H
#define SELECTSOMETHING_H

#include <QDialog>

namespace Ui {
class SelectSomething;
}

class SelectSomething : public QDialog
{
    Q_OBJECT

public:
    explicit SelectSomething(QWidget *parent = 0);
    ~SelectSomething();

public slots:
    void justClose();

private:
    Ui::SelectSomething *ui;
};

#endif // SELECTSOMETHING_H
