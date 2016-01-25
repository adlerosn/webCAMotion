#include "selectsomething.h"
#include "ui_selectsomething.h"
#include <QShortcut>

SelectSomething::SelectSomething(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectSomething)
{
    ui->setupUi(this);
    QShortcut *shortcut = new QShortcut(QKeySequence("Esc"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(justClose()));
}

SelectSomething::~SelectSomething()
{
    delete ui;
}

void SelectSomething::justClose() {window()->close();}
