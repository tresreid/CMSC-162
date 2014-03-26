import xml.etree.ElementTree as ET 
from datetime import date 
from sys import argv 
template = '{:<20} {:>15} {:>5} {:>5}'
template2= '{:<20} {:>15} {:>5} {:>5} {:>20}'
def num(text): 
    if text is None: 
        return 0.0 
    return float(text) 

def nstr(s): 
    if s is None: 
        return '.....' 
    return s 

class Particle(object): 
    events = ['mass','charge','symbol'] 
    def __init__(self,element): 
        self.name = element.find('name').text 
        for field in Particle.events: 
            setattr(self,field,element.find(field).text) 
            
    def __str__(self): 
        return template.format(nstr(self.name), 
                               nstr(self.mass), 
                               nstr(self.charge), 
                               nstr(self.symbol)
                               ) 
        
class Force(object): 
    events = ['mass','charge','symbol','force'] 
    def __init__(self,element): 
        self.name = element.find('name').text 
        for field in Force.events: 
            setattr(self,field,element.find(field).text) 
            
    def __str__(self): 
        return template2.format(nstr(self.name), 
                               nstr(self.mass), 
                               nstr(self.charge), 
                               nstr(self.symbol),
                               nstr(self.force)
                               ) 


# grab the XML 

doc = ET.parse(argv[1]) 
meet = doc.getroot() 

# print the header 
 

print(template.format('Fermion name','mass','charge','symbol')) 
print(template.format('---------','-----','-----','-----')) 

# print the table entries 

particles = list(map(Particle,doc.findall('.//particle'))) 
particles.sort() 
for p in particles: 
    print(p)

print
print(template2.format('Boson name','mass','charge','symbol','associated force')) 
print(template2.format('---------','-----','-----','-----','----------------')) 

# print the table entries 

forces = list(map(Force,doc.findall('.//force-carrier'))) 
forces.sort() 
for f in forces: 
    print(f)

