passweb.cgi : passweb.o menu.cgi login.cgi
	gcc -o passweb.cgi passweb.o
	chmod 755 passweb.cgi

passweb.o : passweb.c
	gcc -c passweb.c
	chmod 755 passweb.o 
	chmod 755 passweb.c

menu.cgi : menu.o
	gcc -o menu.cgi menu.o
	chmod 755 menu.cgi

menu.o : menu.c
	gcc -c menu.c
	chmod 755 menu.o
	chmod 755 menu.c

login.cgi : login.o
	gcc -o login.cgi login.o
	chmod 755 login.cgi

login.o : login.c
	gcc -c login.c
	chmod 755 login.o
	chmod 755 login.c

gitup :
	cd ..
	git add .
	git commit -m $1
	git push origin master
