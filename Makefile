CXX = g++ -I include
CXXFLAGS = -Wall -Wextra -pedantic -Werror -ggdb -std=c++03 $(CMD)
LDFLAGS = -ggdb

SRCS := $(wildcard src/*.cpp)
TEST_SRCS := $(wildcard tests/*.cpp)
TEST_OBJS := $(TEST_SRCS:tests/%.cpp=obj/%.o)
DEPFILES := $(SRCS:src/%.cpp=deps/%.d) $(TEST_SRCS:tests/%.cpp=deps/%.d)
OBJS := $(SRCS:src/%.cpp=obj/%.o)

MAKEDEPEND = g++ -MM -MT "$@" -MF deps/$*.d -I include $<
MAKEDEPEND_TEST = g++ -MM -MT "$@" -MF deps/$*_test.d -I include $<

# Package for submission
.PHONY: submission
submission: $(SRCS) $(TEST_SRCS) tests/testMain.cc doc/latex/refman.pdf include/* | sub 
	echo $? | xargs cp -t sub
	-rm sub/memtrace.*
	-rm sub/gtest_lite.h
	-rm sub/factolog.cpp
	mv sub/testMain.cc sub/testMain.cpp
	mv sub/refman.pdf sub/factolog.pdf
	mkdir -p sub/tests
	cp tests/*.fl sub/tests/
	zip sub/sub.zip sub/* -j -x *.pdf
	cd sub && zip datafiles.zip tests/*

sub:
	mkdir -p sub

# Folder for object files
obj:
	mkdir -p obj

# Folder for dependency files
deps:
	mkdir -p deps

# Clean artifacts
.PHONY: clean
clean:
	-rm -rf obj
	-rm -rf deps
	-rm -rf doc/html doc/latex
	-rm factolog
	-rm factoTest
	-rm tests/testMain.cc
	-rm -rf sub/

# Rules for object files
obj/%.o: src/%.cpp deps/%.d | obj
	@$(MAKEDEPEND)
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Rule for final executable
factolog: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(CMD) -o $@ $(LIBS)

# Rule for documentation
.PHONY: documentation
documentation: doc/html pdf

# Rule for html documentation
.PHONY: html
html: doc/html
doc/html: doc $(wildcard include/*)
	doxygen

# Rule for documentation pdf
.PHONY: pdf
pdf: doc/latex/refman.pdf
doc/latex/refman.pdf: doc/html $(wildcard include/*)
	cd doc/latex
	make -C doc/latex -f Makefile

# Rule for test compilation
.PHONY: tests
tests : factoTest

factoTest: $(TEST_OBJS) $(OBJS) tests/testMain.cc
	$(CXX) $(LDFLAGS) $(CMD) $(TEST_OBJS) $(filter-out obj/factolog.o, $(OBJS)) tests/testMain.cc -o factoTest $(LIBS)

# Using .cc extention to not be included in TEST_SRCS
tests/testMain.cc: $(TEST_SRCS)
	echo $(TEST_SRCS) | tr ' ' '\n' | sed 's/tests\//void /;s/\.cpp/()\;/' > $@
	echo 'int main(){' >> $@
	echo $(TEST_SRCS) | tr ' ' '\n' | sed 's/tests\///;s/\.cpp/()\;/;' >> $@
	echo "return 0;}" >> $@


obj/%_test.o: tests/%_test.cpp deps/%_test.d | obj
	@$(MAKEDEPEND_TEST)
	$(CXX) -c $(CXXFLAGS) -Wno-error $< -o $@

# Automatic dependeny wizardry
$(DEPFILES): deps
include $(DEPFILES)
