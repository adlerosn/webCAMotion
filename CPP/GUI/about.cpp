#include "about.h"
#include "ui_about.h"
#include "rlgpl.h"
#include "rocvl.h"
#include <QShortcut>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    QShortcut *shortcut = new QShortcut(QKeySequence("Esc"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(justClose()));

  /*QPixmap image;
    QImage  *imageObject;
    QGraphicsScene *scene;
    QString imagePath = "smallicon.gif";

    imageObject = new QImage();
    imageObject->load(imagePath);

    image = QPixmap::fromImage(*imageObject);

    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    ui->logo->setScene(scene);*/
}

About::~About()
{
    delete ui;
}

void About::readLicLGPL()
{
    rlgpl fsf;
    fsf.setModal(false);
    fsf.exec();
}

void About::readLicOCV()
{
    rocvl bsd;
    bsd.setModal(false);
    bsd.exec();
}

void About::justClose() {window()->close();}
