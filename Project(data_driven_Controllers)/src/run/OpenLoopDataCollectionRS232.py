'''
Created on 23 Nov 2022

@author: wvx67826

@deprecated: 
   keep collecting data until the program is stopped

'''

from src.dataCollection.DataCollection import DataCollectionLs340
import threading
from time import time,sleep
dc = DataCollectionLs340()
def setHeatAndWait(lakeshore_controler, targetT, waitTime, waitAfterStable, dt):
    lakeshore_controler.ls336.setHeater(targetT)
    sleep(2)
    counter = waitAfterStable
    oldT = float(lakeshore_controler.ls336.getTemp())
    while(counter > 0):                  
        if oldT>450:
            lakeshore_controler.ls336.setHeater(0)
            break
        sleep(waitTime)
        newTemp = float(lakeshore_controler.ls336.getTemp())
        if abs(float (oldT- newTemp))<dt:
            oldT = (oldT+newTemp)/2.0
            counter-=1
        else:
            counter = waitAfterStable
            oldT = float(lakeshore_controler.ls336.getTemp())


#heater power step
arrayheaterStepsize = [10,30,45,75,90]
loop = 1 #number of repeat
numWait = 5 #number of extra data set after temperature is stable
dWaitT = 2
dT = 0.05
for i in range(loop):  
    for heaterStepsize in arrayheaterStepsize:
        
        filename = "..\\data\\EM_LS340_Openloop_heaterStep=%i_loop=%i.dat" %(heaterStepsize, loop)
    
        t1 = threading.Thread(target=dc.startCollection, args=(filename, 0, 10, 5, True))
        t1.start()
        #start with 0 heater power
        setHeatAndWait(dc, 0, dWaitT, numWait, 0.1)
        #run power step up
        for targetT in range(0,101,heaterStepsize):
            setHeatAndWait(dc, targetT, dWaitT, numWait, 0.1)
        #run power step down
        for targetT in range(90,-1,-1*heaterStepsize):
            setHeatAndWait(dc, targetT, dWaitT, numWait, 0.1)
        #end with 0 heater
        setHeatAndWait(dc, 0, dWaitT, numWait, 0.05)
    
        #stop dataCikkectuib
        dc.clearCollectionFlag()
        t1.join()

