CC:=g++

CFLAGS:=-c -std=c++11 -Wall
LFLAGS:=-lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR:=src
BIN_DIR:=bin

SOURCES:=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS:=$(patsubst %.cpp,%.o,$(SOURCES))
DEPS:=$(OBJECTS:.o=.d)

BIN:=$(BIN_DIR)/pong

all: $(BIN)

$(BIN): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN) $(OBJECTS) $(LFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	-rm -rf $(OBJECTS) $(DEPS) $(BIN_DIR)

.PHONY: rebuild

rebuild: clean all

-include $(DEPS)
