
PLUGIN_LIBRARY_NAME := vamp-test-plugin

PLUGIN_SOURCES 	    := VampTestPlugin.cpp plugins.cpp

PLUGIN_HEADERS 	    := VampTestPlugin.h

SRC_DIR		:= .

CFLAGS		:= $(ARCHFLAGS) $(CFLAGS)
CXXFLAGS	:= $(CFLAGS) -I. -I$(VAMPSDK_DIR) $(CXXFLAGS)

LDFLAGS		:= $(ARCHFLAGS) $(LDFLAGS)
PLUGIN_LDFLAGS	:= $(LDFLAGS) $(PLUGIN_LDFLAGS)

VAMPSDK_DIR	?= ../vamp-plugin-sdk
PLUGIN_EXT	?= .so
CXX 		?= g++
CC 		?= gcc

PLUGIN 		:= $(PLUGIN_LIBRARY_NAME)$(PLUGIN_EXT)

PLUGIN_OBJECTS 	:= $(PLUGIN_SOURCES:.cpp=.o)
PLUGIN_OBJECTS 	:= $(PLUGIN_OBJECTS:.c=.o)

all: 		$(PLUGIN)

$(PLUGIN): 	$(PLUGIN_OBJECTS) 
		$(CXX) -o $@ $^ $(PLUGIN_LDFLAGS)

$(PLUGIN_OBJECTS): $(PLUGIN_HEADERS)

clean:
	rm -f $(PLUGIN_OBJECTS)

distclean:	clean
	rm -f $(PLUGIN)

depend:
	makedepend -Y -fMakefile.inc $(PLUGIN_SOURCES) $(PLUGIN_HEADERS)

# DO NOT DELETE

VampTestPlugin.o: VampTestPlugin.h
plugins.o: VampTestPlugin.h
