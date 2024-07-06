MAKEFLAGS+=--no-builtin-rules --no-builtin-variables

CXXFLAGS=-O0 -g -Wall -MMD -Wno-unused-function
CXXFLAGS+=-Iinclude
CFLAGS=$(CXXFLAGS)
?CC=gcc
?CXX=g++

SRC_DIR 	= src
BIN_DIR		= bin
SRC 		= $(wildcard $(SRC_DIR)/*.cpp)
SRC			+= $(wildcard $(SRC_DIR)/imgui/*.cpp)
SRCC		= $(wildcard $(SRC_DIR)/*.c)
OUTPUT		= $(BIN_DIR)/gl

ifeq ($(CC),x86_64-w64-mingw32-gcc)
CPPFLAGS=-DCALLBACK=__stdcall
LDFLAGS=-Llibs/mingw
LDLIBS=-lglfw -lmingw32 -lgdi32 -lglu32
else
LDFLAGS=-Llibs/linux
LDLIBS=-lglfw -lGL -lGLU -ldl
endif

OBJS=$(SRC:%.cpp=%.o) $(SRCC:%.c=%.o)
DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: $(OUTPUT)

-include $(DEPS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(CPPFLAGS)

$(OUTPUT): $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^ $(LDLIBS)

clean:
	rm -f $(OBJS) $(DEPS) $(OUTPUT)
