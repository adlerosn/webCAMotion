#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

int GVAR1 = 0;

#include "core.h"
#include "core.os.cpp"

using namespace std;
using namespace cv;

u_int8_t theCoolPart(int camnum, int smoothNumberFrames, int workingMethod, int inputoffset, int dtrig,
                     int distanceAwayDisplay, int baseToEdgeDistance, int clickingDisabled,
                     int colorBase, int colorEdge, int colorClicker, int screensize)
    {
    screenControl scrctrl = initScreenControl();
    coordinate mainScreenSize = ScrSize(scrctrl);
    int scrx = mainScreenSize.x;
    int scry = mainScreenSize.y;
    if (smoothNumberFrames<1){smoothNumberFrames=1;}; //avoiding crashes
    VideoCapture cap(camnum);
    if(!cap.isOpened()){endScreenControl(scrctrl);return -1;};
    char windowname[256]="webCAMotion - press ESC or click in the window to exit";
    namedWindow(windowname, WINDOW_AUTOSIZE);
    setMouseCallback(windowname, clickedInImage, NULL);
    Mat captured;
    Mat frame;
    Mat frameCP;
    Mat chGRAY;
    Mat frameS[3];                                    //I dont expect a 4-channel cammera
    coordinate coords[4];                             //I dont expect a 4-channel cammera - 4th index is for mouse
    coordinate smoothedcoords[4];                     //I dont expect a 4-channel cammera - 4th index is for mouse
    coordinate coordhistory[4][smoothNumberFrames+1]; //I dont expect a 4-channel cammera - 4th index is for mouse
    int dist[3];
    bool bdist[3];
    int mx;
    int my;
    int coordhistoryptr=0;
    int cn;
    int lin;
    int col;
    int clickcond;
    int clickcode;
    int k=0; //general purpose
    cap >> captured; //this frame is just for getting metadata
    while (captured.data == NULL && k<30){
        waitKey(5);
        cap >> captured;
        k++;
    }
    if(k==30){
        endScreenControl(scrctrl);
        return 7;
    }
    imshow(windowname, captured);
    lin=captured.rows;
    col=captured.cols;
    cn =captured.channels();
    if (cn!=3) {endScreenControl(scrctrl);return 3;};
    for(;;)
        {
        k=0;
        cap >> captured;
        while (captured.data == NULL && k<30){
            waitKey(5);
            cap >> captured;
            k++;
        }
        if(k==30){
            endScreenControl(scrctrl);
            return 7;
        }
        flip(captured,captured,1);
        cvtColor(captured,chGRAY,CV_BGR2GRAY);
        split(captured,frameS);
        merge(frameS,cn,frameCP);
        for (k=(cn-1);k>=0;k--)
        	{
        	subtract(frameS[k],chGRAY,frameS[k]);
        	};
        merge(frameS,cn,frame);
        for (k=(cn-1);k>=0;k--)
        	{
            coords[k]=bestIlluminati(frame,lin,col,k);
            };
        //SMOOTHING MOVEMENTS
        coordhistoryptr=((coordhistoryptr)%(smoothNumberFrames+1));
        for (k=0;k<cn;k++)
            {
            coordhistory[k][coordhistoryptr]=coords[k];
            };
        for (k=0;k<cn;k++)
            {
            smoothedcoords[k]=smootherPoints(coordhistory[k],coordhistoryptr,smoothNumberFrames);
            };
        //printf("%03dx%03d;%d==(%03d,%03d),(%03d,%03d),(%03d,%03d)\n",col,lin,cn,smoothedcoords[0].x,smoothedcoords[0].y,smoothedcoords[1].x,smoothedcoords[1].y,smoothedcoords[2].x,smoothedcoords[2].y);
        //printf("%03dx%03d;%d==(%03d,%03d),(%03d,%03d),(%03d,%03d)\n",col,lin,cn,coords[0].x,coords[0].y,coords[1].x,coords[1].y,coords[2].x,coords[2].y);
        //MAKING SELECTION VISIBLE
        /*for (k=0;k<cn;k++)
            {
            makeSelectionVisible(frameCP,k,cn,lin,col,smoothedcoords[k]);
            };*/
        for (k=(cn-1);k>=0;k--)
            {
            makeSelectionVisible(frameCP,k,cn,lin,col,coords[k]);
            };
        //SHOWING TO USER
        imshow(windowname, frameCP);
        if((waitKey(15) >= 0) || GVAR1) break;

        ///////////////////////////////////////
        //MOUSE EVENTS - PLANNING
        if (workingMethod==0)
         	{
         	mx=coords[2].x;
         	my=coords[2].y;
         	}
        else if (workingMethod==1)
         	{
         	mx=coords[1].x;
         	my=coords[1].y;
         	}
        else if (workingMethod==2)
         	{
         	mx=coords[0].x;
         	my=coords[0].y;
         	}
        else if (workingMethod==3)
            {
            mx=coords[1].x;
            my=coords[1].y;
            }
        else if (workingMethod==4)
            {
            coordhistory[3][coordhistoryptr]=wherePointing(coords,col,lin,scrx,scry,
                                                           distanceAwayDisplay, baseToEdgeDistance, colorBase,
                                                           colorEdge, screensize);
            }
        else {endScreenControl(scrctrl);return 2;};
        if ((workingMethod==0)||(workingMethod==1)||(workingMethod==2)||(workingMethod==3))
            coordhistory[3][coordhistoryptr]=proportionWebcamToScreen(mx,my,col,lin,scrx,scry,inputoffset);
        smoothedcoords[3]=smootherPoints(coordhistory[3],coordhistoryptr,smoothNumberFrames);
        //printf("%04d,%03d=<o>=%04d,%03d\n",mx,my,smoothedcoords[3].x,smoothedcoords[3].y);
        //printf("%04d,%03d=<o>=%04d,%03d\n",col,lin,scrx,scry);
        if ((workingMethod==3) || (workingMethod==4))
            {
            dist[0] = euclideanDistance(smoothedcoords[0],smoothedcoords[1]                  ); //bg
            dist[1] = euclideanDistance(                  smoothedcoords[1],smoothedcoords[2]); //rg
            dist[2] = euclideanDistance(smoothedcoords[0],                  smoothedcoords[2]); //br
            for (k=0;k<cn;k++)
                bdist[k] = (dist[k]<dtrig);
            clickcond = ((((bdist[2]<<1)+bdist[1])<<1)+bdist[0]);
            };
        //printf("%d--%d-%d-%d--%03d-%03d-%03d\n",clickcond,bdist[0],bdist[1],bdist[2],dist[0],dist[1],dist[2]);
        //MOUSE EVENTS - DOING
        gotoMouse(scrctrl,smoothedcoords[3]);
        if ((workingMethod==3) || (workingMethod==4))
            {
            if (workingMethod==3)
                {
                switch(clickcond)
                    {
                    case 0: clickcode=0;
                    case 1: clickcode=1;
                    case 2: clickcode=2;
                    case 3: clickcode=0;
                    case 4: clickcode=3;
                    case 5: clickcode=0;
                    case 6: clickcode=1;
                    case 7: clickcode=1;
                    };
                }
            else if (workingMethod==4)
                {
                if ((euclideanDistance(smoothedcoords[colorBase],smoothedcoords[colorClicker])<dtrig)&&(!((bool)clickingDisabled)))
                    clickcode=1;
                else
                    clickcode=0;
                }
            else {endScreenControl(scrctrl);return 127;};
            clickCode(scrctrl,clickcode);
            };
        coordhistoryptr++;
        }
    endScreenControl(scrctrl);
    return 0;
    }
 /*
//This was necessary for testing purposes, and may be outdated now
#ifndef THIS_IS_THE_FILE_THAT_HOLDS_THE_MAIN
#define THIS_IS_THE_FILE_THAT_HOLDS_THE_MAIN
int main(int argc, char **argv)
    {
    //initialiazing mouse control
    Display *disp = NULL;
	disp = XOpenDisplay (NULL);
	Screen*  scrn = DefaultScreenOfDisplay(disp);
	int ty = scrn->height;
	int tx  = scrn->width;
	//entering loop
    theCoolPart(0,5,0,disp,tx,ty);
    //closing mouse control
    XCloseDisplay(disp);
    return 0;
    };
#endif // THIS_IS_THE_FILE_THAT_HOLDS_THE_MAIN
*/
