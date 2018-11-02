
NAME = avm

SRCS =  src/AOperand.cpp \
		src/Factory.cpp \
		src/DivisionByZero.cpp \
		src/Reader.cpp \
		main.cpp
		#src/Caster.cpp \
		

INCLUDES = -I includes/ 

OBJ = $(SRCS:%.cpp=%.o)

CC = clang++

FLAGS = -Wall -Wextra $(INCLUDES)

%.o: %.cpp
	$(CC) -c -o $@ $< $(FLAGS)

all: $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re