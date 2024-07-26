.SECONDEXPANSION:
TARGETS := release debug
.PHONY: $(TARGETS) all

export TERM ?= xterm-256color

all: $(TARGETS)

compile_commands.json:
	bear -- $(MAKE) -B all clean

EXE := graph_interface
SRCS := $(shell find src -type f -name '*.cpp')
OBJS := $(SRCS:src/%.cpp=%.o)

CXXFLAGS = -std=c++2b -Wall -Wextra -Wshadow -Wconversion -Wsign-conversion -Wunused-parameter -Wno-long-long -pedantic
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

clean:
	rm -vr $(TARGETS)

%/:
	mkdir -vp $@