FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

CXX = g++

SOURCES = main.cpp compare.cpp io.cpp unit_test.cpp solve.cpp
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

all: square.exe

%.o: %.cpp
	$(CXX) -c $^ -o $@ $(FLAGS)

square.exe: $(OBJECTS)
	$(CXX) $^ -o $@

.PHONY: clean

clean:
	rm *.o
	rm square.exe