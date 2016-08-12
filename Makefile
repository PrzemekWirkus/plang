CPP       := g++
CPP_FLAGS := -Wall -g -O2
LD_FLAGS  :=
CPP_FILES := $(filter-out src/main.cpp, $(wildcard src/*.cpp))
OBJ_FILES := $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
INCLUDES  := -I./include

all: $(OBJ_FILES) build/main.o
	$(CPP) $(LD_FLAGS) $^ -o build/plang

.PHONY: clean

clean:
	@echo Cleaning...
	rm -f $(OBJ_FILES) build/plang

build/%.o: src/%.cpp
	$(CPP) $(CPP_FLAGS) $(INCLUDES) -c -o $@ $<

