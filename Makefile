CC=gcc

SRCDIR=src/
OBJDIR=obj/
OUTDIR=bin/

SERVERSRCDIR=$(SRCDIR)server/
CLIENTSRCDIR=$(SRCDIR)client/
COMMONSRCDIR=$(SRCDIR)common/

INCLUDES=-I$(COMMONSRCDIR)

SERVEROBJDIR=$(SERVERSRCDIR)$(OBJDIR)
CLIENTOBJDIR=$(CLIENTSRCDIR)$(OBJDIR)
COMMONOBJDIR=$(COMMONSRCDIR)$(OBJDIR)

SERVERSRC=$(wildcard $(SERVERSRCDIR)*.c)
CLIENTSRC=$(wildcard $(CLIENTSRCDIR)*.c)
COMMONSRC=$(wildcard $(COMMONSRCDIR)*.c)

SERVEROUTNAME=server
CLIENTOUTNAME=client

all: dirs $(patsubst %.c,%.o,$(COMMONSRC)) $(patsubst %.c,%.o,$(SERVERSRC)) $(patsubst %.c,%.o,$(CLIENTSRC))
	$(CC) -o $(OUTDIR)$(SERVEROUTNAME).out $(SERVEROBJDIR)*.o $(COMMONOBJDIR)*.o -lpthread
	$(CC) -o $(OUTDIR)$(CLIENTOUTNAME).out $(CLIENTOBJDIR)*.o $(COMMONOBJDIR)*.o -lpthread
clean:
	rm -r -f $(OUTDIR)
	rm -r -f $(SERVEROBJDIR)
	rm -r -f $(CLIENTOBJDIR)
	rm -r -f $(COMMONOBJDIR)
dirs:
	mkdir -p $(OUTDIR)
	mkdir -p $(SERVEROBJDIR)
	mkdir -p $(CLIENTOBJDIR)
	mkdir -p $(COMMONOBJDIR)
%.o: %.c
	$(CC) $(INCLUDES) -g -c -MD $< -o $(@D)/$(OBJDIR)$(@F)

include $(wildcard $(SERVEROBJDIR)*.d)
include $(wildcard $(CLIENTOBJDIR)*.d)
include $(wildcard $(COMMONOBJDIR)*.d)
