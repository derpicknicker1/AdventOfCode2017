DAYS := 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
FNAMES := $(addprefix advent,$(DAYS))
SOURCE := $(addsuffix .c,$(FNAMES)) helper.c
CFILES := main.c $(addprefix src/,$(SOURCE))
INCLUDES := -I "src/"

PROG := main
CFLAGS := $(INCLUDES) -O3
MAP_FILE :=$(PROG).map
LDFLAGS :=  -Xlinker -Map=$(MAP_FILE)

CC := gcc
LD := ld

OBJECTS := $(CFILES:.c=.o)
.DEFAULT_GOAL := all

%.o : %.c
	@echo 'Building file: $<'
	@$(CC) -c $(CFLAGS) -o $@ $< 

$(PROG) : $(OBJECTS)
	@echo 'Linking: $@'
	@$(CC) $(LDFLAGS) -o $@ $^ 

all: $(PROG)

clean :
	rm -f $(PROG)
	rm -f $(OBJECTS)