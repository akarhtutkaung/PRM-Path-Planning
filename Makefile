CXX=g++
CXXFLAGS = -std=c++17 -g
ROOT_DIR = .
BUILD_DIR = $(ROOT_DIR)/build

INCLUDES = -Iinclude		# header files
SOURCES = $(shell find src -name '*.cpp')			# find the files that ends with .cc
OBJFILES = $(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))	# call object file target to compile
APP_NAME = Voronoi
EXEFILE = $(ROOT_DIR)/build/$(APP_NAME)

all: $(EXEFILE)

# Applicaiton Targets:
$(EXEFILE): $(OBJFILES)
	$(CXX) $(CXXFLAGS) $(OBJFILES) -o $@

# Object File Targets:
$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	cat config/drawAll.m > build/drawAll.m
	cat config/drawPathOnly.m > build/drawPathOnly.m

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(EXEFILE)