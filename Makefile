NAME = miniRT
SRCS_DIR = srcs
SRCS += $(SRCS_DIR)/amb.c
SRCS += $(SRCS_DIR)/bmp.c
SRCS += $(SRCS_DIR)/cam.c
SRCS += $(SRCS_DIR)/cy.c
SRCS += $(SRCS_DIR)/err.c
SRCS += $(SRCS_DIR)/keycon.c
SRCS += $(SRCS_DIR)/light.c
SRCS += $(SRCS_DIR)/main.c
SRCS += $(SRCS_DIR)/pl.c
SRCS += $(SRCS_DIR)/ray.c
SRCS += $(SRCS_DIR)/raytrace.c
SRCS += $(SRCS_DIR)/read_rtfile.c
SRCS += $(SRCS_DIR)/res.c
SRCS += $(SRCS_DIR)/rgb.c
SRCS += $(SRCS_DIR)/rgb2.c
SRCS += $(SRCS_DIR)/sp.c
SRCS += $(SRCS_DIR)/sq.c
SRCS += $(SRCS_DIR)/tr.c
SRCS += $(SRCS_DIR)/vec.c
SRCS += $(SRCS_DIR)/vec2.c
SRCS += $(SRCS_DIR)/win.c
SRCS += $(SRCS_DIR)/utils/ft_atoi.c
SRCS += $(SRCS_DIR)/utils/ft_isdigit.c
SRCS += $(SRCS_DIR)/utils/ft_strdup.c
SRCS += $(SRCS_DIR)/utils/ft_itoa.c
SRCS += $(SRCS_DIR)/utils/ft_lst_add_back_new.c
SRCS += $(SRCS_DIR)/utils/ft_lstadd_back.c
SRCS += $(SRCS_DIR)/utils/ft_lstlast.c
SRCS += $(SRCS_DIR)/utils/ft_lstnew.c
SRCS += $(SRCS_DIR)/utils/ft_putendl_fd.c
SRCS += $(SRCS_DIR)/utils/ft_putstr_fd.c
SRCS += $(SRCS_DIR)/utils/ft_split.c
SRCS += $(SRCS_DIR)/utils/ft_strjoin.c
SRCS += $(SRCS_DIR)/utils/ft_strlen.c
SRCS += $(SRCS_DIR)/utils/ft_strncmp.c
SRCS += $(SRCS_DIR)/utils/get_next_line_utils.c
SRCS += $(SRCS_DIR)/utils/get_next_line.c
SRCS += $(SRCS_DIR)/utils2/ft_add_data4dlst.c
SRCS += $(SRCS_DIR)/utils2/ft_atof.c
SRCS += $(SRCS_DIR)/utils2/ft_ch_dir_vec.c
SRCS += $(SRCS_DIR)/utils2/ft_digit_check.c
SRCS += $(SRCS_DIR)/utils2/ft_new_dlist.c
SRCS += $(SRCS_DIR)/utils2/ft_poipoi_strlen.c
SRCS += $(SRCS_DIR)/utils2/ft_split_counter.c
SRCS += $(SRCS_DIR)/utils2/ft_str2vec.c
SRCS += $(SRCS_DIR)/utils2/ft_strchr_counter.c

OBJS = $(SRCS:.c=.o)
INCLUDE = -I./includes

MLX		= minilibx-linux
all: $(NAME)
LIBS = -lXext -lX11 -L -lft libmlx_Linux.a

CC = gcc -Wall -Wextra -Werror
RM = rm -f

$(NAME): $(MLX) $(OBJS)
	@ $(MAKE) -C ./minilibx-linux > /dev/null 2>&1
	cp ./minilibx-linux/libmlx_Linux.a .
	$(CC) $(INCLUDE) $(OBJS) -L. -L.minilibx-linux -lmlx_Linux $(LIBS) -lm -o $(NAME)
$(MLX) :
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX)

.c.o:
	$(CC) $(INCLUDE) -c $< -o $@
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
	$(RM) -r minilibx-linux
	$(RM) -r libmlx_Linux.a
re: fclean all

.PHONY: all clean fclean re .c.o
