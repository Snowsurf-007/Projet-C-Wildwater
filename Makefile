# Fichiers sources
SRCS = histosrc.c historeal.c histoall.c leaks.c AVL.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Exécutables
EXEC = histosrc historeal histoall leaks

# Le compilateur
CC = gcc
CFLAGS = -Wall -Wextra -g

all: $(EXEC) 

# Règles pour les exécutables
histosrc: histosrc.o
	$(CC) $(CFLAGS) -o histosrc histosrc.o AVL.o

historeal: historeal.o
	$(CC) $(CFLAGS) -o historeal historeal.o AVL.o

histoall: histoall.o
	$(CC) $(CFLAGS) -o histoall histoall.o AVL.o

leaks: leaks.o AVL.o
	$(CC) $(CFLAGS) -o leaks leaks.o AVL.o

# Règles pour les fichiers objets
histosrc.o: histosrc.c biblio.h
	$(CC) $(CFLAGS) -c histosrc.c

historeal.o: historeal.c biblio.h
	$(CC) $(CFLAGS) -c historeal.c

histoall.o: histoall.c biblio.h
	$(CC) $(CFLAGS) -c histoall.c

leaks.o: leaks.c biblio.h
	$(CC) $(CFLAGS) -c leaks.c
	
AVL.o: AVL.c biblio.h
	$(CC) $(CFLAGS) -c AVL.c
	
# Nettoyage des fichiers objets
clean:
	rm -f $(OBJS) $(EXEC)

# Force la recompilation complète
rebuild: clean all
