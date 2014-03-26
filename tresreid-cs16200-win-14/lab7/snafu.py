#!/usr/bin/python

import xml.etree.ElementTree as ET
from sys import argv

invTree = ET.parse(argv[1]).getroot()
transTree = ET.parse(argv[2]).getroot()
#newXMLFile = argv[3]

totalValue = 0

for action in transTree.findall("./*"):
    if action.tag == "sale":
        soldItem = invTree.find("./item[@id='" + action.get("itemID") + "']")
        itemStock = soldItem.get("stock")
        itemPrice = float(soldItem.find("./price").text)

        if itemStock == "0":
            print "Warning: Inventory shows no stock for product '"+soldItem.find("./name").text+"'"
            print "Recheck inventory."
        else:
            soldItem.set("stock",str(int(itemStock) - 1))

            if action.get("card") != None and soldItem.get("card") == None:
                print "Attempt to use discount card on non-discount product ("+soldItem.find("./name").text+")"

            if itemStock == "1":
                print "Warning: '"+soldItem.find("./name").text+"' stock depleted"
        if action.get("card") != None and soldItem.get("card") != None:
            itemPrice *= 0.85
        totalValue += itemPrice

    elif action.tag == "restock":
        restockedItem = invTree.find("./item[@id='" + action.get("itemID") + "']")
        restockedItem.set("stock",str(int(restockedItem.get("stock")) + int(action.get("num"))))

    elif action.tag == "remove":
        invTree.remove(invTree.find("./item[@id='" + action.get("itemID") + "']"))

print "Total sales for today:",round(totalValue,2)

#ET.ElementTree(invTree).write(newXMLFile)