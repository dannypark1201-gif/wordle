# ─────────────────────────────────────────
#  Makefile for MinGW (Windows)
#  Usage:
#    mingw32-make        → build
#    mingw32-make clean  → remove build files
# ─────────────────────────────────────────

CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
TARGET   = wordle.exe
SRCS     = main.cpp Loader.cpp WordBank.cpp Evaluator.cpp Display.cpp WordleGame.cpp
OBJS     = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q *.o $(TARGET) 2>nul || true
