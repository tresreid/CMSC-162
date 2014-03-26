#solarmodel.py
#hard to tell if this actually works or not. Graphics are definately not right though.
import numpy as np
import pygame
from pygame.locals import *
import math

solarSystem = {} # documents the planetary bodies in the system by name and characteristics
emass = 5.9726 * (10**24) # mass of earth
au = 1495978707.0 #astronomical unit
forcedict = {} # documents the force on each planetary body

class particle(object):

    def __init__(self,name,m1,xp,yp,xv,yv): #creation of a body with the name, mass, x and y positions and velocities
        self.__name = name
        self.__mass = m1 # in Kg
        self.__xPos = xp # in km
        self.__yPos = yp 
        self.__xVel = xv # in km/s
        self.__yVel = yv
        solarSystem.update({name: self})

    #series of getters and setters
    def get_name(self):
        return self.__name
    def get_mass(self):
        return self.__mass
    def set_mass(self, mass):
        self.__mass = mass
    def get_xPos(self):
        return self.__xPos
    def set_xPos(self, xPos):
        self.__xPos = xPos
    def get_yPos(self):
        return self.__yPos
    def set_yPos(self, yPos):
        self.__yPos = yPos
    def get_xVel(self):
        return self.__xVel
    def set_xVel(self, xVel):
        self.__xVel = xVel
    def get_yVel(self):
        return self.__yVel
    def set_yVel(self, yVel):
        self.__yVel = yVel
    mass = property(get_mass, set_mass)
    xPos = property(get_xPos, set_xPos)
    yPos = property(get_yPos, set_yPos)
    xVel = property(get_xVel, set_xVel)
    yVel = property(get_yVel, set_yVel)
    name = property(get_name)

# updates calculates the force on each body and updates forcedict
def force(name):
    cx = 0
    cy = 0
    cm = 0
    for item in solarSystem:
        if (item == name):
            pass
        else:
            cx = ((cx * cm) + (solarSystem.get(item).mass * solarSystem.get(item).xPos*au))/ (cm + solarSystem.get(item).mass)
            cy = ((cy * cm) + (solarSystem.get(item).mass * solarSystem.get(item).yPos)*au)/ (cm + solarSystem.get(item).mass)
            cm = cm +solarSystem.get(item).mass

    distancesq = (((cx - solarSystem.get(name).xPos*au)**2) + ((cy - solarSystem.get(name).yPos*au)**2))
    force = (-(6.67*(10**(-11))) * cm * solarSystem.get(name).mass)/ distancesq

    forcedict.update({name: [force/solarSystem.get(name).mass,cx- solarSystem.get(name).xPos*au,cy- solarSystem.get(name).yPos*au]})
                            
def update(time): # time in seconds
    for item in solarSystem:
        force(item)
        angle = math.atan(forcedict.get(item)[2]/forcedict.get(item)[1])
        solarSystem.get(item).xPos += (solarSystem.get(item).xVel * time)
        solarSystem.get(item).yPos += (solarSystem.get(item).yVel * time)
        solarSystem.get(item).xVel += (forcedict.get(item)[0] * math.cos(angle) * time /au)
        solarSystem.get(item).yVel += (forcedict.get(item)[0] * math.sin(angle) * time /au)

def quarter():
    i =0
    while(i<7844000*4):
        update(1)
        print i
        i+= 1

sp = particle("Earth",1*emass,1.0,0,0,29.8)
s1 = particle("Sun",333000*emass, 0, 0,0,0)
s2 = particle("Mercury", 0.055*emass, 0.39,0,0,47.9) 
s3 = particle("Venus", 0.815*emass, 0.72,0,0,35)
s4 = particle("Mars",0.107 *emass, 1.5,0,0,24.1)
s5 = particle("Jupiter",318 *emass, 5.2,0,0,13.1)
s6 = particle("Saturn",95*emass, 9.54,0,0,9.6)
s7 = particle("Uranus",14*emass , 19.23,0,0,6.8)
s8 = particle("neptune",17*emass, 30.10,0,0,5.4)


######################### pygame code ##################3

def app():
    screen = pygame.display.set_mode((640, 480))
    sprite = pygame.image.load("gaia.bmp").convert()
    background = pygame.image.load('background.bmp').convert()
    screen.blit(background, (0, 0))
    while 1:
        for event in pygame.event.get():
            if event.type in (QUIT, KEYDOWN):
                sys.exit()
       # for item in solarSystem:
        screen.blit(sprite, (((solarSystem.get("Earth").xPos)+320), ((solarSystem.get("Earth").yPos)+240)))
        print solarSystem.get("Earth").yPos
           # screen.draw(sprite,((solarSystem.get(item).xPos / 10000000), (solarSystem.get(item).yPos / 10000000)))
        update(1000)
        pygame.display.flip()
       # pygame.time.delay(100)
