#ifndef LINUX_DISP_CPP
#define LINUX_DISP_CPP
#include <X11/extensions/XTest.h>

/* //The coordinate structure isn't recognized by IDE (Qt Creator), but is recognized by compiler (g++).
struct coordinate    {int x; int y;};                                typedef struct coordinate    coordinate;*/
struct screenControl {Display *disp; XEvent event; Screen *screen;}; typedef struct screenControl screenControl;

screenControl initScreenControl()
{
    screenControl scr;
    scr.disp = XOpenDisplay(NULL);
    scr.screen = DefaultScreenOfDisplay(scr.disp);
    return scr;
}

void endScreenControl(screenControl scr)
{
    XCloseDisplay(scr.disp);
}

coordinate ScrSize(screenControl scr)
{
    coordinate sz;
    sz.x = scr.screen->width;
    sz.y = scr.screen->height;
    return sz;
}

void gotoMouse(screenControl sc, coordinate co)
{
    XTestFakeMotionEvent(sc.disp, 0, co.x, co.y, CurrentTime);
    XSync(sc.disp, 0);
}

void clickCode(screenControl sc, int code)
{
    if (code==1) XTestFakeButtonEvent(sc.disp, Button1, true, CurrentTime);
    if (code==2) XTestFakeButtonEvent(sc.disp, Button2, true, CurrentTime);
    if (code==3) XTestFakeButtonEvent(sc.disp, Button3, true, CurrentTime);
    if (code==4) XTestFakeButtonEvent(sc.disp, Button4, true, CurrentTime);
    if (code==5) XTestFakeButtonEvent(sc.disp, Button5, true, CurrentTime);
    if (code!=1) XTestFakeButtonEvent(sc.disp, Button1, false, CurrentTime);
    if (code!=2) XTestFakeButtonEvent(sc.disp, Button2, false, CurrentTime);
    if (code!=3) XTestFakeButtonEvent(sc.disp, Button3, false, CurrentTime);
    if (code!=4) XTestFakeButtonEvent(sc.disp, Button4, false, CurrentTime);
    if (code!=5) XTestFakeButtonEvent(sc.disp, Button5, false, CurrentTime);
    XSync(sc.disp, 0);
}

#endif //LINUX_DISP_CPP
