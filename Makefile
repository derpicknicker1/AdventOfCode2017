SOURCE := advent1.c advent2.c advent3.c advent4.c advent5.c advent6.c advent8.c advent9.c advent10.c advent12.c advent13.c helper.c
CFILES := main.c $(addprefix src/,$(SOURCE))
INCLUDES := -I "src/"

PROG := main
CFLAGS := $(INCLUDES) -O0
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