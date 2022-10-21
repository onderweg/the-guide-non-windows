CFLAGS= 

WFLAGS_LIB=-Wall -Wno-int-conversion
WFLAGS_TEST=-Wall
WFLAGS_UTIL=-Wno-format

OBJ_LIB=libguide.so
OBJ_UTIL=gdeutil

SRC_LIB=$(wildcard src/*.c)
SRC_UTIL=$(wildcard gdeutil/*.c)

DIR_BUILD=build
DIR_INC=include

# to compile for debug: make DEBUG=1
# to compile for no debug: make
ifeq ($(DEBUG),1)
    DIR_BUILD = build/debug
    CFLAGS += -g -O0
endif

DIR_BUILD_TEST=$(DIR_BUILD)/test
DIR_BUILD_UTIL=$(DIR_BUILD)/gdeutil

all: libguide gdeutil test

libguide: $(SRC_LIB)
	@mkdir -p $(DIR_BUILD)
	$(CC) -shared -fPIC -I$(DIR_INC) -o $(DIR_BUILD)/$(OBJ_LIB) $^ $(CFLAGS) $(WFLAGS_LIB)
.PHONY: libguide

gdeutil: libguide $(SRC_UTIL)
	@mkdir -p $(DIR_BUILD_UTIL)
	$(CC) -I$(DIR_INC) -o $(DIR_BUILD_UTIL)/$(OBJ_UTIL) $(SRC_UTIL) $(CFLAGS) -lguide -L$(DIR_BUILD) $(WFLAGS_UTIL)
.PHONY: gdeutil

test: libguide $(wildcard test/*.c)
	@mkdir -p $(DIR_BUILD_TEST)
	$(CC) -o $(DIR_BUILD_TEST)/read test/read.c -lguide -L$(DIR_BUILD) -I$(DIR_INC) $(CFLAGS) $(WFLAGS_TEST)
	$(CC) -o $(DIR_BUILD_TEST)/write test/write.c -lguide -L$(DIR_BUILD) -I$(DIR_INC) $(CFLAGS) $(WFLAGS_TEST)
.PHONY: test

clean:
	rm -rf build
.PHONY: clean
