"""
Created on 18 Nov2022

@author: wvx67826

@deprecated: 
    Python class to connect and control Laksshore 336 
     user manual: https://www.lakeshore.com/docs/default-source/product-downloads/336_manual0ebc9b06cbbb456491c65cf1337983e4.pdf?sfvrsn=2e8633a3_1
@version: 1.0 
    class take two optional parameters, buffer size for the readout and a connection time out in seconds 

        
    get/set command:
       setVoltageAmp(self, v : float) : bool
       getVoltage(self) : String

"""
from src.Control.TCPSocket.TCPSocket import TCPSocket
from epics import caget, caput

    

class Lakeshore336(TCPSocket):
    def __init__(self, bufferSize = 4096, timeout = 5):
        super().__init__(bufferSize, timeout)
        
    

#================== Get Temperature ==============================================================
    """ Get Temperature take 1 parameter, the sensor channel
        return temperature 
    """
    def getTemp(self, channel):
        com = "KRDG?%s" %channel
        if (self.sendCom(com)):
            return self.readBuffer().strip().split(",")[0]
        else:
            return "Temperature readback failed"

#================== Get Temperature Setpoint==============================================================
    """ Get set point Temperature, take 1 parameter, channel setpoint
        return temperature setpoint
    """
    def getSetTemp(self,channel):
        com = "SETP?%s" %channel
        if (self.sendCom(com)):
            return self.readBuffer().strip()
        else:
            return "Temperature readback failed"

#================== Set Temperature Setpoint==============================================================
    """ Set Temperature
        return true /false
    """
    def setTemp(self, channel, value):
        com = "SETP%s,%s" %(channel,value) 
        return self.sendCom(com)

#================== Get Pid ==============================================================
    """ Get PID take 1 parameter, the sensor channel
        return "P, I, D" in one string
    """
    def getPID(self, channel):
        com = "PID?%s" %channel
        if (self.sendCom(com)):
            return self.readBuffer().strip()
        else:
            return "PID readback failed"

#================== Set PID==============================================================
    """ Set PID take 4 parameters, channel, p, i, d 
        return true /false
    """
    def setPID(self, channel, p, i,d):
        com = "PID%s,%s,%s,%s" %(channel, p, i, d) 
        return self.sendCom(com)

#================== Get Heater power ==============================================================
    """ Get heater power take 1 parameter, the heater channel
        return heater power
    """
    def getSetHeater(self, channel):
        com = "MOUT?%s" %channel
        if (self.sendCom(com)):
            return self.readBuffer().strip()
        else:
            return "Heater readback failed"
        
#================== Get Heater power output==============================================================
    """ Get heater power take 1 parameter, the heater channel
        return heater power
    """
    def getHeater(self, channel):
        com = "HTR?%s" %channel
        if (self.sendCom(com)):
            #print(self.readBuffer())
            return self.readBuffer().strip()
        else:
            return "Heater readback failed"

#================== Set Heater ==============================================================
    """ Setheater power 
        return true /false
    """
    def setHeater(self, channel, value):
        com = "MOUT%s,%s" %(channel, value) 
        return self.sendCom(com)
#================== Set AutoTune ==============================================================
    """ Set system to autoTune 
        return true /false
        channel is the control loop channel
        value 0 = p, 1 = pi, 3 = pid
    """
    def autoTune(self, channel, value):
        com = "ATUNE%s,%s" %(channel, value) 
        return self.sendCom(com)



    
#================== Get autotune status ==============================================================
    """ Get autotune status
        return string 
    info for autotune error
    
    Returned <tuning status>,<output>,<error status>,<stage status>[term]
    Format n,n,n,nn
    <tuning status> 0 = no active tuning, 1 = active tuning.
    <output> Heater output of the control loop being tuned (if tuning):
    1 = output 1, 2 = output 2
    <error status> 0 = no tuning error, 1 = tuning error
    <stage status> Specifies the current stage in the Autotune process.
    If tuning error occurred, stage status represents stage
    that failed.
    
    """
    def getAutoTuneStatus(self):
        com = "TUNEST??%s"
        if (self.sendCom(com)):
            return self.readBuffer().strip()
        else:
            return "Heater readback failed"



class Lakeshore340():
    def __init__(self, epicIp = "ME01D-EA-TCTRL-01:"):
        self.epicIPStart = epicIp

#================== Get Temperature ==============================================================
    """
    Get Temperature take 1 parameter, the sensor channel
    return temperature 
    
    """        

    def getTemp(self):
        try:
            return float(caget(self.epicIPStart +"KRDG1"))
        except:
            return 0
#================== Get Temperature Setpoint==============================================================
    """ Get set point Temperature, take 1 parameter, channel setpoint
        return temperature setpoint
    """
    def getSetTemp(self):
        try:
            return float(caget(self.epicIPStart +"SETP"))
        except:
            return 0

#================== Set Temperature Setpoint==============================================================
    """ Set Temperature
        return true /false
    """
    def setTemp(self, value):
        try:
            caput(self.epicIPStart +"SETP_S", value)
            return 1
        except:
            return 0
        
#================== Get PID ==============================================================
    """ Get PID take 1 parameter, the sensor channel
        return "P, I, D" in one string
    """
    def getP(self):
        try:
            
            
            return float(caget(self.epicIPStart +"P"))
        except:
            return 0
    def getI(self):
        try:
            
            return float(caget(self.epicIPStart +"I"))
        except:
            return 0
    def getD(self):
        try:
            
            return float(caget(self.epicIPStart +"D"))
        except:
            return 0

#================== Set PID ==============================================================
    """ Get PID take 1 parameter, the sensor channel
        return "P, I, D" in one string
    """
    def setP(self, value):
        try:
            caput(self.epicIPStart +"P_S", value)
            return 1
        except:
            return 0
    def setI(self, value):
        try:
            caput(self.epicIPStart +"I_S", value)
            return 1
        except:
            return 0
    def setD(self, value):
        try:
            caput(self.epicIPStart +"D_S", value)
            return 1
        except:
            return 0
        
#================== Get Heater power ==============================================================
    """ Get heater power take 1 parameter, the heater channel
        return heater power
    """
    def getHeater(self):
        try:
            
            return float(caget(self.epicIPStart +"MOUT"))
        except:
            return 0

#================== Set Heater ==============================================================
    """ Setheater power 
        return true /false
    """
    def setHeater(self, value):
        try:
            caput(self.epicIPStart +"MOUT_S", value)
            return 1
        except:
            return 0


#================== Set mode ==============================================================
    """ Set controler mode #
         1 = PID
        2 = 
        3 = open loop
        4 = auto tune
        return true /false
    """
    def setMode(self, value):
        try:
            caput(self.epicIPStart +"CMODE_S", value)
            return 1
        except:
            return 0
#================== Get Mode ==============================================================
    """ Get controler mode:
        1 = PID
        2 = 
        3 = open loop
        4 = auto tune
    """
    def getMode(self):
        try:
            
            return float(caget(self.epicIPStart +"CMODE"))
        except:
            return 0



