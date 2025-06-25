CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

TARGET = cub3D
TARGET_B = cub3D_B
SRC = RayCasting/cub3d.c libft_used/ft_split.c libft_used/ft_strjoin.c libft_used/ft_strlen.c libft_used/ft_lstadd_back.c libft_used/ft_lstclear.c \
	 libft_used/ft_lstnew.c parsing/malloc.c libft_used/ft_strncmp.c parsing/main.c parsing/map.c libft_used/ft_putstr_fd.c \
	 get_next_line.c get_next_line_utils.c libft_used/ft_atoi.c libft_used/ft_strtrim.c parsing/validate_configuration_lines.c \
	 parsing/extract_number.c parsing/check_xpm.c parsing/map_section.c parsing/validate_configuration_lines2.c parsing/map_section2.c \
	 parsing/validate_configuration_lines3.c

SRC_B = RayCasting/cub3d_bonus.c libft_used/ft_split.c libft_used/ft_strjoin.c libft_used/ft_strlen.c libft_used/ft_lstadd_back.c libft_used/ft_lstclear.c \
	 libft_used/ft_lstnew.c parsing/malloc.c libft_used/ft_strncmp.c parsing/main.c parsing/map.c libft_used/ft_putstr_fd.c \
	 get_next_line.c get_next_line_utils.c libft_used/ft_atoi.c libft_used/ft_strtrim.c parsing/validate_configuration_lines.c \
	 parsing/extract_number.c parsing/check_xpm.c parsing/map_section.c parsing/validate_configuration_lines2.c parsing/map_section2.c \
	 parsing/validate_configuration_lines3.c


OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)
MINILIBX = minilibx-linux/libmlx.a

all: $(TARGET) clean

bonus: $(TARGET_B) clean

$(TARGET): $(OBJ) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) $(MINILIBX) -o $(TARGET) -lm -lXext -lX11

$(TARGET_B): $(OBJ_B) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ_B) $(MINILIBX) -o $(TARGET_B) -lm -lXext -lX11

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_B)

fclean: clean
	rm -rf $(TARGET)
	rm -rf $(TARGET_B)

re: fclean all
.PHONY: all clean fclean re
