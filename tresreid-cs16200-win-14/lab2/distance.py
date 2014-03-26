#!/usr/bin/python

import sys
import re
import math
#reads the first file
f = open(sys.argv[1], 'r') 
file1 = f.read()
f.close()
# reads the second file
f = open(sys.argv[2], 'r') 
file2 = f.read()
f.close()

# makes a dictionary with each word and the frequency
def wordFreq (file):
    word_list = re.split('\s+', file)
    freq_dic = {}
    normalized = {}
    freqSq =[]
    punctuation = re.compile(r'[.?!,":;]')
    for word in word_list:
        word = punctuation.sub("", word)
        try:
            freq_dic[word] += 1
        except:
            freq_dic[word] = 1
            freq_list = freq_dic.items()
            #squares the frequencies for normalization
    for key in freq_dic:
        freqSq += [freq_dic[key]**2]
        #normalizes the frequencies
    for key in freq_dic:
        normalized[key] = freq_dic[key]/ math.sqrt(sum(freqSq))
    return normalized
#finds the distance
def distance (norm1, norm2):
    abslist =[]
    #makes a new dictionary with all the keys of the other two
    d3 = dict(norm1, **norm2)
    #checks the difference in frequencies
    for key in d3:
        abslist += [(norm1.get(key,0) - norm2.get(key,0))]
        squareabs = [i ** 2 for i in abslist]
        #finds the distance
    dis = math.sqrt(sum(squareabs))
    return dis
#shows distance is the same dispite the order of input
print(distance(wordFreq(file1), wordFreq(file2)))
print(distance(wordFreq(file2), wordFreq(file1)))
