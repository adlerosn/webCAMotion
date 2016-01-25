#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

public slots:
    void justClose();
    void readLicOCV();
    void readLicLGPL();

private:
    Ui::About *ui;
};

#endif // ABOUT_H
