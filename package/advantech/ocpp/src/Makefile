
ODIR=obj
FSRC=src

#CC=/home/nimish/buildroot/buildroot-at91/sam9x60-ek/host/bin/arm-buildroot-linux-gnueabi-gcc

LIBS := -lpthread -lm -lsqlite3 -locpp1.6

_APPOBJ = \
main.o



APPOBJ = $(patsubst %,$(ODIR)/%,$(_APPOBJ))


all: ocpp1.6_WD

ocpp1.6_WD: $(OBJ) $(APPOBJ)
	$(TARGET_CC) -o $@ $(APPOBJ) $(LIBS) -L lib


$(ODIR)/%.o: $(FSRC)/%.c
	$(TARGET_CC) -c -o $@ $<  -I include 

clean:
	rm -rf $(ODIR)/*.o $(EXEDIR)/ocpp1.6_WD

