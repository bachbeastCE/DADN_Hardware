from codecs import ignore_errors

import serial.tools.list_ports
import random
import time
import sys
from Adafruit_IO import MQTTClient

AIO_FEED_ID = ["dadn-door", "dadn-detect"]
AIO_USERNAME = "BachbeastCE"
AIO_KEY = "aio_eaue76HZurAww7Kso1LWJUbRs8Q8"

def connected (client):
    print (" Ket noi thanh cong ...")
    for feed in AIO_FEED_ID:
        client.subscribe(feed)

def subscribe ( client , userdata , mid , granted_qos ):
    print (" Subcribe thanh cong ... ")

def disconnected ( client ):
    print (" Ngat ket noi ... ")
    sys.exit (1)

detect_state = 0
door_state = 0

def message ( client , feed_id , payload ):
    print (" Nhan du lieu : " + payload + " tu feed " + feed_id)
    if feed_id == "dadn-door":
        if payload == "1": door_state = 1
        else: door_state = 0;
    if feed_id == "dadn-detect":
        if payload == "1":  detect_state = 1
        else: detect_state = 0;

#    if isMicrobitConnected:
#       ser.write((str("*"+feed_id+":"+payload) + "#").encode())

# MQTT INITIAL
client = MQTTClient ( AIO_USERNAME , AIO_KEY )
client . on_connect = connected
client . on_disconnect = disconnected
client . on_message = message
client . on_subscribe = subscribe
client . connect ()
client . loop_background ()

# SERIAL CONFIGURATION
def getPort ():
    ports = serial.tools.list_ports.comports()
    N = len (ports)
    commPort = "None"
    for i in range (0, N):
        port = ports[i]
        strPort = str(port)
        if " USB Serial Device " in strPort :
            splitPort = strPort.split (" ")
            commPort = ( splitPort [0])
    return commPort

isMicrobitConnected = False
#if getPort () != " None ":
#    ser = serial.Serial ( port = "COM3" , baudrate =9600)
#    print("Connected to COM4")
#    isMicrobitConnected = True

# PROCESS DATA
def processData (data):
    data = data.replace ("!", "")
    data = data.replace ("#", "")
    splitData = data.split (":")
    print(splitData)
    if splitData [1] == "TEMP":
        client.publish (AIO_FEED_ID[0], splitData [2])

mess = ""
def readSerial():
    bytesToRead = ser.inWaiting ()
    if (bytesToRead > 0):
        global mess
        mess = mess + ser.read(bytesToRead).decode("UTF -8", errors='ignore')
        while ("#" in mess ) and ("!" in mess ):
            start = mess . find ("!")
            end = mess . find ("#")
            processData ( mess [ start :end + 1])
            if (end == len(mess)):
                mess = ""
            else :
                mess = mess [end +1:]

while True :
#    if isMicrobitConnected:
#        readSerial()
    time.sleep(10)
    pass