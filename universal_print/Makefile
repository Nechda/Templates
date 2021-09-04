CXX0 = g++
CXX1 = clang++

CXX0_exist := $(shell which $(CXX0) 2>/dev/null)
CXX1_exist := $(shell which $(CXX1) 2>/dev/null)

.PHONY: test
.SILENT: test
test:
ifdef CXX0_exist
	echo "Compiling by" $(CXX0)
	$(CXX0) -DTEST main.cpp 
	./a.out > out
	diff out t/answers || (echo "GCC comparison test fail" && exit 1)
endif

ifdef CXX1_exist
	echo "Compiling by" $(CXX1)
	$(CXX1) -DTEST main.cpp 
	./a.out > out
	diff out t/answers || (echo "Clang comparison test fail" && exit 1)
endif

	rm a.out out || @echo

	echo "Test successfully finished"

