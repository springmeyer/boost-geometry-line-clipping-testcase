# first inherit from env
CXX := $(CXX)
CXXFLAGS := $(CXXFLAGS)
LDFLAGS := $(LDFLAGS)

COMMON_FLAGS := -Wextra -pedantic -fvisibility-inlines-hidden -std=c++11 $(WARNING_FLAGS) -O0 -g -DDEBUG

OS:=$(shell uname -s)
ifeq ($(OS),Darwin)
    CXXFLAGS += -stdlib=libc++
    LDFLAGS += -stdlib=libc++
endif

all: test

./.mason:
	git clone --depth 1 https://github.com/mapbox/mason.git ./.mason && export MASON_DIR=$$(pwd)/.mason && ./.mason/mason install boost 1.57.0 && ./.mason/mason link boost 1.57.0;

./bg-test: ./.mason
	clang++ -o bg-test bg-testcase.cpp -Imason_packages/.link/include/ -std=c++11 -O0 -DDEBUG;

test: ./bg-test
	./bg-test

clean:
	rm -f ./bg-test

.PHONY: test

