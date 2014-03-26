import urllib2
textFile1 = urllib2.urlopen("http://www.nhc.noaa.gov/data/hurdat/hurdat2-atlantic-1851-2012-060513.txt")

class Storm:
    def readDate(self,textFile):
# takes the text and throws out unusable data
        reducedList =[]
        for line in textFile:
            if line[0].isdigit():
                reducedList.append(line)
            else:
                pass
        return reducedList
    def averageDailyWinds(self,reducedlist):
        # takes the average windspeed per day
        winddic ={}
        for item in reducedlist:
            winddic[item[:8]] = winddic.get(item[:8],[]) + [int(item[38:41])]
        aveday = {}
        for key in winddic:
            aveday[key] = sum(winddic[key])/ 4.0
        return aveday
    def saffir_simpson_day(self,aveday):
        # convertes to saffir simpson scale and adds it based on year
        yearwinds = {}
        for item in aveday:
            if aveday[item] < 82:
                yearwinds[item[:4]] =  yearwinds.get(item[:4], []) + [1]
            elif aveday[item] < 95:
                yearwinds[item[:4]] =  yearwinds.get(item[:4], []) + [2]
            elif aveday[item] < 112:
                yearwinds[item[:4]] =  yearwinds.get(item[:4], []) + [3]
            elif aveday[item] < 136:
                yearwinds[item[:4]] =  yearwinds.get(item[:4], []) + [4]
            else:
                yearwinds[item[:4]] =  yearwinds.get(item[:4], []) + [5]  
        return yearwinds

st = Storm()
print((st.saffir_simpson_day(st.averageDailyWinds(st.readDate(textFile1) ))))
