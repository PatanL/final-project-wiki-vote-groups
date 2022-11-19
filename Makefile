CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic $(INCLUDES)
CXX_FLAGS_OPTIMIZED=-std=c++20 -O3 -Wall -Wextra -Werror -pedantic $(INCLUDES)
SRC_INPUTS=src/main.cpp src/graph.cpp
INCLUDES_INPUTS=includes/graph.h
INPUTS=$(SRC_INPUTS) $(INCLUDES_INPUTS)

exec: bin/exec
exec-opt: bin/exec-opt
tests: bin/tests

bin/exec: $(INPUTS)
	${CXX} ${CXX_FLAGS} ${SRC_INPUTS} -o $@

bin/exec-opt: $(INPUTS)
	${CXX} ${CXX_FLAGS_OPTIMIZED} ${SRC_INPUTS} -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec exec-opt

clean:
	rm -fr bin/* obj/*