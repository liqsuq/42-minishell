NAME := minishell
SOURCE := main.c
OBJECT := $(SOURCE:.c=.o)
LFTDIR := libft
LFT := $(LFTDIR)/libft.a
CFLAGS := -Wall -Wextra -Werror -I$(LFTDIR)
LDLIBS := -lreadline

$(NAME): $(LFT) $(MLX) $(OBJECT)
	$(LINK.o) $(OBJECT) $(LFT) $(LDLIBS) -o $@

$(LFT): | $(LFTDIR)
	$(MAKE) -C $(LFTDIR)

$(LFTDIR):
	git clone https://github.com/liqsuq/libft

all: $(NAME)

clean:
	-$(MAKE) -C $(LFTDIR) clean
	$(RM) $(OBJECT)

fclean: clean
	$(RM) -r $(LFTDIR)
	$(RM) $(NAME)

re: fclean all
