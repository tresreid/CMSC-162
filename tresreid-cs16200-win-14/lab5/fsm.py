#!/usr/bin/python
#fsm.py

import sys
from ConfigParser import *

class FSM():
    def __init__(self, filename):
        self.transitionDict = dict() 
       
        pars = ConfigParser()
        pars.read(filename)
        names = pars.get('states','names').split(',') #dictionary of names and states
        self.state = pars.get('states','start') #gets start state
        self.end = pars.get('states','end') #gets end state
        
        #loop through the names to add them to the dict
        for n in names:
            n = n.strip() #clears whitespace
            nDict = dict() #new dictionary for each name

            translist = pars.get('transitions',n).split(',') 
            for t in translist:
                sToD = t.split(':') # state to destination
                origin = sToD[0].strip() #clears whitespace
                dest = sToD[1].strip()
                #adds the origin and destination to the new dictionary
                val = nDict.setdefault(origin,dest)
                if(val != dest):
                    print 'Non-deterministic behavior detected'
                    sys.exit(1)
            self.transitionDict[n] = nDict

    def transition(self, character):
        tDict = self.transitionDict[self.state] #gets current state
        self.state = tDict.get(character) # reads character to get transition
        if(self.state == None): 
            self.state = tDict.get('*') #no transition goes back to * state
            if(self.state == None):
                print 'Non-exhaustive transitions detected'
                sys.exit(1)

fsm = FSM(sys.argv[1])

for c in sys.argv[2]:
    fsm.transition(c)

if fsm.state == fsm.end:
    print 'Accept'
else:
    print 'Reject. Ended in state ', fsm.state
