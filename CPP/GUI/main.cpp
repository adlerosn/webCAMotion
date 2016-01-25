#define THIS_IS_THE_FILE_THAT_HOLDS_THE_MAIN
#include "mainwindow.h"
#include "errormsgafterfailure.h"
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <opencv2/opencv.hpp>

int *gui(int argc, char *argv[])
{
    static int retd[15];
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    retd[14]=a.exec();           //function return
    retd[13]=w.whatsthescreensize();
    retd[12]=w.whatgivesCcolor();
    retd[11]=w.whatgivesPcolor();
    retd[10]=w.whatgivesBcolor();
    retd[9]=1; //add this to GUI
    retd[8]=w.whatgivesDC();    //disable clicking
    retd[7]=w.whatgivesCP();    //Blue-Red distance
    retd[6]=w.whatgivesDD();    //display distance
    retd[5]=w.whatgivesT();     //trigger distance
    retd[4]=w.whatgivesB();     //clicked in OK?
    retd[3]=w.whatgivesOF();    //border offset
    retd[2]=w.whatgivesBF();    //latency
    retd[1]=w.whatgivesCM();    //camera num
    retd[0]=w.whatgivesWM();    //working mode (radio button selected)
    return retd;
}

void errorMsgAfter(int codeRet, int argc, char *argv[])
{
    //Creating error lib
    std::string key[256];
    int k;
    for (k=0;k<256;k++) key[k]="I don't have a clue what happened";
    //Putting known errors on it
    key[255]="Camera not found.";
    key[127]="There's an error of logic in the source code of the program, and you triggered it. Someone has to fix it.";
    key[007]="Your webcam didn't return an image in 30 requests. Program was aborted safely.";
    key[003]="Your camera must have 3 channels of colors (RGB).";
    key[002]="Graphical User Interface sent to the core of this program an invalid parameter.";
    key[000]="The error is that the program ended normally.";
    //Finished

    //Printing error on terminal
    std::cout << "Error #" << codeRet << ": "<< key[codeRet] << '\n' << std::endl;
    //Displaying error message
    QApplication a(argc, argv);
    errorMsgAfterFailure we;
    we.setErrorCode(codeRet);
    we.setErrorDesc(key[codeRet]);
    we.setModal(false);
    we.show();
    a.exec();
}

#include "core/core.cpp"

int main(int argc, char *argv[])
{
    int *workmode;
    workmode = gui(argc,argv);
    int coolret=0;
    if (workmode[4])
        coolret = theCoolPart(workmode[1],workmode[2]+1,workmode[0]-1,workmode[3],
                              workmode[5],workmode[6],  workmode[7],  workmode[8],
                              workmode[10]-1,workmode[11]-1,workmode[12]-1,
                              workmode[13]);
    if (coolret!=0)
        errorMsgAfter(coolret, argc, argv);
    return coolret;
}
