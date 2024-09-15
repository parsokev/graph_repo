# Adapted from instructional material provided by Oregon State University
# Date: 9/15/2024
# Utilization/Definition of gprint functionality for debug printing derived from material provided in coursework from CS344 - 2024

.SECONDEXPANSION:
TARGETS := release debug
.PHONY: $(TARGETS) all

all: $(TARGETS)

compile_commands.json:
	bear -- $(MAKE) -B all clean

# Define executable, source file locations and object file generation
EXE := graph_interface
SRCS := $(shell find src -type f -name '*.cpp')
OBJS := $(SRCS:src/%.cpp=%.o)

# Define general and configuration-specific compiler flags
CXXFLAGS = -std=c++20 -Wall -Wextra -Wshadow -Wconversion -Wsign-conversion -Wunused-parameter -Wno-long-long -pedantic
release: CXXFLAGS += -O3 
debug: CXXFLAGS += -g -O0
CPPFLAGS :=
release: CPPFLAGS += -DNDEBUG

# First rule creates definition for path of file copies into target directories
# Second rule defines how exectuable file is compiled with all dependencies, using path outlined in first rule
# Third rule defines how all object files other than executable are compiled with their dependencies, using path outlined in first rule
define build_template = 
$(1): $(1)/$$(EXE) | $(1)/
 
$(1)/$$(EXE): $$(addprefix $(1)/,$$(OBJS)) | $(1)/
	$$(LINK.cpp) $$^ $$(LOADLIBES) $$(LDLIBS) -o $$@

$$(addprefix $(1)/,$$(OBJS)): $(1)/%.o : src/%.cpp | $$(foreach obj,$$(addprefix $(1)/,$$(OBJS)),$$(dir $$(obj)))
	$$(COMPILE.cpp) $$(OUTPUT_OPTION) $$<
endef

# For each directory listed in TARGETS, create and compiles copies of files from source into target directories using rules defined in template
$(foreach target,$(TARGETS),$(eval $(call build_template,$(target))))

# For cleanup
clean:
	rm -vr $(TARGETS)

# Create new directories for both configurations if they do not already exist, and notify user in terminal
%/:
	mkdir -vp $@