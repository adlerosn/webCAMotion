#ifndef ERRORMSGAFTERFAILURE_H
#define ERRORMSGAFTERFAILURE_H

#include <QDialog>

namespace Ui {
class errorMsgAfterFailure;
}

class errorMsgAfterFailure : public QDialog
{
    Q_OBJECT

public:
    explicit errorMsgAfterFailure(QWidget *parent = 0);
    ~errorMsgAfterFailure();

public slots:
    void justClose();
    void setErrorCode(int in);
    void setErrorDesc(std::string in);

private:
    Ui::errorMsgAfterFailure *ui;
};

#endif // ERRORMSGAFTERFAILURE_H
