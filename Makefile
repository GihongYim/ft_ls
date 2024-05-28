NAME = ft_ls
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./libft/
LIBFT_NAME = libft.a
LIBFT=$(LIBFT_DIR)$(LIBFT_NAME)
INCLUDE=-I ./libft
AR = AR
ARFLAGS = rcs
RM = rm -f
SRCS = ft_ls.c
OBJ_DIR = ./obj
OBJS=$(SRCS:.c=.o)

$(NAME) : $(LIBFT) $(OBJ_DIR)/$(OBJS)
	cp $(LIBFT) $(LIBFT_NAME)
	$(CC) $(OBJ_DIR)/$(OBJS) -o $(NAME) $(LIBFT)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT) :
	make -C $(LIBFT_DIR) all


all : $(NAME)

clean :
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR) $(LIBFT_NAME)

fclean : clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re : 
	make fclean
	make all

.PHONY: all clean fclean re bonus