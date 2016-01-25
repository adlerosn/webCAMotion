#include "errormsgafterfailure.h"
#include "ui_errormsgafterfailure.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <QShortcut>

using namespace std;

static QString errorcode="Error code: NUM";
static QString errordesc="Description: DESC";

int charsize(char* in)
{
    int cz=0;
    while (*(in+cz)!=0) cz++;
    return cz;
}

int wchartsize(wchar_t* in)
{
    int cz=0;
    while (*(in+cz)!=0) cz++;
    return cz;
}

wchar_t *char2wchart(char *in)
{
    int sz=charsize(in);
    static wchar_t out[255];
    int k=0;
    for (k=0;k<sz;k++) out[k]=in[k];
    return out;
}

/*
(ノಠ益ಠ)ノ彡┻━┻
ಠ_ರೃ
ಠ~ಠ
ಠ╭╮ಠ
ಠ▃ಠ
ಥ_ಥ
┻━┻ ︵ヽ(`Д´)ﾉ︵﻿ ┻━┻
*/

errorMsgAfterFailure::errorMsgAfterFailure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::errorMsgAfterFailure)
{
    ui->setupUi(this);
    QShortcut *shortcut = new QShortcut(QKeySequence("Esc"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(justClose()));
    ui->meme->setText(QString::fromUtf8("┻━┻ ︵ヽ(`Д´)ﾉ︵﻿ ┻━┻"));
    /*ui->meme->setText(QString::fromUtf8("(ノಠ益ಠ)ノ彡┻━┻"));*/
}

void errorMsgAfterFailure::setErrorCode(int in)
{
    char tmp[255];
    int k=0;
    for (k=0;k<255;k++) tmp[k]=0;
    snprintf(tmp,254,"Error code: %d",in);
    wchar_t tmp2[255];
    for (k=0;k<255;k++) tmp2[k]=tmp[k];
    errorcode=QString::fromWCharArray(tmp2,wchartsize(tmp2));
    ui->errcode->setText(errorcode);
}

void errorMsgAfterFailure::setErrorDesc(std::string in)
{
    errordesc=QString::fromStdString("Description: " + in);
    ui->errdesc->setText(errordesc);
}

errorMsgAfterFailure::~errorMsgAfterFailure()
{
    delete ui;
}

void errorMsgAfterFailure::justClose() {window()->close();}
