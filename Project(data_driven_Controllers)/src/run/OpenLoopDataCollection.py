'''
Created on 23 Nov 2022

@author: wvx67826

@deprecated: 
   keep collecting data until the program is stopped

'''

from src.dataCollection.DataCollection import DataCollection
import threading
from time import time,sleep
dc = DataCollection()
dc.connect("172.23.110.186", 7777)
ls340 = DataCollection()
ls340.connect("172.23.110.186", 7777)
def setHeatAndWait(lakeshore_controler, targetT, waitTime, waitAfterStable, dt):
    lakeshore_controler.ls336.setHeater(1, targetT)
    sleep(2)
    counter = waitAfterStable
    oldT = float(dc.ls336.getTemp("c"))
    timeOut = 0
    while(counter > 0 and timeOut<600):                  
        if oldT>450:
            lakeshore_controler.ls336.setHeater(1, 0)
            counter = -1
            break
        sleep(waitTime)
        newTemp = float(dc.ls336.getTemp("c"))
        if abs(float (oldT- newTemp))<dt:
            oldT = (oldT+newTemp)/2.0
            counter-=1
        else:
            counter = waitAfterStable
            oldT = float(dc.ls336.getTemp("c"))
        timeOut += waitTime
    print(counter)
#heater power step
arrayheaterStepsize = [-20]
loop = 1 #number of repeat
numWait = 20 #number of extra data set after temperature is stable
dWaitT = 5
dT = 0.1
for i in range(loop):  
    for heaterStepsize in arrayheaterStepsize:
        
        filename = "..\\data\\EM_LS336_CoolOpenloop_heaterStep=%i_loop=%i_shotTimeout_300s.dat" %(heaterStepsize, loop)
    
        t1 = threading.Thread(target=dc.startCollection, args=(filename, 0, 10, 1, True))
        t1.start()
        #start with 0 heater power
        #setHeatAndWait(ls340, 100, dWaitT, numWait, dT)
        #run power step up
        for targetT in range(80, -1, heaterStepsize):
            setHeatAndWait(ls340, targetT, dWaitT, numWait, dT)
       
        """
        #run power step down
        for targetT in range(90,19,-1*heaterStepsize):
            setHeatAndWait(ls340, targetT, dWaitT, numWait, dT)
            
        #end with 0 heater
        setHeatAndWait(ls340, 20, dWaitT, numWait, dT)
    
        """    #stop dataCikkectuib
        dc.clearCollectionFlag()
        t1.join()
dc.disconnet()
