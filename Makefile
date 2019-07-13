# Tuning
CXXFLAGS += \
    -g -O0
    # -O

SUFFIXES += .d
CXXFLAGS += \
    -std=c++14 -Wall -Wpedantic -Wextra -Wduplicated-cond \
    -Wlogical-op -Wnull-dereference \
    -Wdouble-promotion -Wshadow -Wformat=2 \
    -Wold-style-cast -Wuseless-cast

PROGRAMS = filetree
SOURCES = filetree.cpp
LIB_OBJECTS = 

Q_ = @
ifdef VERBOSE
    Q_ =
endif

DEPFILES:=$(patsubst %.cpp,%.d,$(SOURCES))

all: $(PROGRAMS) $(DEPFILES)

%: %.o $(LIB_OBJECTS)
	@echo Linking $@
	$(Q_)$(LINK.cc) $(LDFLAGS) $@.o $(LIB_OBJECTS) $(LDLIBS) -o $@

%.d: %.cpp
	@echo Computing dependencies $@
	$(Q_)$(CXX) $(CXXFLAGS) -MM -MT '$(patsubst %.cpp,%.o,$<)' $< -MF $@

%.o: %.cpp
	@echo Compiling $@
	$(Q_)$(CXX) $(CXXFLAGS) -c $< -o $@

install: $(PROGRAMS)
	cp $(PROGRAMS) $(HOME)/bin
clean:
	$(RM) *.o *.d $(PROGRAMS)

.PHONY: all install clean

-include $(DEPFILES)
