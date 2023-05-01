# New Makefile that automatically depends itself

IFLAGS =
DFLAGS =
CXX = gcc
CC  = $(GCC)
GCC = gcc
LD  = $(CXX)

LIBS =

WFLAGS = -Wall
SYMFLAGS = -g

PROFILE = #-pg
OPTFLAGS = #-O
CFLAGS = $(OPTFLAGS) $(PROFILE) $(WFLAGS) $(IFLAGS) $(SYMFLAGS)
CXXFLAGS = $(CFLAGS)
CPPFLAGS = $(IFLAGS) $(DFLAGS)
LDFLAGS = $(PROFILE) -g

PROGRAM = proj3
CXXSRCS = $(shell ls *.c)

SRCS = $(CXXSRCS)
OBJS = $(CXXSRCS:.c=.o)

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $(OBJS) $(LIBS)

test: $(PROGRAM)
	./$(PROGRAM)

clean:
	-rm -f $(OBJS) $(PROGRAM)

tidy:
	-rm -f *.BAK *.bak *.CKP

undepend:
	-rm -f $(OBJS:%.o=.%.d)

spotless: tidy clean undepend

# auto depend stuff for GNU make only
depend: undepend
	@echo ""
	@echo "Dependences are handled automatically, just \"make\""

ifneq ($(strip $(CSRCS)),)
.%.d: %.c
	$(SHELL) -ec '$(GCC) -MM $(CPPFLAGS) $< > $@'

include $(CSRCS:%.c=.%.d)
endif

ifneq ($(strip $(CXXSRCS)),)
.%.d: %.c
	$(SHELL) -ec '$(GCC) -MM $(CPPFLAGS) $< > $@'

include $(CXXSRCS:%.c=.%.d)
endif
