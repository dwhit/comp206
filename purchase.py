#!/usr/local/bin/python

import cgi
import sys
import os
import stat
import csv
import webbrowser

print "Content-type: text/html\n\n"
print "<html>\n<head>\n"
print "<title>Purchase</title>\n"
print "</head>\n"
print "<body>"
form = cgi.FieldStorage()

def main ():
	if form.has_key("uname") and form["uname"].value != "" and form.has_key("password") and form["password"].value != "":
		username = form["uname"].value
		password = form["password"].value	
		command = "./passweb -verify " + username + " " + password
		value = os.system(command)	
		if (value != 0):
			print "Login information incorrect! click below to return to catalogue. <p>"
			print "<a href=\"http://www.cs.mcgill.ca/~parauj2/catalogue\">CATALOGUE<a><br/>"	
		else:
			purchase(username, password)
	else:
  		print "Please enter your username and password. <p>"
		print "<a href=\"http://www.cs.mcgill.ca/~parauj2/catalogue\">CATALOGUE<a><br/>"

def purchase(username, password):
	itemOne = "0"
	itemTwo = "0"
	itemThree = "0"
	itemFour = "0"
	itemFive = "0"
	if form.has_key("item1") and form["item1"].value != "off" and form.has_key("item1A"):
		itemOne = form["item1A"].value
		notDigit = (not itemOne.isdigit())
		if (notDigit):
			error(1, 3)
                if int(itemOne) < 0:
                        error(1, 1)
	if form.has_key("item2") and form["item2"].value != "off" and form.has_key("item2A"):
                itemTwo = form["item2A"].value
		notDigit = (not itemTwo.isdigit())
		if (notDigit):
			error(2, 3)
		if int(itemTwo) < 0:
			error(2, 1)
	if form.has_key("item3") and form["item3"].value != "off" and form.has_key("item3A"):
                itemThree = form["item3A"].value
		notDigit = (not itemThree.isdigit())
		if (notDigit):
			error(3, 3)
		if int(itemThree) < 0:
			error(3, 1)
	if form.has_key("item4") and form["item4"].value != "off" and form.has_key("item4A"):
                itemFour = form["item4A"].value
		notDigit = (not itemFour.isdigit())
		if (notDigit):
			error(4, 3)
		if int(itemFour) < 0:
			error(4, 1)
	if form.has_key("item5") and form["item5"].value != "off" and form.has_key("item5A"):
                itemFive = form["item5A"].value
		notDigit = (not itemFive.isdigit())
		if (notDigit):
			error(5, 3)
		if int(itemFive) < 0:
			error(5, 1)
	i = 1
	test = "hi"
	fin = open('Inventory.csv', 'r')
	fout = open('Temp.csv', 'w')
	log = open('log.csv', 'a')
	price1 = 0
	price2 = 0
	price3 = 0
	price4 = 0
	price5 = 0
	first = True
	for line in fin:
		row = line.split(',')
		if (i == 1 and int(itemOne) != 0 and int(row[3]) >= int(itemOne)):
			row[3] = str(int(row[3]) - int(itemOne))
			price1 = int(itemOne) * int(row[4])
			fout.write(','.join(row))
			append = username + "," + "Freshly-killed pigeon coloured ruby,001," + str(itemOne) + "," + str(price1)
			log.write(append)
			first = False
		elif (i == 1 and int(itemOne) == 0):
			fout.write(line)
		elif (i == 1 and int(itemOne) > int(row[3])):
			error(1, 2)
		if (i == 2 and int(itemTwo) != 0 and int(row[3]) >= int(itemTwo)):
			row[3] = str(int(row[3]) - int(itemTwo))
			price2 = int(itemTwo) * int(row[4])
			fout.write(','.join(row))
			append = username + "," + "Ruby-eyed python,010," + str(itemTwo) + "," + str(price2)
			if first:
				log.write(append)
				first = False
			else:
				log.write("\n" + append)
		elif (i == 2 and int(itemTwo) == 0):
			fout.write(line)
		elif (i == 2 and int(itemTwo) > int(row[3])):
			error(2, 2)
		if (i == 3 and int(itemThree) != 0 and int(row[3]) >= int(itemThree)):
			row[3] = str(int(row[3]) - int(itemThree))
			price3 = int(itemThree) * int(row[4])
			fout.write(','.join(row))
                        append = username + "," + "Python for the anti-social,011, " + str(itemThree) + "," + str(price3)
			if first:
	                        log.write(append)
				first = False
			else:
				log.write("\n" + append)
		elif (i == 3 and int(itemThree) == 0):
			fout.write(line)
		elif (i == 3 and int(itemThree) > int(row[3])):
			error(3, 2)
		if (i == 4 and int(itemFour) != 0 and int(row[3]) >= int(itemFour)):
			row[3] = str(int(row[3]) - int(itemFour))
			price4 = int(itemFour) * int(row[4])
			fout.write(','.join(row))
                        append = username + "," + "Fair trade coffee beans,100," + str(itemFour) + "," + str(price4)
 			if first:
				log.write(append)
				first = False
			else:
                        	log.write("\n" + append)
		elif (i == 4 and int(itemFour) == 0):
			fout.write(line)
		elif (i == 4 and int(itemFour) > int(row[3])):
			error(4, 2)
		if (i == 5 and int(itemFive) != 0 and int(row[3]) >= int(itemFive)):
			row[3] = str(int(row[3]) - int(itemFive))
			price5 = int(itemFive) * int(row[4])
			fout.write(','.join(row))
                        append = username + "," + "Tears of the gods,101," + str(itemFive) + "," + str(price5)
			if first:
				log.write(append)
			else:
                        	log.write("\n" + append)
		elif (i == 5 and int(itemFive) == 0):
			fout.write(line)
		elif (i == 5 and int(itemFive) > int(row[3])):
			error(5, 2)
		i = i+1
	if not first:
		log.write("\n")
	fout.close()
	fin.close()
	log.close()
	fout =  open('Inventory.csv', 'w')
	fin = open('Temp.csv', 'r')
	for line in fin:
		fout.write(line)
	fin.close()
	fout.close()
	displayBill(price1, price2, price3, price4, price5, itemOne, itemTwo, itemThree, itemFour, itemFive)
	print "<a href=\"http://www.cs.mcgill.ca/~parauj2/homepage\">HOME<a><br/>"
	print "<a href=\"http://www.cs.mcgill.ca/~parauj2/catalogue\">CATALOGUE<a><br/>"

def displayBill(price1, price2, price3, price4, price5, itemOne, itemTwo, itemThree, itemFour, itemFive):
	total = int(price1) + int(price2) + int(price3) + int(price4) + int(price5)
	taxedTotal = float(total) * 0.05 + float(total) * 0.095 + float(total)
	print """<body bgcolor="green">
		<br/>
		<br/>
		<center>
		<!--========================= TABLE========================-->
		<!-- !!!!TOP ROW !!!! --->
		<table border="1" bgcolor=#FFFFFF>
                <tr>
                <th>Item</th>
                <th>Price</th>
                <th>Quantity</th>
                <th>Total</th>

		<!---1st ITEM: 2nd ROW!!!!!--->
                </tr>
                <th>Freshly-killed-pigeon coloured ruby</th>
                <td>$67.00</td>
                <td>""" + itemOne + """</td>
                <td>$""" + str(price1) + """.00</td>

                <!---2nd ITEM: 3rd ROW!!!!!--->
                </tr>
                <th>Ruby-eyed python</th>
                <td>$40.00</td>
                <td>""" + itemTwo + """</td>
                <td>$""" + str(price2) + """.00</td>

                <!---3rd ITEM: 4th ROW!!!!!--->
                </tr>
                <th>Python for the anti-social</th>
                <td>$60.00</td>
                <td>""" + itemThree + """</td>
                <td>$""" + str(price3) + """.00</td>

                <!---4th ITEM: 5th ROW!!!!!--->
                </tr>
                <th>Fair trade coffee beans</th>
                <td>$20.00</td>
                <td>""" + itemFour + """</td>
                <td>$""" + str(price4) + """.00</td>

                <!---5th ITEM: 6th ROW!!!!!--->
                </tr>
                <th>Tears of the gods</th>
                <td>$30.00</td>
                <td>""" + itemFive + """</td>
                <td>$""" + str(price5) + """.00</td>

		<!---TOTAL BEFORE TAXES--->
                </tr>
                <th>Total cost (before taxes)</th>
                <td></td>
		<td></td>
                <td>$""" + str(total) + """.00</td>

                <!---GST--->
                </tr>
                <th>GST</th>
                <td></td>
		<td></td>
                <td>%5.0</td>

                <!---QST--->
                </tr>
                <th>QST</th>
		<td></td>
                <td></td>
                <td>%9.5</td>
 
                <!---TOTAL AFTER TAXES--->
                </tr>
                <th>Total cost</th>
		<td></td>
                <td></td>
                <td>$""" + str("%0.2f" % (taxedTotal,)) + """</td>

	</tr>
	</table>
	</br>
	</br>
	<!--============================================================-->"""

def error(item, errorType):
	if (errorType == 1):
		if (item == 1):
			print "YOU CANNOT BUY A NEGATIVE AMOUNT OF FRESHLY-KILLED PIGEON COLOURED RUBIES!"
		if (item == 2):
			print "YOU CANNOT BUY A NEGATIVE AMOUNT OF RUBY-EYED PYTHONS!"
		if (item == 3):
			print "YOU CANNOT BUY A NEGATIVE AMOUNT OF PYTHONS FOR THE ANTI-SOCIAL!"
		if (item == 4):
			print "YOU CANNOT BUY A NEGATIVE AMOUNT OF FAIR TRADE COFFEE BEANS!"
		if (item == 5):
			print "YOU CANNOT BUY A NEGATIVE AMOUNT OF TEARS OF THE GODS!"
	if (errorType == 2):
		if (item == 1):
			print "NOT ENOUGH FRESHLY-KILLED PIGEON COLOURED RUBIES IN INVENTORY!"
		if (item == 2):
			print "NOT ENOUGH RUBY-EYED PYTHONS IN INVENTORY!"
		if (item == 3):
			print "NOT ENOUGH PYTHONS FOR THE ANTI-SOCIAL IN INVENTORY!"
		if (item == 4):
			print "NOT ENOUGH FAIR TRADE COFFEE BEANS IN INVENTORY!"
		if (item == 5):
			print "NOT ENOUGH TEARS OF THE GODS IN INVENTORY!"
	if (errorType == 3):
			print "INVALID INPUT: MUST ENTER AN INTEGER VALUE!" 
	print "PLEASE RETURN TO <a href=\"http://www.cs.mcgill.ca/~parauj2/catalogue\">CATALOGUE<a><br/>"
	print "</form></body></html>"
	sys.exit()
print "</form></body></html>"
main()

