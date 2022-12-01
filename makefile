CC=gcc
DEPS+=include/my_ls.h include/utils.h include/sort.h
OBJ+=src/my_ls.o
CFLAGS+=-Wall -Wextra -Werror -g3 -fsanitize=address
TARGET+=my_ls

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

.PHONY: all clean fclean re
clean:
	rm -f src/*.o

fclean: clean 
	rm -rf $(TARGET)

re: fclean all