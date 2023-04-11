'''
Created on 15 Dec 2022

@author: wvx67826
'''
from src.Control.Lakeshore.Lakeshore import Lakeshore336
from src.dataCollection.DataCollection import DataCollection
import threading
from time import sleep

def setTAndWait(lakeshore_controler, targetT, waitTime, waitAfterStable, dt):
    lakeshore_controler.ls336.setTemp(1, targetT)
    counter = waitAfterStable
    oldT = float(dc.ls336.getTemp("c"))
    timeOut = 0
    while(counter > 0 and timeOut<3600):                  
        if oldT>460:
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



dc = DataCollection()
dc.connect("172.23.110.186", 7777)
#filename = "..\\data\\EM_LS336_during experiment.dat"
filename = "..\\data\\EM_LS336_pid_autoPID_FullRangeExperiment.dat"



t1 = threading.Thread(target=dc.startCollection, args=(filename, -0.1, 20, 2,True))
t1.start()

tStep = [5,10,20,30,40,50,100]
watitTime = 5
waitAStable = 12
dt = 0.1
for tStepSize in tStep:
    for setT in range(100,401, tStepSize):
        setTAndWait(dc, setT, watitTime, waitAStable, dt)
    for setT in range(400,99, -1*tStepSize):
        setTAndWait(dc, setT, watitTime, waitAStable, dt) 
        
    
dc.clearCollectionFlag()
t1.join()


dc.disconnet()
