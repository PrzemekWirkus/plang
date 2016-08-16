CPP       := g++
CPP_FLAGS := -Wall -g -O2 --std=c++11
LD_FLAGS  :=
CPP_FILES := $(filter-out src/main.cpp, $(wildcard src/*.cpp))
OBJ_FILES := $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
INCLUDES  := -I./include

TEST_CPP_FILES := $(wildcard test/*.cpp)
TEST_OBJ_FILES := $(addprefix build/,$(notdir $(TEST_CPP_FILES:.cpp=.o)))
TEST_INCLUDES := -I./test


all: dirs parser

parser: $(OBJ_FILES) build/main.o
	$(CPP) $(LD_FLAGS) $^ -o bin/plang

test: dirs test_suite

test_suite: $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CPP) $(LD_FLAGS) $^ -o bin/test_suite

.PHONY: clean dirs all test

clean:
	@echo Cleaning...
	rm -rf bin/*
	rm -rf build/*.o

dirs:
	mkdir -p bin/
	mkdir -p build/

build/%.o: src/%.cpp
	$(CPP) $(CPP_FLAGS) $(INCLUDES) -c -o $@ $<

build/%.o: test/%.cpp
	$(CPP) $(CPP_FLAGS) $(INCLUDES) $(TEST_INCLUDES) -c -o $@ $<

