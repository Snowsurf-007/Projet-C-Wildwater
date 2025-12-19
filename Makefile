# Nom de l'exécutable
EXEC = leaks

# Fichiers source
SRCS = leaks.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Le compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -std=c11

# Options de liaison
LDFLAGS = -lm
	
histosrc: $(OBJS) biblio.h
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)
	
historeal: $(OBJS) biblio.h
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)
	
histoall: $(OBJS) biblio.h
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)
	
leaks: $(OBJS) biblio.h
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)
	
# Nettoyage des fichiers objets
clean:
	rm -f $(OBJS) $(EXEC)

# Force la recompilation complète
rebuild: clean all
