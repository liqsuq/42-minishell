NAME := minishell
TOKSRC := $(addprefix tokenize/, \
	tokenize.c tokenize_operator.c tokenize_word.c tokenutils.c)
PARSRC := $(addprefix parse/, \
	parse.c nodeutils.c)
EXPSRC := $(addprefix expand/, \
	expand.c expand_variable.c expand_parameter.c \
	expand_word.c expand_quote.c expand_heredoc.c)
EXESRC := $(addprefix execute/, \
	execute.c find_path.c argvutils.c)
REDSRC := $(addprefix redirect/, \
	redirect.c)
PIPSRC := $(addprefix pipeline/, \
	pipeline.c)
BLTSRC := $(addprefix builtin/, \
	builtin_echo.c builtin_cd.c builtin_pwd.c builtin_export.c \
	builtin_unset.c builtin_env.c builtin_exit.c)
MSCSRC := $(addprefix misc/, \
	signal.c environ.c envutils.c error.c ft_funcs.c)
SOURCE := main.c \
	$(TOKSRC) $(PARSRC) $(EXPSRC) $(EXESRC) \
	$(REDSRC) $(PIPSRC) $(BLTSRC) $(MSCSRC)
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

$(LFT):
	$(MAKE) -C $(LFTDIR)

all: $(NAME)

clean:
	-$(MAKE) -C $(LFTDIR) clean
	$(RM) $(OBJECT)

fclean: clean
	-$(MAKE) -C $(LFTDIR) fclean
	$(RM) $(NAME)

re: fclean all
