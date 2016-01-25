#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "about.h"
#include "notimplemented.h"
#include "selectsomething.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void justClose();
    void buttonOpenAbout();
    void clickinNI();
    void sel1();
    void sel2();
    void sel3();
    void sel4();
    void sel5();
    void sel5things(bool);
    void sel4things(bool);
    void BR();
    void BG();
    void BB();
    void PR();
    void PG();
    void PB();
    void CR();
    void CG();
    void CB();
    void unselectEverything();
    void wcnum(int);
    void latch(int);
    void edoff(int);
    void setSizeOfThePointer(int);
    void setTriggerDistance(int);
    void setDistanceFromScreen(int);
    void setScreenSize(int);
    void clickedOK();
    void ChkBoxChanged(bool);
    int whatgivesBcolor();
    int whatgivesPcolor();
    int whatgivesCcolor();
    int whatgivesWM();//working mode (radio button selected)
    bool whatgivesB();//clicked in OK?
    int whatgivesCM();//camera num
    int whatgivesBF();//latency
    int whatgivesOF();//border offset
    int whatgivesCP();//Base's to edge's color pointer distance
    int whatgivesDC();//disable clicking
    int whatgivesDD();//display distance
    int whatgivesT(); //trigger distance
    int whatsthescreensize();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
/*
public: signals:
    static void reverserB(bool in);
 */

private slots:
    void on_actionAboutOpen_triggered();

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
