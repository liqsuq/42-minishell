SOURCE := $(wildcard *.c)
OBJECT := $(SOURCE:%.c=%.o)
BINARY := $(SOURCE:%.c=%)
CFLAGS := -Wall -Wextra -march=native
LDLIBS := -lreadline
.PHONY: all clean wipeout
all: $(BINARY)
clean:
	$(RM) $(OBJECT) $(BINARY)
wipeout:
	$(RM) $(SOURCE) $(OBJECT) $(BINARY)
