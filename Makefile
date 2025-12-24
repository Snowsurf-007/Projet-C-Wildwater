# Fichiers sources
SRCS = histo.c leaks.c AVL.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Exécutables
EXEC = histo leaks

# Le compilateur
CC = gcc
CFLAGS = -Wall -Wextra -g

all: $(EXEC) 

# Règles pour les exécutables
projet: projet.o AVL.o
	$(CC) $(CFLAGS) -o projet projet.o AVL.o

# Règles pour les fichiers objets
projet.o: projet.c biblio.h
	$(CC) $(CFLAGS) -c projet.c
	
AVL.o: AVL.c biblio.h
	$(CC) $(CFLAGS) -c AVL.c
	
# Nettoyage des fichiers objets
clean:
	rm -f $(OBJS) $(EXEC)

# Force la recompilation complète
rebuild: clean all
