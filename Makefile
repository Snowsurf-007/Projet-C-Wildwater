# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Le compilateur
CC = gcc
	
histosrc: histosrc.o AVL.o
	$(CC) -o $(EXEC) $(OBJS)
	
histosrc.o: histosrc.c biblio.h
	$(CC) -o $(EXEC) $(OBJS)
	
historeal: historeal.o AVL.o
	$(CC) -o $(EXEC) $(OBJS)
	
historeal.o: historeal.c biblio.h
	$(CC) -o $(EXEC) $(OBJS)
	
histoall: histoall.o AVL.o
	$(CC) -o $(EXEC) $(OBJS)
	
histoall.o: histoall.c biblio.h
	$(CC) -o $(EXEC) $(OBJS)
	
leaks: leaks.o AVL.o
	$(CC) -o $(EXEC) $(OBJS)
	
leaks.o: leaks.c
	$(CC) -o $(EXEC) $(OBJS)
	
AVL.o: AVL.c
	$(CC) -o $(EXEC) $(OBJS)
	
# Nettoyage des fichiers objets
clean:
	rm -f $(OBJS) $(EXEC)

# Force la recompilation complète
rebuild: clean all
