#ifndef ROCVL_H
#define ROCVL_H

#include <QDialog>

namespace Ui {
class rocvl;
}

class rocvl : public QDialog
{
    Q_OBJECT

public:
    explicit rocvl(QWidget *parent = 0);
    ~rocvl();

public slots:
    void justClose();

private:
    Ui::rocvl *ui;
};

#endif // ROCVL_H
