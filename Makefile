NAME := minishell
TOKSRC := $(addprefix tokenize/, tokenize.c tokenutils.c)
PARSRC := $(addprefix parse/, parse.c nodeutils.c)
EXPSRC := $(addprefix expand/, expand.c)
REDSRC := $(addprefix redirect/, redirect.c reset_redirect.c)
ERRSRC := $(addprefix error/, error.c)
SOURCE := main.c \
					interpret.c \
					search_path.c \
					debug_print.c \
					pipeline/pipe.c \
					execution/exec.c \
					$(TOKSRC) $(PARSRC) $(EXPSRC) $(REDSRC) $(ERRSRC)
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
