NAME := libft.a
MANSRC := ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
          ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
          ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
          ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
          ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
          ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c \
          ft_putendl_fd.c ft_striteri.c ft_putnbr_fd.c ft_putstr_fd.c
MANOBJ := $(MANSRC:.c=.o)
BONSRC := ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
          ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
          ft_lstmap.c
BONOBJ := $(BONSRC:.c=.o)
PRIDIR := ft_printf
PRISRC := $(addprefix $(PRIDIR)/, ft_printf.c print_number.c print_string.c)
PRIOBJ := $(PRISRC:.c=.o)
GNLDIR := get_next_line
GNLSRC := $(addprefix $(GNLDIR)/, get_next_line.c)
GNLOBJ := $(GNLSRC:.c=.o)
OBJECT := $(MANOBJ) $(BONOBJ) $(PRIOBJ) $(GNLOBJ)
CFLAGS := -Wall -Wextra -Werror -I.
.BONUS := .bonus
.PRINTF := .printf
.GETNL := .getnl

all: $(NAME) bonus printf getnl

$(NAME): $(MANOBJ)
	ar rcs $(NAME) $(MANOBJ)

bonus: $(NAME) $(.BONUS)

$(.BONUS): $(BONOBJ)
	ar rcs $(NAME) $(BONOBJ)
	touch $(.BONUS)

printf: $(NAME) $(.PRINTF)

$(.PRINTF): $(PRIOBJ)
	ar rcs $(NAME) $(PRIOBJ)
	touch $(.PRINTF)

getnl: $(NAME) $(.GETNL)

$(.GETNL): $(GNLOBJ)
	ar rcs $(NAME) $(GNLOBJ)
	touch $(.GETNL)

clean:
	$(RM) $(OBJECT) $(.BONUS) $(.PRINTF) $(.GETNL)

fclean: clean
	$(RM) $(NAME)

re: fclean all
