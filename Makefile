CPP       := g++
CPP_FLAGS := -Wall -g -O2 --std=c++11
LD_FLAGS  :=
CPP_FILES := $(filter-out src/main.cpp, $(wildcard src/*.cpp))
OBJ_FILES := $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
INCLUDES  := -I./include

TEST_CPP_FILES := $(wildcard test/*.cpp)
TEST_OBJ_FILES := $(addprefix build/,$(notdir $(TEST_CPP_FILES:.cpp=.o)))
TEST_INCLUDES := -I./test


all: $(OBJ_FILES) build/main.o
	$(CPP) $(LD_FLAGS) $^ -o build/plang

test: $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CPP) $(LD_FLAGS) $^ -o test/test_suite

.PHONY: clean

clean:
	@echo Cleaning...
	rm -f $(OBJ_FILES) build/plang

build/%.o: src/%.cpp
	$(CPP) $(CPP_FLAGS) $(INCLUDES) -c -o $@ $<

build/%.o: test/%.cpp
	$(CPP) $(CPP_FLAGS) $(INCLUDES) $(TEST_INCLUDES) -c -o $@ $<

