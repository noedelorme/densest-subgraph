###################################################################
# A simple and powerfull Makefile to run C++
# 
# - Specify in EXECUTABLE the name of your project
# - Specify in SRCDIR the name of the source directory
# - Specify in BUILDDIR the name of the build directory
# - Use "make" to compile your project
# - Use "make run" to compile and run your project
# - It searches automatically source files (in SRCDIR)
# - It Outs builded files to the build directory (in BUILDDIR)

EXECUTABLE = densestsubgraph
SRCDIR = ./src
BUILDDIR = ./build


###################################################################
SRCS = $(shell cd ./src && find ./ -name "*.cpp")
OBJS = $(addprefix ./build/, $(addsuffix .o , $(basename $(SRCS))))
DEPS = $(OBJS:.o=.d)

INC_DIRS = $(shell find $(SRCDIR) -type d)
INC_FLAGS = $(addprefix -I,$(INC_DIRS))
CPPFLAGS = $(INC_FLAGS) -MMD -MP
CXX = g++

$(BUILDDIR)/$(EXECUTABLE): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

run: $(BUILDDIR)/$(EXECUTABLE)
	$(BUILDDIR)/$(EXECUTABLE)

clean:
	$(RM) -r $(BUILDDIR)
###################################################################