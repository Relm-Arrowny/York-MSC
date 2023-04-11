'''
Created on 23 Nov 2022

@author: wvx67826

@deprecated: 
   keep collecting data until the program is stopped

'''


from src.Control.Lakeshore.Lakeshore import Lakeshore336
from src.dataCollection.DataCollection import DataCollection
import threading

dc = DataCollection()
dc.connect("172.23.110.186", 7777)
#filename = "..\\data\\EM_LS336_during experiment.dat"
filename = "..\\data\\EM_LS336_pid_autoPID_380K-2.dat"

t1 = threading.Thread(target=dc.startCollection, args=(filename, -1, 20, 1,True))
t1.start()
userInput = None
#dc.ls336.setPID(1, 15, 20, 0)
#dc.ls336.setTemp(1, 100)
while userInput != "y":
    
    userInput = input("End collection? (y/n)")
dc.clearCollectionFlag()
t1.join()


dc.disconnet()

