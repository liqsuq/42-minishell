NAME := minishell
TOKSRC := $(addprefix tokenize/, tokenize.c tokenutils.c)
PARSRC := $(addprefix parse/, parse.c nodeutils.c)
EXPSRC := $(addprefix expand/, expand.c expand_variable.c)
EXESRC := $(addprefix execute/, execute.c argvutils.c pathutils.c)
REDSRC := $(addprefix redirect/, redirect.c)
PIPSRC := $(addprefix pipeline/, pipeline.c)
MSCSRC := $(addprefix misc/, error.c debug.c ft_funcs.c signal.c)
SOURCE := main.c \
	$(TOKSRC) $(PARSRC) $(EXPSRC) $(EXESRC) $(REDSRC) $(PIPSRC) $(MSCSRC)
OBJECT := $(SOURCE:.c=.o)
LFTDIR := libft
LFT := $(LFTDIR)/libft.a
CFLAGS := -Wall -Wextra -Werror -I. -I$(LFTDIR)
LDLIBS := -lreadline

ifeq ($(shell uname), Darwin)
	RLDIR := $(shell brew --prefix readline)
	CFLAGS += -I$(RLDIR)/include
	LDFLAGS += -L$(RLDIR)/lib
endif

$(NAME): $(LFT) $(OBJECT)
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
