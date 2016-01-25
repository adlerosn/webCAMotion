#include "notimplemented.h"
#include "ui_notimplemented.h"
#include <QShortcut>

NotImplemented::NotImplemented(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotImplemented)
{
    ui->setupUi(this);
    QShortcut *shortcut = new QShortcut(QKeySequence("Esc"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(justClose()));
}

NotImplemented::~NotImplemented()
{
    delete ui;
}

void NotImplemented::justClose() {window()->close();}
