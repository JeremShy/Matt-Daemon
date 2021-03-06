SRC_NAME =	main.cpp \
			Tintin_reporter.cpp \
			Matt_Exception.cpp \
			get_next_line.cpp

INC_PATH = ./includes
OBJ_PATH = ./obj/

NAME = Matt_daemon

CC = clang++

CFLAGS = -Wall -Werror -Wextra

SRC_PATH = ./srcs/

OBJ_PATH = ./obj/

OBJ_NAME = $(SRC_NAME:.cpp=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all : $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $< -g

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(INC) $^ -o $@

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
