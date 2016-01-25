#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include "notimplemented.h"
#include "selectsomething.h"
#include <stdio.h>
#include <QShortcut>

static int returnRadioSelectionToUser=0;
static bool selected=false;
static int camnum=0;
static int bufframes=0;
static int offsed=10;//percent
static int becpd=15;//cm
static bool disClick=false;
static int dispDist=50;//cm
static int trigDist=100;//px
static int color[3];
static int screensize=14; //inches
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sel5things(false);
    sel4things(false);
    QShortcut *shortcutquit = new QShortcut(QKeySequence("Esc"), this);
    connect(shortcutquit, SIGNAL(activated()), this, SLOT(justClose()));
    QShortcut *shortcuthelp = new QShortcut(QKeySequence("F1"), this);
    connect(shortcuthelp, SIGNAL(activated()), this, SLOT(buttonOpenAbout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAboutOpen_triggered()
{
    About ab;
    ab.setModal(true);
    ab.exec();
}

void MainWindow::buttonOpenAbout()
{
    About ab;
    ab.setModal(true);
    ab.exec();
};

void MainWindow::clickinNI()
{
    NotImplemented nimpl;
    nimpl.setModal(false);
    nimpl.exec();
}

void MainWindow::sel1()
{
    returnRadioSelectionToUser=1;
    sel4things(false);
    sel5things(false);
};
void MainWindow::sel2()
{
    returnRadioSelectionToUser=2;
    sel4things(false);
    sel5things(false);
};
void MainWindow::sel3()
{
    returnRadioSelectionToUser=3;
    sel4things(false);
    sel5things(false);
};
void MainWindow::sel4()
{
    returnRadioSelectionToUser=4;
    sel4things(true);
    sel5things(false);
};
void MainWindow::sel5()
{
    returnRadioSelectionToUser=5;
    //not implemented -- undo
    //returnRadioSelectionToUser=-1;
    sel4things(true);
    sel5things(true);
    ui->rBfiller->setChecked(true);
    ui->rPfiller->setChecked(true);
    ui->rCfiller->setChecked(true);
    ui->rBfiller->setVisible(false);
    ui->rPfiller->setVisible(false);
    ui->rCfiller->setVisible(false);
};
void MainWindow::sel5things(bool i)
{
    ui->gB->setVisible(i);
    ui->gP->setVisible(i);
    ui->gC->setVisible(i);
    ui->ldfc->setVisible(i);
    ui->sdfc->setVisible(i);
    ui->pdfc->setVisible(i);
    ui->lsotp->setVisible(i);
    ui->ssotp->setVisible(i);
    ui->psotp->setVisible(i);
    ui->lscrsz->setVisible(i);
    ui->sscrsz->setVisible(i);
    ui->pscrsz->setVisible(i);
}

void MainWindow::sel4things(bool i)
{
    ui->ltd->setVisible(i);
    ui->std->setVisible(i);
    ui->ptd->setVisible(i);
    if (i)
        ui->checkBox->setChecked(false);
}

void MainWindow::justClose() {window()->close();}

void MainWindow::clickedOK()
{
    if ((returnRadioSelectionToUser>=1) && (returnRadioSelectionToUser<=4))
    {
        selected=true;
        ui->controlbtn->window()->close();
    }
    else if (returnRadioSelectionToUser==5)
    {
        if ((color[0]==0)||(color[1]==0)||((!(disClick))&&(color[2]==0)))
        {
            SelectSomething ss;
            ss.setModal(false);
            ss.exec();
        }
        else
        {
            selected=true;
            ui->controlbtn->window()->close();
        }
    }
    else if ((returnRadioSelectionToUser)==(-1))
    {
        MainWindow::clickinNI();
    }
    else
    {
        SelectSomething ss;
        ss.setModal(false);
        ss.exec();
    }
};


void MainWindow::wcnum(int in)
{
    camnum=in;
}

void MainWindow::latch(int in)
{
    bufframes=in;
}

void MainWindow::edoff(int in)
{
    offsed=in;
}

int MainWindow::whatgivesWM()
{
    return returnRadioSelectionToUser;
}

bool MainWindow::whatgivesB()
{
    return selected;
}

int MainWindow::whatgivesCM()
{
    return camnum;
}

int MainWindow::whatgivesBF()
{
    return bufframes;
}

int MainWindow::whatgivesOF()
{
    return offsed;
}

int MainWindow::whatgivesDC()//disable clicking
{
    return disClick;
}

int MainWindow::whatgivesDD()//display distance
{
    return dispDist;
}

int MainWindow::whatgivesT() //trigger distance
{
    return trigDist;
}

int MainWindow::whatgivesCP()//Base's to edge's color pointer distance
{
   return becpd;
}

void MainWindow::ChkBoxChanged(bool i)
{
    disClick=i;
    if (i)
        {
        color[2]=0;
        ui->rCR->setChecked(false);
        ui->rCG->setChecked(false);
        ui->rCB->setChecked(false);
        ui->rCfiller->setChecked(true);
        }
}

void MainWindow::unselectEverything()
{
    int k;
    for (k=0;k<3;k++)
        color[k]=0;
    ui->rBR->setChecked(false);
    ui->rBG->setChecked(false);
    ui->rBB->setChecked(false);
    ui->rPR->setChecked(false);
    ui->rPG->setChecked(false);
    ui->rPB->setChecked(false);
    ui->rCR->setChecked(false);
    ui->rCG->setChecked(false);
    ui->rCB->setChecked(false);
    ui->rBfiller->setChecked(true);
    ui->rPfiller->setChecked(true);
    ui->rCfiller->setChecked(true);
}

void MainWindow::BR()
{
    color[0]=3;
    if ((color[0]==color[1])||(color[0]==color[2]))
        unselectEverything();
}

void MainWindow::BG()
{
    color[0]=2;
    if ((color[0]==color[1])||(color[0]==color[2]))
        unselectEverything();
}

void MainWindow::BB()
{
    color[0]=1;
    if ((color[0]==color[1])||(color[0]==color[2]))
        unselectEverything();
}

void MainWindow::PR()
{
    color[1]=3;
    if ((color[1]==color[0])||(color[1]==color[2]))
        unselectEverything();
}

void MainWindow::PG()
{
    color[1]=2;
    if ((color[1]==color[0])||(color[1]==color[2]))
        unselectEverything();
}

void MainWindow::PB()
{
    color[1]=1;
    if ((color[1]==color[0])||(color[1]==color[2]))
        unselectEverything();
}

void MainWindow::CR()
{
    color[2]=3;
    if ((color[2]==color[0])||(color[2]==color[1]))
        unselectEverything();
}

void MainWindow::CG()
{
    color[2]=2;
    if ((color[2]==color[0])||(color[2]==color[1]))
        unselectEverything();
}

void MainWindow::CB()
{
    color[2]=1;
    if ((color[2]==color[0])||(color[2]==color[1]))
        unselectEverything();
}

int MainWindow::whatgivesBcolor()
{
    return color[0];
}

int MainWindow::whatgivesPcolor()
{
    return color[1];
}

int MainWindow::whatgivesCcolor()
{
    return color[2];
}

int MainWindow::whatsthescreensize()
{
    return screensize;
}

void MainWindow::setSizeOfThePointer(int i)
{
    becpd=i;
}

void MainWindow::setTriggerDistance(int i)
{
    trigDist=i;
}

void MainWindow::setDistanceFromScreen(int i)
{
    dispDist=i;
}

void MainWindow::setScreenSize(int i)
{
    screensize=i;
}
