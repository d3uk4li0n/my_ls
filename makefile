CC=gcc
CFLAGS+=-Wall -Wextra -Werror -g3 -fsanitize=address
DEPS+=include/my_ls.h include/utils.h include/sort.h
OBJ+=src/my_ls.o
TARGET=my_ls

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

.PHONY: all clean fclean re
clean:
	rm -f src/*.o

fclean: clean 
	rm $(TARGET)

re: fclean all
