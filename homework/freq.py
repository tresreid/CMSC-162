#!/usr/bin/python

import sys
import re

word_list = re.split('\s+', raw_input("input: "))
print 'Words in text:', len(word_list)

freq_dic = {}

punctuation = re.compile(r'[.?!,":;]')
for word in word_list:
    word = punctuation.sub("", word)
    try:
        freq_dic[word] += 1
    except:
        freq_dic[word] = 1

print 'number of unique words:', len(freq_dic)
        
freq_list = freq_dic.items()

#freq_list.sort()

for word, freq in freq_list:
    print word, freq
