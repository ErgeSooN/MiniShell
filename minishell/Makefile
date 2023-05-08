USERNAME = ayaman
NAME = minishell
CFLAGS = $(INCLUDE) -Wall -Werror -Wextra -g
INCLUDE = -IInclude/ -I/Users/$(USERNAME)/goinfre/homebrew/Cellar/readline/8.2.1/include
CC = gcc -g

SRC = $(shell find src -name "*.c")
SRCDIR = $(sort $(dir $(SRC)))
SRCFLS = $(notdir $(SRC))

OUTPREFIX = builds/
OBJ = $(addprefix $(OUTPREFIX), $(SRCFLS:.c=.o))

vpath %.c $(SRCDIR)
$(OUTPREFIX)%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: outfolder $(NAME)
	@echo "Done"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -L /Users/$(USERNAME)/goinfre/homebrew/Cellar/readline/8.2.1/lib -o $(NAME)

outfolder:
	@echo "Building Minishell"
	@if [ ! -d $(OUTPREFIX) ]; then echo "$(OUTPREFIX) folder created."; fi
	@mkdir -p $(OUTPREFIX);
	@echo "Compiling Files..."

clean:
	@echo "Cleaning Objects..."
	@if [ -d $(OUTPREFIX) ]; then rm -rf $(OUTPREFIX); fi

fclean: clean
	@echo "Cleaning Program..."
	@if [ ! -d $(NAME) ]; then rm -rf $(NAME); fi
	@echo "Done"

re: fclean seperate all

seperate:
	@echo "-----------------"

.PHONY:
	all clean fclean re seperate

check:
	@echo "SRC : "
	@echo $(SRC)
	@echo "\nSRCDIR : "
	@echo $(SRCDIR)
	@echo "\nSRCFLS : "
	@echo $(SRCFLS)
	@echo "\nOBJ : "
	@echo $(OBJ)