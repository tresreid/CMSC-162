

target = float(raw_input("Input target value: "))
terms = int(raw_input("Input number of terms: "))
i=2.0
j=1.0
showseries = "0.0"
series=0

while((((i-2)/2) + ((j-1)/2)) < terms):
    if(series<=target):
        nextterm = i**(-1)
        series += nextterm
        showseries = showseries + " + " + "1/"+str(i)
        i+=2
    else:
        nextterm = -j**(-1)
        series += nextterm
        showseries = showseries + " - " + "1/"+str(j)
        j+=2
print "reached value: ", series
print "number of positive terms: ", (i-2)/2
print "number of negative terms: ", (j-1)/2
print "approximate remainder/error: ", abs(target-series)
print "series: ", showseries
