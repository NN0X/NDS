CXX = g++
CXXFLAGS = -Isource -O3
SRCDIR = examples
BUILDDIR = build
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
TARGETS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%,$(SOURCES))

all: $(TARGETS)

$(BUILDDIR)/%: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< source/nds.cpp -o $@

clean:
	rm -f $(BUILDDIR)/*