############################## Variables ###############################
dossier= /Sequence
nom1= LE_DENMAT
nom2= CAMBRESY
nom= $(nom1)_$(nom2)
chemin= /home/user/IN301
##############################
obj1= sequence.o gestion.o distance.o
obj2= $(obj1) famille.o
obj3= $(obj2) alignement.o
##############################
modeSegFault= --track-origins=yes
modeMemory1= --leak-check=full
modeMemory2= --leak-check=full --show-leak-kinds=all
##############################
gestion= gestion.c gestion.h
sequence= sequence.c sequence.h
distance= distance.c distance.h
famille= famille.c famille.h
alignement= alignement.c alignement.h
##############################
main= main1.c main2.c main3.c
progExtern= $(gestion) $(sequence) $(distance) $(famille) $(alignement)
projetADN= $(main) $(progExtern) makefile
############################ Fin variables #############################

################################ Main1 #################################
debugmain1: compile
	valgrind ./main1 $(dossier)
	
debug2main1: compile
	valgrind $(modeSegFault) ./main1 $(dossier)

debug3main1: compile
	valgrind $(modeMemory1) ./main1 $(dossier)

debug4main1: compile
	valgrind $(modeMemory2) ./main1 $(dossier)
############################## Fin main1 ###############################

################################ Main2 #################################
debugmain2: compile
	valgrind ./main2 $(dossier)
	
debug2main2: compile
	valgrind $(modeSegFault) ./main2 $(dossier)

debug3main2: compile
	valgrind $(modeMemory1) ./main2 $(dossier)

debug4main2: compile
	valgrind $(modeMemory2) ./main2 $(dossier)
############################## Fin main2 ###############################

################################ Main3 #################################
debugmain3: compile
	valgrind ./main3 $(dossier)
	
debug2main3: compile
	valgrind $(modeSegFault) ./main3 $(dossier)

debug3main3: compile
	valgrind $(modeMemory1) ./main3 $(dossier)

debug4main3: compile
	valgrind $(modeMemory2) ./main3 $(dossier)
############################## Fin main3 ###############################

################################ Main1 #################################
partie1: compile 
	./main1 $(dossier)
	
compile: main1.o $(obj1)
	gcc -Wall main1.o $(obj1) -o main1

main1.o: main1.c
	gcc -Wall -c -g main1.c
	
sequence.o: $(sequence)
	gcc -Wall -c -g sequence.c

gestion.o: $(gestion)
	gcc -Wall -c -g gestion.c
	
distance.o: $(distance)
	gcc -Wall -c -g distance.c
############################## Fin main1 ###############################

################################ Main2 #################################
partie2: compile2
	./main2 $(dossier)

compile2: main2.o $(obj2) 
	gcc -Wall main2.o $(obj2) -o main2
	
main2.o: main2.c
	gcc -Wall -c -g main2.c
	
famille.o: $(famille)
	gcc -Wall -c -g famille.c
############################## Fin main2 ###############################	

################################ Main3 #################################
partie3: compile3
	./main3 $(dossier)

compile3: main3.o $(obj3)
	gcc -Wall main3.o $(obj3) -o main3
	
main3.o: main3.c
	gcc -Wall -c -g main3.c
	
alignement.o: $(alignement)
	gcc -Wall -c -g alignement.c
############################## Fin main3 ###############################

############################### Archive ################################
archive:
	mkdir $(chemin)/$(nom)
	mkdir $(chemin)/$(nom)/Sequence
	cp $(projetADN) $(chemin)/$(nom)
	cp Sequence/* $(chemin)/$(nom)/Sequence
	tar -zcvf $(chemin)/$(nom).tar.gz $(nom)
	
#~ "c" : créer une nouvelle archive.
#~ "z" : permet d'activer la compression "gzip" pour un taux de compression plus important
#~ "v" : mode verbeux, permet d'afficher dans le détail les fichiers compressés
#~ "f" : indication de la donnée à compresser

############################# Fin archive ##############################

############################## Nettoyage ###############################
clean:
	rm -f *.o
	rm -f main1
	rm -f main2
	rm -f main3
	rm -rf famille
	rm -f *.txt
	clear
############################ Fin nettoyage #############################
