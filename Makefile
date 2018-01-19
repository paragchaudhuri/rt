.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen

######################################
# Project Name (generate executable with this name)
TARGET = rt

# Project Paths
PROJECT_ROOT:=.
SRCDIR := $(PROJECT_ROOT)/src
INCDIR := $(PROJECT_ROOT)/include/rt
DOCDIR := $(PROJECT_ROOT)/doc
EXTDIR := $(PROJECT_ROOT)/ext

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
EIGEN_INCLUDE=/usr/local/include/eigen3
TINYXML2_INCLUDE=$(EXTDIR)/tinyxml2
FILESYSTEM_INCLUDE=$(EXTDIR)/filesystem
EXTMODULES=$(EXTDIR)/tinyxml2

# Compiler and Linker flags
LDFLAGS=-L/usr/local/lib 

CPPFLAGS=-I$(EIGEN_INCLUDE) -I$(TINYXML2_INCLUDE) -I$(FILESYSTEM_INCLUDE) -I$(INCDIR) 
CPPFLAGS+=-O3 -Wall -std=c++11

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"

######################################

SRCS:=$(wildcard $(SRCDIR)/*.cpp)
include $(patsubst %,%/makefile.mk,$(EXTMODULES))
OBJS:=$(patsubst %.cpp,%.o,$(filter %.cpp,$(SRCS)))
DEPS:=$(patsubst %.cpp,%.d,$(filter %.cpp,$(SRCS)))

.PHONY: all doc clean distclean

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include -include $(OBJS:.o=.d)

$(OBJS): %.o : %.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"

clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf *~ $(OBJS) $(DEPS) $(SRCDIR)/*~
	@$(ECHO) "Done"

distclean: clean
	@$(RM) -rf $(TARGET) $(DOCDIR)/html scenes/*.ppm