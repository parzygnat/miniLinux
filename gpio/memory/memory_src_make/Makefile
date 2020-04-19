CC=$(CROSS_COMPILE)gcc
OBJS := main.o button_press.o light_led.o

memory: $(OBJS)
	$(CC) -o memory $(CFLAGS) $(LDFLAGS) $(OBJS) -lgpiod
$(OBJS) : %.o : %.c
	$(CC) -c $(CFLAGS) -lgpiod $< -o $@ 
