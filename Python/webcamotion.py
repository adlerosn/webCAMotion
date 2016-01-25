#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Fri Feb 13 17:49:50 2015

    LICENSE

    A general purpose mouse simulator via webcam.
    Copyright (C) 2015  Ádler Oliveira Silva Neves

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

@filecreator: Ádler O. S. Neves
@authorslist: Ádler O. S. Neves
@authorslist: <Next one>
"""

def finish():
    print('The program finished. Press ENTER to continue...')
    raw_input()
    quit()

print('''This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.\n
This program may use of many external libraries, so the license above is
contemplating NO libraries used and refers just to the code of the program;
then by using the program by running as script or bytecode you agree with all
licenses of all libraries this program uses. Have fun!\n''')

#
#==============================================================================
# # INICIO DA GAMBIARRA
# # (e não tem fim)
#==============================================================================
#

dependencias=["python-dev",
              "python-scipy",
              "python-numpy",
              "python-tk",
              "python-imaging",
              "python-pil",
              "python-pil.imagetk",
              "python-xlib",
              "python-opencv"]

print("########################################")
print("########################################")
print("              webCAMotion     - alpha 5!")
print("     A buggy alpha by Adler Neves       ")
print("                       Also for Windows!")
print("########################################")
print("########################################")
print("")
print("In Ubuntu, this program needs:")
for d in dependencias:
    print(' >'+d)
print("")

#==============================================================================
# 
#==============================================================================

importError=False
numpyImported=False
#BUILT-IN
from collections import deque
from sys import argv as argv
from sys import platform as OSname
import time

#EXTERNAL
try:
    import cv2
except:
    print('Error while importing OPENCV')
    importError=True
#
try:
    from PIL import Image
except:
    print('Error while importing IMAGE from PIL')
    importError=True
#
try:
    from PIL import ImageTk
except:
    print('Error while importing IMAGETK from PIL')
    importError=True
#
try:
    import Tkinter as tk
except:
    print('Error while importing TKINTER')
    importError=True
#
try:
    import numpy
    numpyImported=True
except:
    print('Error while importing NUMPY')
    importError=True
#
try:
    from scipy.stats import mode
except:
    print('Error while importing MODE from SCIPY')
    if numpyImported:
        try:
            print("No problem with SCIPY! Rewriting some slower code with numpy...")
            def mode(L):
                c1=L[0]
                c2=1
                S=set(L)
                for s in S:
                    c=L.count(s)
                    if c>c2:
                        c1=s
                        c2=c
                return [[c1]]
        except:
            importError=True
    else:
        importError=True
#
try:
    from scipy.spatial.distance import euclidean
except:
    print('Error while importing EUCLIDEAN DISTANCE from SCIPY')
    if numpyImported:
        try:
            print("No problem with SCIPY! Rewriting some slower code with numpy...")
            def euclidean(A,B):
                a=numpy.array(A)
                b=numpy.array(B)
                dist = numpy.linalg.norm(a-b)
                return dist
        except:
            importError=True
    else:
        importError=True
#
#
if importError:
    finish()

#==============================================================================
# 
#==============================================================================


dontRun=False

if OSname == 'win32':
    import win32api
    screenres=(win32api.GetSystemMetrics(0),win32api.GetSystemMetrics(1))
elif OSname == 'linux2' or OSname == 'linux3':
    from Xlib import X, display
    from Xlib.ext.xtest import fake_input
    d = display.Display()
    s = d.screen()
    root=s.root
    root=root.get_geometry()
    screenres=(root.width,root.height)
    mouse = s.root
    mouse.warp_pointer(screenres[0]//2,screenres[1]//2)
    d.sync()
else:
    print('This OS ('+OSname+') is not supported.')
    finish()


failcount=0
cam=0 #will receive the camera controller

lmx=[]
lmy=[]
lrx=[]
lgx=[]
lbx=[]
lry=[]
lgy=[]
lby=[]
lact=[]
pagb=0
parg=0
pabr=0

pyversion=''
#pyversion='3'
usagetxt='\n\nUsage:\n--> python'+pyversion+' '+argv[0]+'\n--> python'+pyversion+' '+argv[0]+' noclick <cor a ser rastreada (r,g,b)> <tamanho do buffer>'

isClickingEnabled=True
moveTrackColor='g'

bufferFramesC=1

camIden=0

image_label=0
r_label=0
g_label=0
b_label=0
bg_label=0
br_label=0
rg_label=0
act_label=0
fps_label=0
webcamres=0
rootk=0

#==============================================================================
# 
#==============================================================================

def openCam(camIden=0):
    camLink = cv2.VideoCapture(camIden)
    webcamresol=getCamRes(camLink)
    return (camLink,webcamresol)

def getCamRes(cameraLink):
    global failcount
    readedimg=False
    failcount=-1
    while not readedimg:
        (readedimg, image) = cameraLink.read()
        failcount+=1
        if failcount<60:
            pass
        else:
            print('ERROR: WEBCAM DIDNT SEND A IMAGE 60 TIMES IN A ROW. Aborting program.')
            finish()
    tmp=numpy.shape(image)
    wc=(tmp[1],tmp[0])
    return wc

def putLabels(tke):
    global image_label
    global r_label
    global g_label
    global b_label
    global bg_label
    global br_label
    global rg_label
    global act_label
    global fps_label
    #
    image_label = tk.Label(master=tke)
    image_label.pack()
    c_label = tk.Label(master=tke)
    c_label.configure(text='RGB')
    c_label.pack()
    r_label = tk.Label(master=tke)
    r_label.configure(text='R= 0000 x 0000')
    r_label.pack()
    g_label = tk.Label(master=tke)
    g_label.configure(text='G= 0000 x 0000')
    g_label.pack()
    b_label = tk.Label(master=tke)
    b_label.configure(text='B= 0000 x 0000')
    b_label.pack()
    bg_label = tk.Label(master=tke)
    bg_label.configure(text='RG= 000')
    bg_label.pack()
    br_label = tk.Label(master=tke)
    br_label.configure(text='BR= 000')
    br_label.pack()
    rg_label = tk.Label(master=tke)
    rg_label.configure(text='RG= 000')
    rg_label.pack()
    act_label = tk.Label(master=tke)
    act_label.configure(text='Action = ---')
    act_label.pack()
    fps_label = tk.Label(master=tke)
    fps_label._frame_times = deque([0]*5)  # arbitrary 5 frame average FPS
    fps_label.pack()

def isnumeric(s):
    try:
        s=int(s)
        return True
    except:
        return False

def criaMedia(frames=bufferFramesC):
    global lmx
    global lmy
    global lrx
    global lgx
    global lbx
    global lry
    global lgy
    global lby
    global pagb
    global parb
    global parg
    #    
    lmx=[(screenres[0]//2) for x in range(frames)]
    lmy=[(screenres[1]//2) for y in range(frames)]
    lrx=[(webcamres[0]//2) for x in range(frames)]
    lgx=[(webcamres[0]//2) for x in range(frames)]
    lbx=[(webcamres[0]//2) for x in range(frames)]
    lry=[(webcamres[1]//2) for y in range(frames)]
    lgy=[(webcamres[1]//2) for y in range(frames)]
    lby=[(webcamres[1]//2) for y in range(frames)]
    criaMediaAcoes(frames)

def criaMediaAcoes(f=bufferFramesC):
    global lact
    lact=[0 for k in range(f)]

def calculaMedia(mx,my,rx,ry,gx,gy,bx,by):
    global lmx
    global lmy
    global lrx
    global lgx
    global lbx
    global lry
    global lgy
    global lby
    #
    lmx.append(mx)
    lmy.append(my)
    lrx.append(rx)
    lgx.append(gx)
    lbx.append(bx)
    lry.append(ry)
    lgy.append(gy)
    lby.append(by)
    #
    mmx=sum(lmx)//len(lmx)
    mmy=sum(lmy)//len(lmy)
    mrx=sum(lrx)//len(lrx)
    mgx=sum(lgx)//len(lgx)
    mbx=sum(lbx)//len(lbx)
    mry=sum(lry)//len(lry)
    mgy=sum(lgy)//len(lgy)
    mby=sum(lby)//len(lby)
    #
    del(lmx[0])
    del(lmy[0])
    del(lrx[0])
    del(lgx[0])
    del(lbx[0])
    del(lry[0])
    del(lgy[0])
    del(lby[0])
    #
    return (mmx, mmy, mrx, mgx, mbx, mry, mgy, mby)
    
def wheresMyMouse(wpx,wpy,bordas=0.2):
    if wpx<(bordas*webcamres[0]):
        mx=0
    elif wpx>((1-bordas)*webcamres[0]):
        mx=screenres[0]
    else:
        mx=int(((wpx-bordas*webcamres[0]))*(screenres[0]/(webcamres[0]*(1-(2*bordas)))))
    if wpy<(bordas*webcamres[1]):
        my=0
    elif wpy>((1-bordas)*webcamres[1]):
        my=screenres[1]
    else:
        my=int((wpy-(bordas*webcamres[1]))*(screenres[1]/(webcamres[1]*(1-(2*bordas)))))
    return (mx,my)


if OSname == 'win32':
    import win32con
    def sclick(): #Simple CLICK
        win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,0,0)
#        win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,0,0)
#        win32api.mouse_event(win32con.MOUSEEVENTF_MIDDLEDOWN,0,0)
        win32api.mouse_event(win32con.MOUSEEVENTF_MIDDLEUP,0,0)
#        win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTDOWN,0,0)
        win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTUP,0,0)
 
    def wclick(): #Wrong CLICK
#        win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,0,0)
        win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,0,0)
#        win32api.mouse_event(win32con.MOUSEEVENTF_MIDDLEDOWN,0,0)
        win32api.mouse_event(win32con.MOUSEEVENTF_MIDDLEUP,0,0)
        win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTDOWN,0,0)
#        win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTUP,0,0)
    
    def mclick(): #Middle CLICK
#        win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,0,0)
        win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,0,0)
        win32api.mouse_event(win32con.MOUSEEVENTF_MIDDLEDOWN,0,0)
#        win32api.mouse_event(win32con.MOUSEEVENTF_MIDDLEUP,0,0)
#        win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTDOWN,0,0)
        win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTUP,0,0)
    
    def uclick(): # UNCLICK
#        win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,0,0)
        win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,0,0)
#        win32api.mouse_event(win32con.MOUSEEVENTF_MIDDLEDOWN,0,0)
        win32api.mouse_event(win32con.MOUSEEVENTF_MIDDLEUP,0,0)
#        win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTDOWN,0,0)
        win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTUP,0,0)

    def mouseMove(mousexto,mouseyto):
        win32api.SetCursorPos((mousexto,mouseyto))
#        win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,0,0)
#        win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,0,0)
#        win32api.mouse_event(win32con.MOUSEEVENTF_MIDDLEDOWN,0,0)
#        win32api.mouse_event(win32con.MOUSEEVENTF_MIDDLEUP,0,0)
#        win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTDOWN,0,0)
#        win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTUP,0,0)
        
elif OSname == 'linux2' or OSname == 'linux3':
    def sclick(): #Simple CLICK
        fake_input(d, X.ButtonRelease, 2)
        fake_input(d, X.ButtonRelease, 3)
        fake_input(d, X.ButtonPress, 1)
        d.sync()
 
    def wclick(): #Wrong CLICK
        fake_input(d, X.ButtonRelease, 1)
        fake_input(d, X.ButtonRelease, 3)
        fake_input(d, X.ButtonPress, 2)
        d.sync()
    
    def mclick(): #Middle CLICK
        fake_input(d, X.ButtonRelease, 1)
        fake_input(d, X.ButtonRelease, 2)
        fake_input(d, X.ButtonPress, 3)
        d.sync()
    
    def uclick(): # UNCLICK
        fake_input(d, X.ButtonRelease, 1)
        fake_input(d, X.ButtonRelease, 2)
        fake_input(d, X.ButtonRelease, 3)
        d.sync()
        
    def mouseMove(mousexto,mouseyto):
        mouse.warp_pointer(mousexto,mouseyto)
        d.sync()

def quit_(rootk):
    #cam.release()
    mouse.warp_pointer(screenres[0]//2,screenres[1]//2)
    d.sync()
    rootk.destroy()

def quebraRGB(image):
    red = image[:,:,0]
    green = image[:,:,1]
    blue = image[:,:,2]
    return red, green, blue

def mediaAcoes(res,limiar=0.3):
    global lact
    lact+=[res]
    frq=0
    ss=mode(lact)
    frq=int(ss[0][0])
    del(lact[0])
    return frq
    
def clicker(code): #not from "The Last of Us"
#    Move cursor - 0
#    Usual click - 1
#    Menu click - 2
#    Move cursor - 3
#    Wheel click - 4
#    Move cursor - 5
#    Grab - 6
#    Grab - 7
    clickN=[0,3,5]
    click1=[1,6,7]
    click2=[2]
    click3=[4]
    if code in clickN:
        uclick()
    elif code in click1:
        sclick()
    elif code in click2:
        mclick()
    elif code in click3:
        wclick()
    else:
        print("!!! PROGRAM WRONGLY MODDED !!!")
        finish()
    
def update_image(image_label, cam):
    (readsuccessful, f) = cam.read()
    global failcount
    if not readsuccessful:
        failcount+=1
        if failcount<60:
            pass
        else:
            print('ERROR: WEBCAM DIDNT SEND A IMAGE 60 TIMES IN A ROW. Aborting program.')
            quit_(rootk)
    else:
        failcount=0
        #
        col_im = cv2.cvtColor(f, cv2.COLOR_BGR2RGB)
        col_im = numpy.fliplr(col_im)
        #
        col_im = cv2.resize(col_im, (0,0), fx=1, fy=1)
        #
        rgbchannels=quebraRGB(col_im)
        #
        gray_im = cv2.cvtColor(col_im, cv2.COLOR_RGB2GRAY)
        #
        gray_imr = cv2.subtract(rgbchannels[0], gray_im)
        gray_img = cv2.subtract(rgbchannels[1], gray_im)
        gray_imb = cv2.subtract(rgbchannels[2], gray_im)
        #
        gray_imr = (gray_imr//(numpy.amax(gray_imr)))*255
        gray_img = (gray_img//(numpy.amax(gray_img)))*255
        gray_imb = (gray_imb//(numpy.amax(gray_imb)))*255
        #
        # Calculando a posição dos pontos do frame atual
        #
        rpos=(0,0)
        gpos=(0,0)
        bpos=(0,0)
        if numpy.count_nonzero(gray_imr)>0:
            rpos=gray_imr.nonzero()
            rpos=((numpy.amax(rpos[0])+numpy.amin(rpos[0]))//2,
                  (numpy.amax(rpos[1])+numpy.amin(rpos[1]))//2)
        if numpy.count_nonzero(gray_img)>0:
            gpos=gray_img.nonzero()
            gpos=((numpy.amax(gpos[0])+numpy.amin(gpos[0]))//2,
                  (numpy.amax(gpos[1])+numpy.amin(gpos[1]))//2)
        if numpy.count_nonzero(gray_imb)>0:
            bpos=gray_imb.nonzero()
            bpos=((numpy.amax(bpos[0])+numpy.amin(bpos[0]))//2,
                  (numpy.amax(bpos[1])+numpy.amin(bpos[1]))//2)
        #
        # Pegando a média dos últimos frames
        #
        if moveTrackColor=='r':
            mpos=rpos
        elif moveTrackColor=='g':
            mpos=gpos
        elif moveTrackColor=='b':
            mpos=bpos
        else:
            mpos=gpos #the default
        (mx,my)=wheresMyMouse(mpos[1],mpos[0])
        (mmx, mmy,
         mrx, mgx,
         mbx, mry,
         mgy, mby)=calculaMedia(mx,     my,
                                rpos[1],rpos[0],
                                gpos[1],gpos[0],
                                bpos[1],bpos[0])
        #
        #################################
        #
        if (not isClickingEnabled) and (moveTrackColor!="r"):
            pass
        else:
            col_im[:,rpos[1],0]=255 #R#
            col_im[:,rpos[1],1]=0   #G
            col_im[:,rpos[1],2]=0   #B
            col_im[rpos[0],:,0]=255 #R#
            col_im[rpos[0],:,1]=0   #G
            col_im[rpos[0],:,2]=0   #B
        #
        if (not isClickingEnabled) and (moveTrackColor!="g"):
            pass
        else:
            col_im[:,gpos[1],0]=0   #R
            col_im[:,gpos[1],1]=255 #G#
            col_im[:,gpos[1],2]=0   #B
            col_im[gpos[0],:,0]=0   #R
            col_im[gpos[0],:,1]=255 #G#
            col_im[gpos[0],:,2]=0   #B
        #
        if (not isClickingEnabled) and (moveTrackColor!="b"):
            pass
        else:
            col_im[:,bpos[1],0]=0   #R
            col_im[:,bpos[1],1]=0   #G
            col_im[:,bpos[1],2]=255 #B#
            col_im[bpos[0],:,0]=0   #R
            col_im[bpos[0],:,1]=0   #G
            col_im[bpos[0],:,2]=255 #B#
        #
        #################################
        #
        a = Image.fromarray(col_im)
        b = ImageTk.PhotoImage(image=a)
        image_label.configure(image=b)
        image_label._image_cache = b  
        #
        #################################
        #
        r_label.configure(text='R= %04d x %04d ==> %04d x %04d'%(rpos[0],rpos[1],mrx,mry))
        g_label.configure(text='G= %04d x %04d ==> %04d x %04d'%(gpos[0],gpos[1],mgx,mgy))
        b_label.configure(text='B= %04d x %04d ==> %04d x %04d'%(bpos[0],bpos[1],mbx,mby))
        #
        bg=int(euclidean(bpos,gpos))
        rg=int(euclidean(rpos,gpos))
        br=int(euclidean(bpos,rpos))
        bgs=int(bg<40)
        rgs=int(rg<40)
        brs=int(br<40)
        #
        mbg=int(euclidean((mbx,mby),(mgx,mgy)))
        mrg=int(euclidean((mrx,mry),(mgx,mgy)))
        mbr=int(euclidean((mbx,mby),(mrx,mry)))
        mbgs=int(mbg<40)
        mrgs=int(mrg<40)
        mbrs=int(mbr<40)
        #
        bg_label.configure(text='BG = (%03d --> %01d) ==> (%03d --> %01d)'%(bg,bgs,mbg,mbgs))
        rg_label.configure(text='RG = (%03d --> %01d) ==> (%03d --> %01d)'%(rg,rgs,mrg,mrgs))
        br_label.configure(text='BR = (%03d --> %01d) ==> (%03d --> %01d)'%(br,brs,mbr,mbrs))
        #
        #################################
        #
        mouseMove(mmx,mmy)
        #
        actions=['Move cursor - 0',
                 'Usual click - 1',
                 'Menu click - 2',
                 'Move cursor - 3',
                 'Wheel click - 4',
                 'Move cursor - 5',
                 'Grab - 6',
                 'Grab - 7']
        (pact)=mediaAcoes((1*mbgs)+(2*mrgs)+(4*mbrs))
        if isClickingEnabled:
            act_label.configure(text='Action detected = %s ==> %s ==> %s'%(
                                actions[(1*bgs)+(2*rgs)+(4*brs)],
                                actions[(1*mbgs)+(2*mrgs)+(4*mbrs)],
                                actions[pact]))
            clicker(pact)
        else:
            act_label.configure(text='Action detected = DISABLED')
        #
        rootk.update()

def update_fps(fps_label):
    frame_times = fps_label._frame_times
    frame_times.rotate()
    frame_times[0] = time.time()
    sum_of_deltas = frame_times[0] - frame_times[-1]
    count_of_deltas = len(frame_times) - 1
    try:
        fps = int(float(count_of_deltas) / sum_of_deltas)
    except ZeroDivisionError:
        fps = 0
    fps_label.configure(text='FPS: {}'.format(fps))


def update_all(rootk, image_label, cam, fps_label):
    update_image(image_label, cam)
    update_fps(fps_label)
    rootk.after(0, func=lambda: update_all(rootk, image_label, cam, fps_label))

#==============================================================================
# 
#==============================================================================


class firstscr(tk.Tk):
    def __init__(self,parent):
        tk.Tk.__init__(self,parent)
        self.parent = parent
        self.initialize()
    
    def initialize(self):
        self.grid()

        try:
            cc = tk.PhotoImage(file='normalglovebgr.gif')
        except:
            cc = tk.PhotoImage(data=gloveImageInBase64)
        self.cc = tk.Button(self, image=cc,command=self.glp)
        self.img=cc
        self.cc.grid(row = 1, column = 0, sticky='E')
        
        self.r = tk.Button(self,text="No click\nRED",command=self.rc,bg="red",fg="white")
        self.r.grid(column=1,row=1,sticky='')    
        self.g = tk.Button(self,text="No click\nGREEN",command=self.gc,bg="green",fg="white")
        self.g.grid(column=2,row=1,sticky='')    
        self.b = tk.Button(self,text="No click\nBLUE",command=self.bc,bg="blue",fg="white")
        self.b.grid(column=3,row=1,sticky='')    
        
        self.button = tk.Button(self,text="Close",command=self.destroy)
        self.button.grid(column=3,row=6,sticky='EW')  
        
        self.labelVariable = tk.StringVar()
        self.label = tk.Label(self,textvariable=self.labelVariable,anchor="sw")
        self.label.grid(column=0,row=6,columnspan=3,sticky='EW')
        self.labelVariable.set("""This program is under GNU LGPL v3.""")
        
        self.label2Variable = tk.StringVar()
        self.label2 = tk.Label(self,textvariable=self.label2Variable,
                              anchor="n",fg="white",bg="green")
        self.label2.grid(column=0,row=0,columnspan=4,sticky='EW')
        self.label2Variable.set("Select working method")

        self.label3Variable = tk.StringVar()
        self.label3 = tk.Label(self,textvariable=self.label3Variable,anchor="sw")
        self.label3.grid(column=0,row=4,sticky='EW')
        self.label3Variable.set("""Webcam identifier""")
        
        self.wmb = tk.Button(self,text="-",command=self.webcamMinusB)
        self.wmb.grid(column=1,row=4,sticky='e')    
        self.wpb = tk.Button(self,text="+",command=self.webcamPlusB)
        self.wpb.grid(column=2,row=4,sticky='w')     
        
        self.mmb = tk.Button(self,text="-",command=self.delayMinusB)
        self.mmb.grid(column=1,row=5,sticky='e')    
        self.mpb = tk.Button(self,text="+",command=self.delayPlusB)
        self.mpb.grid(column=2,row=5,sticky='w') 
        
        self.label4Variable = tk.StringVar()
        self.label4 = tk.Label(self,textvariable=self.label4Variable,anchor="sw")
        self.label4.grid(column=0,row=5,sticky='EW')
        self.label4Variable.set("""Mouse delay""")

        global camIden
        self.label5Variable = tk.StringVar()
        self.label5 = tk.Label(self,textvariable=self.label5Variable,anchor="sw")
        self.label5.grid(column=3,row=4,sticky='EW')
        self.label5Variable.set(str(camIden))
        
        global bufferFramesC
        self.label6Variable = tk.StringVar()
        self.label6 = tk.Label(self,textvariable=self.label6Variable,anchor="sw")
        self.label6.grid(column=3,row=5,sticky='EW')
        self.label6Variable.set(str(bufferFramesC))

        self.resizable(False,False)
        self.update()
        
    def webcamPlusB(self):
        global camIden
        camIden+=1
        self.label5Variable.set(str(camIden))
        self.update()
    def webcamMinusB(self):
        global camIden
        if camIden>0:
            camIden-=1
            self.label5Variable.set(str(camIden))
        self.update()
    def delayPlusB(self):
        global bufferFramesC
        bufferFramesC+=1
        self.label6Variable.set(str(bufferFramesC))
        self.update()
    def delayMinusB(self):
        global bufferFramesC
        if bufferFramesC>0:
            bufferFramesC-=1
            self.label6Variable.set(str(bufferFramesC))
        self.update()
    def readLabels(self):
        #just go to the main program
        self.destroy()
    def rc(self):
        global isClickingEnabled
        global moveTrackColor
        global fscreenSel
        fscreenSel=True
        isClickingEnabled=False
        moveTrackColor='r'
        self.readLabels()
    def gc(self):
        global isClickingEnabled
        global moveTrackColor
        global fscreenSel
        fscreenSel=True
        isClickingEnabled=False
        moveTrackColor='g'
        self.readLabels()
    def bc(self):
        global isClickingEnabled
        global moveTrackColor
        global fscreenSel
        fscreenSel=True
        isClickingEnabled=False
        moveTrackColor='b'
        self.readLabels()
    def glp(self):
        global isClickingEnabled
        global moveTrackColor
        global fscreenSel
        fscreenSel=True
        isClickingEnabled=True
        moveTrackColor='g'
        self.readLabels()
        

#==============================================================================
# 
#==============================================================================
fscreenSel=False

def choserFScreen():
    global fscreenSel
    fs = firstscr(None)
    fs.title('webCAMotion')
    fs.mainloop()
    if fscreenSel:
        main()

def main():
    global webcamres
    global rootk
    global bufferFramesC
    (cam,webcamres)=openCam(camIden)
    criaMedia(bufferFramesC)
    rootk = tk.Tk()
    putLabels(rootk)
    quit_button = tk.Button(master=rootk, text='Quit', command=lambda: quit_(rootk))
    quit_button.pack()
    rootk.after(0, func=lambda: update_all(rootk, image_label, cam, fps_label))
    rootk.mainloop()

gloveImageInBase64="""R0lGODlhKgAqAMZMAAwA9BYA/x4fHSEiNBUYvyMkIiQlIxwW0CUnJCYoJScoJigpJykrKC4qKSosKSstKhY1GSorSCwuKy4vLVskIi8xLjIzMTM0MjU2NP8AADY4NTg5N+MQCTw9OyRIJEVHRE5PTVBST1JTUVVXVGhqZ2ltcGxua29xbnN1cnd5dnp7eXx+eyyoKIiKh42PjBTCEjTCN5mbmGW5Z6KkoSHaFADoAKaopVrJWADtAqmrqLS2s7e5tgz/ALm7uLu9ur2/vMDCv8TGw8nLx9DSz9PV0trc2d7g3eHj4OPl4u7w7fb49Pj69////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////yH+EUNyZWF0ZWQgd2l0aCBHSU1QACH5BAEKAH8ALAAAAAAqACoAAAf+gH+Cg4SFhoeIiYqLjI2Oj5CLApMCkZaCAhmalYOUl5KaGZx/AktLo5+GmaGcpaaoqZ2mm7KnsaorpktDrbqtt5i6tqS+mEqTkrCErqYLlcy9xYgCAQDKpB/Cz9rEuseJ1AEBsJXCBpPcAjHc4OLiqAJIukQCFdCkM+zgBOIHowIveNAwRYrZKQE6hCW4VugeKQ88IvJggc6XgCDCTDBsqK2SRIlKOg4RBuSXIoOTPkaUIcyHACDCbE1KgmyaNpU8cMQUoGJnQWmHDOLkEbOoTB/6VAnDaTQmgopAgwq78bGpsA0CEAg7srGWqRo8YFjVdUKADWEtunody/agI4NRbZuq5RjX6lxCGODWjdpI795hkPzWFWAhkuC4AlxcOjxWgI9UjI0KcHArsk9gll8Bw2Sk7d1HjNNublhE7mhVI4p+/jQpR9LTDSmthk27dqFAADs="""

if __name__ == '__main__':
    if len(argv)==1:
        pass
    elif len(argv)==4:
        if (argv[1]=='noclick') and (argv[2] in ['r','g','b']):
            isClickingEnabled=False
            moveTrackColor=argv[2]
            if isnumeric(argv[3]):
                bufferFramesC=int(argv[3])
            else:
                dontRun=True
        else:
            dontRun=True
    else:
        dontRun=True
    if not dontRun:
        if len(argv)==1:
            choserFScreen()
        else:
            main()
    else:
        print(usagetxt)

