# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

# Project files
TARGET = cub3D
SRC = RayCasting/cub3d.c libft_used/ft_split.c libft_used/ft_strjoin.c libft_used/ft_strlen.c libft_used/ft_lstadd_back.c libft_used/ft_lstclear.c \
	 libft_used/ft_lstnew.c parsing/malloc.c libft_used/ft_strncmp.c parsing/main.c parsing/map.c libft_used/ft_putstr_fd.c \
	 get_next_line.c get_next_line_utils.c libft_used/ft_atoi.c libft_used/ft_strtrim.c parsing/validate_configuration_lines.c \
	 parsing/extract_number.c parsing/check_xpm.c parsing/map_section.c parsing/validate_configuration_lines2.c parsing/map_section2.c \
	 parsing/validate_configuration_lines3.c


OBJ = $(SRC:.c=.o)
MINILIBX = minilibx-linux/libmlx.a

# Rules
all: $(TARGET) banner clean

$(TARGET): $(OBJ) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) $(MINILIBX) -o $(TARGET) -lm -lXext -lX11

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean bye
	rm -rf $(TARGET)

re: fclean all
.PHONY: all clean fclean re banner bye
