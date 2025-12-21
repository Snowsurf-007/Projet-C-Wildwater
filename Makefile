# Fichiers sources
SRCS = histosrc.c historeal.c histoall.c leaks.c AVL.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Exécutables
EXEC = histosrc historeal histoall leaks

# Le compilateur
CC = gcc
CFLAGS = -Wall -Wextra -g
	
# Règles pour les exécutables
histosrc: histosrc.o
	$(CC) $(CFLAGS) -o histosrc histosrc.o

historeal: historeal.o
	$(CC) $(CFLAGS) -o historeal historeal.o

histoall: histoall.o
	$(CC) $(CFLAGS) -o histoall histoall.o

leaks: leaks.o
	$(CC) $(CFLAGS) -o leaks leaks.o

# Règles pour les fichiers objets
histosrc.o: histosrc.c biblio.h
	$(CC) $(CFLAGS) -c histosrc.c

historeal.o: historeal.c biblio.h
	$(CC) $(CFLAGS) -c historeal.c

histoall.o: histoall.c biblio.h
	$(CC) $(CFLAGS) -c histoall.c

leaks.o: leaks.c biblio.h
	$(CC) $(CFLAGS) -c leaks.c
	
# Nettoyage des fichiers objets
clean:
	rm -f $(OBJS) $(EXEC)

# Force la recompilation complète
rebuild: clean all
