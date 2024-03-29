#!/usr/bin/awk -f

BEGIN{
    FS="[ ]+"
    RS="\n"
}
# incriments the spam files and adds the spam score
$8 ~ /SPAM/ {
    scount+=1
    score+= $18
}
# incriments the clean files
$8 ~ /CLEAN/ {
    ccount+=1
}
#increments the senders and recipients
$7 ~ /Checking/ {
    sender[$8]+=1
    recipient[$10]+=1
}
#incriments the infected files
$8 ~ /INFECTED/ {
    icount+=1
}
END{
    print("spam: ", scount);
    print("ham: ", ccount);
    print("Infected files: ", icount);
    print("Spam to Ham ratio: ", (scount/ccount));
    print("Average Spam score: ", (score/scount)); 
    print("Top senders:")
    #creates senders which is identical to sender to be sorted later. creates senders which flips the key and index of sender
    for (i in sender){
    	senders[sender[i]] = i
	sender2[i] = sender[i]
    }
    #sorts senders2
    n= asort(sender2)
    #creates senders3 which flips the order of sender2
    for (i=0; i<=n; i++){
	sender3[i] = sender2[n-i]
    }
    for (i=0; i<10;i++){
	print (senders[sender3[i]], ":",  sender[senders[sender3[i]]])
    }
    print("Top recipients:")
  for (i in recipient){
    	recipients[recipient[i]] = i
	recipient2[i] = recipient[i]
    }
    #sorts recipient2
    n= asort(recipient2)
    #creates recipient3 which flips the order of recipient2
    for (i=0; i<=n; i++){
	recipient3[i] = recipient2[n-i]
    }
    for (i=0; i<10;i++){
	print (recipients[recipient3[i]], ":",  recipient[recipients[recipient3[i]]])
    }
}
   