#include "rlgpl.h"
#include "ui_rlgpl.h"
#include <QShortcut>

rlgpl::rlgpl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rlgpl)
{
    ui->setupUi(this);
    QShortcut *shortcut = new QShortcut(QKeySequence("Esc"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(justClose()));
}

rlgpl::~rlgpl()
{
    delete ui;
}

void rlgpl::justClose() {window()->close();}
