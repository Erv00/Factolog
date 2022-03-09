CXX = g++ -I include
CXXFLAGS = -Wall -Wextra -pedantic -Werror -ggdb -std=c++03 $(CMD)
LDFLAGS = -ggdb

SRCS := $(wildcard src/*.cpp)
TEST_SRCS := $(wildcard tests/*.cpp)
TEST_OBJS := $(TEST_SRCS:tests/%.cpp=obj/%.o)
DEPFILES := $(SRCS:src/%.cpp=deps/%.d) $(TEST_SRCS:tests/%.cpp=deps/%.d)
OBJS := $(SRCS:src/%.cpp=obj/%.o)

MAKEDEPEND = g++ -MM -MF deps/$*.d -I include $<
MAKEDEPEND_TEST = g++ -MM -MF deps/$*_test.d -I include $<

# Package for submission
.PHONY: package
package: NeuralNetwork.zip

NeuralNetwork.zip: doc

# Folder for object files
obj:
	mkdir obj

# Folder for dependency files
deps:
	mkdir deps

# Clean artifacts
.PHONY: clean
clean:
	-rm -rf obj
	-rm -rf deps
	-rm -rf doc
	-rm neural

# Rules for object files
obj/%.o: src/%.cpp deps/%.d | obj
	@$(MAKEDEPEND)
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Rule for final executable
neural: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)

# Folder for documentation
doc:
	mkdir doc

# Rule for documentation
.PHONY: documentation
documentation: doc/html pdf

# Rule for html documentation
.PHONY: html
html: doc/html
doc/html: doc $(SRCS) $(wildcard include/*)
	doxygen

# Rule for documentation pdf
.PHONY: pdf
pdf: doc/latex/refman.pdf
doc/latex/refman.pdf: doc/html
	cd doc/latex
	make -C doc/latex -f Makefile

# Rule for test compilation
.PHONY: tests
factoTest: $(TEST_OBJS) $(OBJS)
	$(CXX) $(LDFLAGS) $(TEST_OBJS) $(OBJS) -o factoTest $(LIBS)

$(warn $(TEST_OBJS))

obj/%_test.o: tests/%_test.cpp deps/%_test.d | obj
	@$(MAKEDEPEND_TEST)
	$(CXX) -c $(CXXFLAGS) -Wno-error $< -o $@

# Automatic dependeny wizardry
$(DEPFILES): deps
include $(DEPFILES)