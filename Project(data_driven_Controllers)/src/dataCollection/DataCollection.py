'''
Created on 22 Nov 2022

@author: Relm Arrowny

@deprecated: 
    Python to write data to file continuously until collection flag is flip

@version: 1.0 
'''
from src.Control.Lakeshore.Lakeshore import Lakeshore336, Lakeshore340
from time import time,sleep

class DataCollection():
    #create lakeshore object and set collection flag
       
    def __init__(self):
        self.ls336 = Lakeshore336()
        self.collectionFlag = False
    #connect to lakeshore
    def connect(self,ip,port):
        self.ls336.connection(ip, port)
    #close off connection
    def disconnet(self):
        self.ls336.closeConnection()
        
    #start collecting data with fixed format in ascii
    #function take 5 parameters
    #Filename
    #dT : different in setpoint and temperature that will trigger data collection
    #      set this to 0 for continuous measurement
    #poinsAfaterStable : number of extra points to collect after temperature is stable
    #waitT: time wait between each data read
    #newFile: if set to True a new file will be created otherwise data will be appended to the file.    
    def startCollection(self,filename, dT = 0.1, pointsAfterStable = 20, waitT = 2, newFile = True):
        #if new file write new header
        if newFile:
            f = open(filename, 'w')
            dataheader = "Time(s),SetTemp(K),Temp(K),HeatPower,P,I,D\n" 
            f.write("%s" %dataheader)
        else:
            f = open(filename, "a+")
        #start data collection, stop when flag is flip    
        self.collectionFlag = True
        #set counter to only collect data if the set temperature and setpoint is not the same by more than Dt
        counter = pointsAfterStable
        startT = time()
        while(self.collectionFlag):
            while( counter>0):
                outputData = "%f,%s,%s,%s,%s\n" %(time()-startT, self.ls336.getSetTemp(1), self.ls336.getTemp("c"), 
                                  self.ls336.getHeater(1),self.ls336.getPID(1))
                f.write("%s" %outputData)
                f.flush()
                sleep(waitT)
                if abs(float (self.ls336.getSetTemp(1))- float(self.ls336.getTemp("c")))<dT:
                    counter-=1
                else:
                    counter = pointsAfterStable
            
        f.close()
    #clear flag    
    def clearCollectionFlag(self):
        self.collectionFlag = False;
        
#This is more than less the same class but this is using rs232/epic connection

class DataCollectionLs340():
    #create lakeshore object and set collection flag
       
    def __init__(self):
        self.ls336 = Lakeshore340()
        self.collectionFlag = False
        
        
    #start collecting data with fixed forat in ascii
    #function take 5 parameters
    #Filename
    #dT : different in setpoint and temperature that will trigger data collection
    #      set this to 0 for continuous measurement
    #poinsAfaterStable : number of extra points to collect after temperature is stable
    #waitT: time wait between each data read
    #newFile: if set to True a new file will be created otherwise data will be appended to the file.    
    def startCollection(self,filename, dT = 0.1, pointsAfterStable = 20, waitT = 2, newFile = True):
        #if new file write new header
        if newFile:
            f = open(filename, 'w')
            dataheader = "Time(s),SetTemp(K),Temp(K),HeatPower,P,I,D\n" 
            f.write("%s" %dataheader)
        else:
            f = open(filename, "a+")
        #start data collection, stop when flag is flip    
        self.collectionFlag = True
        startT = time()
        #set counter to only collect data if the set temperature and setpoint is not the same by more than Dt
        counter = pointsAfterStable
        while(self.collectionFlag and counter>0):
            
            outputData = "%f,%s,%s,%s,%s,%s,%s\n" %(time()-startT, self.ls336.getSetTemp(), self.ls336.getTemp(), 
                              self.ls336.getHeater(),self.ls336.getP(),self.ls336.getI(),self.ls336.getD())
            f.write("%s" %outputData)
            f.flush()
            sleep(waitT)
            if abs(float (self.ls336.getSetTemp())- float(self.ls336.getTemp()))<dT:
                counter-=1
            else:
                counter = pointsAfterStable
        
        f.close()
    #clear flag    
    def clearCollectionFlag(self):
        self.collectionFlag = False;