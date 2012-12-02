passweb.cgi : passweb2.o menu.cgi login.cgi
	gcc -o passweb.cgi passweb2.o
	chmod 755 passweb.cgi

passweb2.o : passweb2.c
	gcc -c passweb2.c
	chmod 755 passweb2.o 
	chmod 755 passweb2.c

menu.cgi : menu2.o
	gcc -o menu.cgi menu2.o
	chmod 755 menu.cgi

menu2.o : menu2.c
	gcc -c menu2.c
	chmod 755 menu2.o
	chmod 755 menu2.c

login.cgi : log.o
	gcc -o login.cgi log.o
	chmod 755 login.cgi

log.o : log.c
	gcc -c log.c
	chmod 755 log.o
	chmod 755 log.c

gitup :
	cd ..
	git add .
	git commit -m $1
	git push origin master
