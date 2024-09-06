all: BlyncLight

CC       ?= gcc 
CFLAGS   ?= -Wall -g -pthread -std=c99 -no-pie

COBJS     = BlyncLight.o
OBJS      = $(COBJS)
LIBS      = EmbravaApi/libembravaapi.a -lusb-1.0
INCLUDES ?= -I./


BlyncLight: $(OBJS) 
		$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LIBS) -o BlyncLight

$(COBJS): %.o: %.c	
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJS) BlyncLight

.PHONY: clean
