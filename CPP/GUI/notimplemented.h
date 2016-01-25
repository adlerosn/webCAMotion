#ifndef NOTIMPLEMENTED_H
#define NOTIMPLEMENTED_H

#include <QDialog>

namespace Ui {
class NotImplemented;
}

class NotImplemented : public QDialog
{
    Q_OBJECT

public:
    explicit NotImplemented(QWidget *parent = 0);
    ~NotImplemented();

public slots:
    void justClose();

private:
    Ui::NotImplemented *ui;
};

#endif // NOTIMPLEMENTED_H
