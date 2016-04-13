import serial
import time
import cPickle as pickle
from math import *
from threading import Thread,Lock,Event,Timer

mutexAC = Lock()
mutexBR = Lock()

start = Event()
numConfigOK = Event()


# IMPORTANT : ardBR et ardAC sont des liens symboliques dans /dev
# qui pointent vers les bonnes Arduino. La selection se fait par le numero
# de serie des cartes, donc ce code ne marchera plus si une des arduinos est remplacee.

serBR = serial.Serial('/dev/ardBR', 115200)
serAC = serial.Serial('/dev/ardAC', 115200, timeout=0.1)



def stopEverything():
    with mutexAC:
	serAC.write('s')
    with mutexBR:
	serBR.write('bsssssssssse')
    print "Commandes d'arret envoyees"


class ArduinoAC(Thread):

    def __init__(self):
	Thread.__init__(self)
	self.end = False
	self.configPalets = 1

    def run(self):
	
	while(not self.end):
	    with mutexAC:
	        c = serAC.read(1)
	    if(c == 'x' or c == 'o'):
		with mutexBR:
		    serBR.write('b' + c + '         e')
		    print 'OBSTACLE : ' + c

	    elif(c == 'g'):
		start.set()
	    elif(c in '12345' and c != ''):
		self.configPalets = int(c)
		numConfigOK.set()

	    time.sleep(0.1)

    def quit(self):
	self.end = True

    def write(self, c):
	with mutexAC:
	    serAC.write(c)


def normalizeAngle(angle):
    while (angle <= -pi):
	 angle += 2*pi
    while (angle > pi):
	angle -= 2*pi;
    return angle

# Main

arduinoAC = ArduinoAC()
arduinoAC.start()
time.sleep(2)

arduinoAC.write('r') # On demande la config des palets


 
pack = pickle.load(open('waypoints.txt','r'))
side = pack[0]
waypoints = pack[1]

rX,rY,_ = waypoints[0]

if(side == 'g')
    rAngle = 0
else:
    rAngle = pi

del waypoints[0]

cmdAC = ['f','t','o']

numConfigOK.wait(5)
print arduinoAC.configPalets
start.wait()

timer = Timer(20.0, stopEverything)
timer.start()

try:

    for (x,y,m) in waypoints:
        print "Waypoint (" + str(x) + " " + str(y) + ")"
    
        arduinoAC.write(cmdAC[m])    
        dX, dY = x-rX, y-rY

        distance = round(hypot(dX, dY))
        targetAngle = atan2(dY,dX)
        angle = normalizeAngle(targetAngle - rAngle)

        if(angle > pi/2 or angle < -pi/2):
	    angle = normalizeAngle(pi + angle)
            distance = -distance	

        angle = round(angle, 3)

        strAngle = format(int(1000*angle),'05')
        strDistance = format(int(distance),'05')

        print "Envoi " + str(angle) + " " + str(distance) + " -> " + strAngle + " " + strDistance

        msg = 'b' + strAngle + strDistance + 'e'
        with mutexBR:
		serBR.write(msg)
        time.sleep(1)

        while True:
            c = serBR.read(1)
            if(c == 'k'):
	        break
        
        rX,rY = x,y
        rAngle += angle

except (KeyboardInterrupt, SystemExit) as e:
    raise e
finally:
    arduinoAC.quit()
    arduinoAC.join()
    print 'Clean exit'
    
	
arduinoAC.quit()
arduinoAC.join()

print "Fin"
