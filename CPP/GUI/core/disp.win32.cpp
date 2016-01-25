#ifndef WIN32_DISP_CPP
#define WIN32_DISP_CPP
#include <windows.h>

typedef unsigned char u_int8_t; //NOW WORKS !!!

struct screenControl {}; typedef struct screenControl screenControl;

/*
void gotoMouse(screenControl, coordinate co) {
    COORD coord;
    coord.X = co.x;
    coord.Y = co.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void mouseclick{
    GetCursorPos(&pos_cursor);
    hwnd_outra_win = WindowFromPoint(pos_cursor);
    SendMessage(hwnd_outra_win,WM_LBUTTONDOWN,MK_LBUTTON,MAKELPARAM(pos_cursor.x,pos_cursor.y));
    SendMessage(hwnd_outra_win,WM_LBUTTONUP,0,MAKELPARAM(pos_cursor.x,pos_cursor.y));
}*/


screenControl initScreenControl()
{
    screenControl scr;
    return scr;
}

void endScreenControl(screenControl scr)
{
    ;
}

coordinate ScrSize(screenControl scr)
{
    coordinate sz;
    RECT desktop;
    HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    sz.x=desktop.right;
    sz.y=desktop.bottom;
    return sz;
}

void gotoMouse(screenControl sc, coordinate co)
{
    coordinate s;
    s=ScrSize(sc);
    INPUT thisInput = { 0 };
    thisInput.type = INPUT_MOUSE;
    thisInput.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    thisInput.mi.dx = (LONG)(long int)((65536/((float)s.x))*co.x);
    thisInput.mi.dy = (LONG)(long int)((65536/((float)s.y))*co.y);
    SendInput(1, &thisInput, sizeof(INPUT));
}

void clickCode(screenControl sc, int code)
{
    INPUT thisInput = { 0 };
    thisInput.type = INPUT_MOUSE;
    if (code==1) thisInput.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN;
    if (code!=1) thisInput.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP;
    SendInput(1, &thisInput, sizeof(INPUT));
    if (code==2) thisInput.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN;
    if (code!=2) thisInput.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTUP;
    SendInput(1, &thisInput, sizeof(INPUT));
    if (code==3) thisInput.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MIDDLEDOWN;
    if (code!=3) thisInput.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MIDDLEUP;
    SendInput(1, &thisInput, sizeof(INPUT));
}

#endif //WIN32_DISP_CPP
