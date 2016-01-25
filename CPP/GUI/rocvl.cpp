#include "rocvl.h"
#include "ui_rocvl.h"
#include <QShortcut>

rocvl::rocvl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rocvl)
{
    ui->setupUi(this);
    QShortcut *shortcut = new QShortcut(QKeySequence("Esc"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(justClose()));
}

rocvl::~rocvl()
{
    delete ui;
}

void rocvl::justClose() {window()->close();}
