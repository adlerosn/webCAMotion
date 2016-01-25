#ifndef RLGPL_H
#define RLGPL_H

#include <QDialog>

namespace Ui {
class rlgpl;
}

class rlgpl : public QDialog
{
    Q_OBJECT

public:
    explicit rlgpl(QWidget *parent = 0);
    ~rlgpl();

public slots:
    void justClose();

private:
    Ui::rlgpl *ui;
};

#endif // RLGPL_H
