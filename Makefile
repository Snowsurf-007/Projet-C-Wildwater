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
histo: histo.o
	$(CC) $(CFLAGS) -o histo histo.o

leaks: leaks.o AVL.o
	$(CC) $(CFLAGS) -o leaks leaks.o AVL.o

# Règles pour les fichiers objets
histo.o: histo.c biblio.h
	$(CC) $(CFLAGS) -c histo.c

leaks.o: leaks.c biblio.h
	$(CC) $(CFLAGS) -c leaks.c
	
AVL.o: AVL.c biblio.h
	$(CC) $(CFLAGS) -c AVL.c
	
# Nettoyage des fichiers objets
clean:
	rm -f $(OBJS) $(EXEC)

# Force la recompilation complète
rebuild: clean all
