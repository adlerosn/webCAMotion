#ifndef CORE_H
#define CORE_H
#include <opencv2/opencv.hpp>
#include <math.h>

struct coordinate {int    x; int    y;          }; typedef struct coordinate coordinate;
struct coord3d    {double x; double y; double z;}; typedef struct coord3d    coord3d;

using namespace std;
using namespace cv;

#ifndef _MATH_H
#define _MATH_H

int pow(int a, int b)
{
    int o=1;
    int t;
    for (t=0;t<b;t++)
        o*=a;
    return o;
}

int sqrt(int i)
{
    if (i==0) return 0;
    if (i==1) return 1;
    if (i<0)  return sqrt(-i);
    int o=1;
    while (!((pow(o,2)<=i) && (pow(o+1,2)>i)))
    {
        o++;
    }
    return o;
}
#endif // _MATH_H


double deg2rad(double i)
{
    return (i*(M_PI/180.0));
}

double rad2deg(double i)
{
    return (i*(180.0/M_PI));
}

double euclideanDistance(coordinate in1, coordinate in2)
{
    double f;
    long long int dx,dy;
    double t;
    dx = ((in1.x)-(in2.x));
    dy = ((in1.y)-(in2.y));
    t = pow(dx,2) + pow(dy,2);
    f = sqrt(t);
    return f;
}

double pitagoras(double cat1, double cat2)
{
    return sqrt(pow(cat1,2)+pow(cat2,2));
}

void swapCoord(coordinate *in1, coordinate *in2)
    {
    coordinate *tmp = in1;
    in1 = in2;
    in2 = tmp;
    return;
    }

void swapInt(int *in1, int *in2)
    {
    int *tmp = in1;
    in1 = in2;
    in2 = tmp;
    return;
    }

#ifdef __unix__ //works perfectly on linux; why not in windows?
coordinate bestIlluminati(Mat inmage, int lin, int col, int layer)
{
    int x;
    int y;
    int sx=inmage.step[1];
    int sy=inmage.step[0];
    char v;
    coordinate vec1[lin*col];
    coordinate vec2[lin*col];
    uint8_t* pixelPtr;
    pixelPtr = (uint8_t*)inmage.data;
    char vec1val=0;
    char vec2val=0;
    long int vec1len=0;
    long int vec2len=0;
    for (y=0; y<lin; y++)
       {for (x=0; x<col; x++)
            {
            v=*(pixelPtr+((sx*x)+(y*sy)+(layer)));
            if (((int)vec1val)==((int)v))
                {
                vec1[vec1len].x=x;
                vec1[vec1len].y=y;
                vec1len++;
                }
            else if (((int)vec2val)==((int)v))
                {
                vec2[vec2len].x=x;
                vec2[vec2len].y=y;
                vec2len++;
                }
            else if (((int)vec1val)<((int)v))
                {
                vec2len=vec1len;
                vec2val=vec1val;
                swapCoord(vec1,vec2);
                vec1val=v;
                vec1len=0;
                vec1[vec1len].x=x;
                vec1[vec1len].y=y;
                vec1len++;
                }
            else if ((((int)vec1val)>((int)v))&&(((int)v)>((int)vec2val)))
                {
                vec2val=v;
                vec2len=0;
                vec2[vec2len].x=x;
                vec2[vec2len].y=y;
                vec2len++;
                };
            };};
    /////////////////////////////////////
    long long int sv1x=0;
    long long int sv1y=0;
    long long int sv2x=0;
    long long int sv2y=0;
    for (x=0; x<vec1len; x++)
        {
        sv1x+=vec1[x].x;
        sv1y+=vec1[x].y;
        };
    for (x=0; x<vec2len; x++)
        {
        sv2x+=vec2[x].x;
        sv2y+=vec2[x].y;
        };
    int v1x=0;
    int v1y=0;
    if (vec1len>0)
        {
        v1x=sv1x/vec1len;
        v1y=sv1y/vec1len;
        }
    else {struct coordinate retVal; retVal.x=0; retVal.y=0; return retVal;};
    int v2x=v1x;
    int v2y=v1y;
    if (vec2len>0)
        {
        v2x=sv2x/vec2len;
        v2y=sv2y/vec2len;
        };
    //////////////////////
    struct coordinate retVal;
    retVal.x=((2*v1x)+(v2x))/3;
    retVal.y=((2*v1y)+(v2y))/3;
    return retVal;
}
#endif //unix
#ifdef _WIN32
#include <malloc.h>

coordinate bestIlluminati(Mat inmage, int lin, int col, int layer)
{
    int x;
    int y;
    int sx=inmage.step[1];
    int sy=inmage.step[0];
    char v;
    long long int tmp=lin*col*2;
    int *vec1=(int*)malloc(sizeof(int)*tmp);
    int *vec2=(int*)malloc(sizeof(int)*tmp);
    uint8_t* pixelPtr;
    pixelPtr = (uint8_t*)inmage.data;
    char vec1val=0;
    char vec2val=0;
    long int vec1len=0;
    long int vec2len=0;
    for (y=0; y<lin; y++)
       {for (x=0; x<col; x++)
            {
            v=*(pixelPtr+((sx*x)+(y*sy)+(layer)));
            if (((int)vec1val)==((int)v))
                {
                vec1[0+2*vec1len]=x;
                vec1[1+2*vec1len]=y;
                vec1len++;
                }
            else if (((int)vec2val)==((int)v))
                {
                vec2[0+2*vec2len]=x;
                vec2[1+2*vec2len]=y;
                vec2len++;
                }
            else if (((int)vec1val)<((int)v))
                {
                vec2len=vec1len;
                vec2val=vec1val;
                swapInt(vec1,vec2);
                vec1val=v;
                vec1len=0;
                vec1[0+2*vec1len]=x;
                vec1[1+2*vec1len]=y;
                vec1len++;
                }
            else if ((((int)vec1val)>((int)v))&&(((int)v)>((int)vec2val)))
                {
                vec2val=v;
                vec2len=0;
                vec2[0+2*vec2len]=x;
                vec2[1+2*vec2len]=y;
                vec2len++;
                };
            };};
    /////////////////////////////////////
    long long int sv1x=0;
    long long int sv1y=0;
    long long int sv2x=0;
    long long int sv2y=0;
    for (x=0; x<vec1len; x++)
        {
        sv1x+=vec1[0+2*x];
        sv1y+=vec1[1+2*x];
        };
    for (x=0; x<vec2len; x++)
        {
        sv2x+=vec2[0+2*x];
        sv2y+=vec2[1+2*x];
        };
    free(vec1);
    free(vec2);
    int v1x=0;
    int v1y=0;
    if (vec1len>0)
        {
        v1x=sv1x/vec1len;
        v1y=sv1y/vec1len;
        }
    else {struct coordinate retVal; retVal.x=0; retVal.y=0; return retVal;};
    int v2x=v1x;
    int v2y=v1y;
    if (vec2len>0)
        {
        v2x=sv2x/vec2len;
        v2y=sv2y/vec2len;
        };
    //////////////////////
    struct coordinate retVal;
    retVal.x=((2*v1x)+(v2x))/3;
    retVal.y=((2*v1y)+(v2y))/3;
    return retVal;
}
#endif //win32

#if defined(__unix__) || defined(_WIN32)
#else
#error
#endif


void makeSelectionVisible(Mat inmage, int sel, int cn, int lins, int cols, coordinate co)
    {
    int x;
    int y;
    int sx=inmage.step[1];
    int sy=inmage.step[0];
    int k;
    uint8_t *pixelPtr;
    pixelPtr = (uint8_t*)inmage.data;
    x=co.x;
    y=co.y;
    for (y=0; y<lins; y++)
        {
        for (k=0;k<cn;k++)
            {
            if (sel==k)
                {
                *(pixelPtr+((sx*x)+(y*sy)+(k)))=255;
                }
            else
                {
                *(pixelPtr+((sx*x)+(y*sy)+(k)))=0;
                };
            };
        };
    x=co.x;
    y=co.y;
    for (x=0; x<cols; x++)
        {
        for (k=0;k<cn;k++)
            {
            if (sel==k)
                {
                *(pixelPtr+((sx*x)+(y*sy)+(k)))=255;
                }
            else
                {
                *(pixelPtr+((sx*x)+(y*sy)+(k)))=0;
                };
            };
        };
    return;
    }

coordinate smootherPoints(coordinate *coordhistory, int coordhistoryptr, int smoothNumberFrames)
    {
    int l;
    int m;
    long int sx=0;
    long int sy=0;
    coordinate crdnt;
    for (l=0;l<smoothNumberFrames;l++)
        {
        m=(coordhistoryptr+l)%smoothNumberFrames;
        sx+=coordhistory[m].x;
        sy+=coordhistory[m].y;
        };
    crdnt.x=(int)(sx/smoothNumberFrames);
    crdnt.y=(int)(sy/smoothNumberFrames);
    return crdnt;
    };

coordinate proportionWebcamToScreen(float basex, float basey, int wcrx, int wcry, int scrx, int scry, int offprop)
{
    coordinate m;
    float mx;
    float my;
    float ex;
    float ey;
    float ax;
    float ay;
    ex=(wcrx*(offprop/100.0));
    ey=(wcry*(offprop/100.0));
    ax=(wcrx-(2*ex));
    ay=(wcry-(2*ey));
    ////
    if (basex<ex)
        mx=0;
    else if (basex>(ex+ax))
        mx=scrx-1;
    else
        mx=((basex-ex)/((float)ax))*scrx;
    ////
    if (basey<ey)
        my=0;
    else if (basey>(ey+ay))
        my=scry-1;
    else
        my=((basey-ey)/((float)ay))*scry;
    ////
    m.x = mx;
    m.y = my;
    return m;
}

double cameraPX2CM(double camAngle, double distInCm, int pixAmm)
{
    return ((sin(camAngle)*distInCm)/pixAmm);
}

#include <stdio.h>

coordinate wherePointing(coordinate* coords, int wcrx, int wcry, int scrx, int scry,
                         int distanceAwayDisplay, int baseToEdgeDistance, int colorBase,
                         int colorEdge, int screensize)
{
    //printf("%d,%d\n",colorBase,colorEdge);
    double camAngle = deg2rad(60)/2; //read as FOV
    coord3d base;
    coord3d edge;
    double p2c=cameraPX2CM(camAngle,distanceAwayDisplay,scrx/4);
    double distanceBaseEdge=euclideanDistance(coords[colorBase],coords[colorEdge])*p2c;
    if (distanceBaseEdge>baseToEdgeDistance)
        distanceBaseEdge=baseToEdgeDistance;
    double zangle=acos(distanceBaseEdge/baseToEdgeDistance);
    //printf("%f\n",cameraPX2CM(camAngle,distanceAwayDisplay,wcrx/2));
    //
    base.z=distanceAwayDisplay;
    base.x=(distanceAwayDisplay*((sin(camAngle)*(coords[colorBase].x/((double)wcrx)))-0.5));
    base.y=(distanceAwayDisplay*((sin(camAngle)*(coords[colorBase].y/((double)wcry)))-0.5));
    //printf("%05.1f -- %05.1f -- %05.1f\n",base.x,base.y,base.z);
    //
    double angle = atan2(coords[colorBase].y-coords[colorEdge].y, coords[colorBase].x-coords[colorEdge].x);
    //printf("% 6.1f\n",rad2deg(angle));
    //
    edge.x=base.x+(distanceBaseEdge*cos(angle));
    edge.y=base.y+(distanceBaseEdge*sin(angle));
    edge.z=distanceAwayDisplay-(baseToEdgeDistance*cos(zangle));
    //printf("%05.1f -- %05.1f\n",zangle,cos(zangle));
    //printf("%05.1f -- %05.1f -- %05.1f\n",edge.x,edge.y,edge.z);
    //
    coord3d delta;
    delta.x=base.x-edge.x;
    delta.y=base.y-edge.y;
    delta.z=base.z-edge.z;
    if (delta.z==0)
        delta.z=0.002;
    //printf("%05.1f -- %05.1f -- %05.1f\n",delta.x,delta.y,delta.z);
    //
    double px,py;
    int dx,dy;
    dx=scrx/2;
    dy=scry/2;
    px=((((distanceAwayDisplay*cos(zangle))/delta.z)*delta.x)/p2c);
    py=((((distanceAwayDisplay*cos(zangle))/delta.z)*delta.y)/p2c);
    px*=sqrt(screensize);
    py*=sqrt(screensize);
    px+=dx;
    py+=dy;
    //printf("%d\n",screensize);
    /*
    px+=wcrx/2;
    py+=wcry/2;*/
    //(screensize*2.54)
    /*
     * Here the projections PX and PY are scaled as*/
    //printf("%05.1f -- %05.1f\n",px,py);
    coordinate ret;
    ret=proportionWebcamToScreen(px,py,scrx,scry,scrx,scry,0);
    return ret;
}

using namespace std;
using namespace cv;

void clickedInImage(int event, int x, int y, int flags, void* userdata){
if(event == EVENT_LBUTTONDOWN || event == EVENT_RBUTTONDOWN || event == EVENT_MBUTTONDOWN) GVAR1=1;
else GVAR1=0;
}

using namespace std;

#endif // CORE_H
