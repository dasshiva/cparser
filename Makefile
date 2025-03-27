# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shiva/cparser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shiva/cparser

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/shiva/cparser/CMakeFiles /home/shiva/cparser//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/shiva/cparser/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -P /home/shiva/cparser/CMakeFiles/VerifyGlobs.cmake
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named langc

# Build rule for target.
langc: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 langc
.PHONY : langc

# fast build rule for target.
langc/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/langc.dir/build.make CMakeFiles/langc.dir/build
.PHONY : langc/fast

src/driver.o: src/driver.cpp.o
.PHONY : src/driver.o

# target to build an object file
src/driver.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/langc.dir/build.make CMakeFiles/langc.dir/src/driver.cpp.o
.PHONY : src/driver.cpp.o

src/driver.i: src/driver.cpp.i
.PHONY : src/driver.i

# target to preprocess a source file
src/driver.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/langc.dir/build.make CMakeFiles/langc.dir/src/driver.cpp.i
.PHONY : src/driver.cpp.i

src/driver.s: src/driver.cpp.s
.PHONY : src/driver.s

# target to generate assembly for a file
src/driver.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/langc.dir/build.make CMakeFiles/langc.dir/src/driver.cpp.s
.PHONY : src/driver.cpp.s

src/lexer.o: src/lexer.cpp.o
.PHONY : src/lexer.o

# target to build an object file
src/lexer.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/langc.dir/build.make CMakeFiles/langc.dir/src/lexer.cpp.o
.PHONY : src/lexer.cpp.o

src/lexer.i: src/lexer.cpp.i
.PHONY : src/lexer.i

# target to preprocess a source file
src/lexer.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/langc.dir/build.make CMakeFiles/langc.dir/src/lexer.cpp.i
.PHONY : src/lexer.cpp.i

src/lexer.s: src/lexer.cpp.s
.PHONY : src/lexer.s

# target to generate assembly for a file
src/lexer.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/langc.dir/build.make CMakeFiles/langc.dir/src/lexer.cpp.s
.PHONY : src/lexer.cpp.s

src/parser.o: src/parser.cpp.o
.PHONY : src/parser.o

# target to build an object file
src/parser.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/langc.dir/build.make CMakeFiles/langc.dir/src/parser.cpp.o
.PHONY : src/parser.cpp.o

src/parser.i: src/parser.cpp.i
.PHONY : src/parser.i

# target to preprocess a source file
src/parser.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/langc.dir/build.make CMakeFiles/langc.dir/src/parser.cpp.i
.PHONY : src/parser.cpp.i

src/parser.s: src/parser.cpp.s
.PHONY : src/parser.s

# target to generate assembly for a file
src/parser.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/langc.dir/build.make CMakeFiles/langc.dir/src/parser.cpp.s
.PHONY : src/parser.cpp.s

src/utility.o: src/utility.cpp.o
.PHONY : src/utility.o

# target to build an object file
src/utility.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/langc.dir/build.make CMakeFiles/langc.dir/src/utility.cpp.o
.PHONY : src/utility.cpp.o

src/utility.i: src/utility.cpp.i
.PHONY : src/utility.i

# target to preprocess a source file
src/utility.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/langc.dir/build.make CMakeFiles/langc.dir/src/utility.cpp.i
.PHONY : src/utility.cpp.i

src/utility.s: src/utility.cpp.s
.PHONY : src/utility.s

# target to generate assembly for a file
src/utility.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/langc.dir/build.make CMakeFiles/langc.dir/src/utility.cpp.s
.PHONY : src/utility.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... langc"
	@echo "... src/driver.o"
	@echo "... src/driver.i"
	@echo "... src/driver.s"
	@echo "... src/lexer.o"
	@echo "... src/lexer.i"
	@echo "... src/lexer.s"
	@echo "... src/parser.o"
	@echo "... src/parser.i"
	@echo "... src/parser.s"
	@echo "... src/utility.o"
	@echo "... src/utility.i"
	@echo "... src/utility.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -P /home/shiva/cparser/CMakeFiles/VerifyGlobs.cmake
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

