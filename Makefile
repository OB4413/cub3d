NAME = cub3D

NAME_BONUS = cub3D_bonus

SRC = mandatory/main.c mandatory/cub3d.c\
	  mandatory/get_next_line/get_next_line.c \
	  mandatory/get_next_line/get_next_line_utils.c \
	  mandatory/parsing/parse_file.c \
	  mandatory/parsing/load_config.c \
	  mandatory/parsing/load_config_utils.c \
	  mandatory/parsing/load_map.c \
	  mandatory/parsing/check_map.c \
	  mandatory/utils/ft_memset.c \
	  mandatory/utils/ft_strtrim.c \
	  mandatory/utils/ft_putstr_fd.c \
	  mandatory/utils/ft_strncmp.c \
	  mandatory/utils/ft_strcmp.c \
	  mandatory/utils/ft_split.c \
	  mandatory/utils/ft_split_ws.c \
	  mandatory/utils/ft_isspace.c \
	  mandatory/utils/ft_isdigit.c \
	  mandatory/utils/ft_atoi.c \

BONUS_SRC = bonus/main.c bonus/cob3b_bonus.c \
	  bonus/get_next_line/get_next_line.c \
	  bonus/get_next_line/get_next_line_utils.c \
	  bonus/parsing/parse_file.c \
	  bonus/parsing/load_config.c \
	  bonus/parsing/load_config_utils.c \
	  bonus/parsing/load_map.c \
	  bonus/parsing/check_map.c \
	  bonus/utils/ft_memset.c \
	  bonus/utils/ft_strtrim.c \
	  bonus/utils/ft_putstr_fd.c \
	  bonus/utils/ft_strncmp.c \
	  bonus/utils/ft_strcmp.c \
	  bonus/utils/ft_split.c \
	  bonus/utils/ft_split_ws.c \
	  bonus/utils/ft_isspace.c \
	  bonus/utils/ft_isdigit.c \
	  bonus/utils/ft_atoi.c \

OBJS = $(SRC:.c=.o)

BONUS_OBJS = $(BONUS_SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

MLX = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

RM = rm -f

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

$(NAME_BONUS): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(MLX) -o $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)
fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
