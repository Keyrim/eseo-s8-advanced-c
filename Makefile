# Ajout de variables

BIN_DIR = bin
EXEC = $(BIN_DIR)/prog.elf
OBJ_DIR = obj

CC = gcc
LD = gcc

CCFLAGS = -Wall
CCFLAGS += -g 	# Pour activer les points d'arrêt dans le deboger
LDFLAGS = -lm

RM = rm -f

SRC= $(wildcard *.c)
OBJ= $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

# Crée les dossiers nécessaires
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Compilation rules
all: $(EXEC)

$(EXEC): $(OBJ)
	$(LD) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY:clean

# Clean the project
clean:
	$(RM) $(OBJ_DIR)/*.o $(EXEC)

run: $(EXEC)
	./$(EXEC)

start:
	./$(EXEC)


