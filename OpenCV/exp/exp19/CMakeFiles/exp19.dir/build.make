# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dnq/Working/learn_C++/OpenCV/exp/exp19

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dnq/Working/learn_C++/OpenCV/exp/exp19

# Include any dependencies generated for this target.
include CMakeFiles/exp19.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/exp19.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exp19.dir/flags.make

CMakeFiles/exp19.dir/main.cpp.o: CMakeFiles/exp19.dir/flags.make
CMakeFiles/exp19.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dnq/Working/learn_C++/OpenCV/exp/exp19/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/exp19.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exp19.dir/main.cpp.o -c /home/dnq/Working/learn_C++/OpenCV/exp/exp19/main.cpp

CMakeFiles/exp19.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exp19.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dnq/Working/learn_C++/OpenCV/exp/exp19/main.cpp > CMakeFiles/exp19.dir/main.cpp.i

CMakeFiles/exp19.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exp19.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dnq/Working/learn_C++/OpenCV/exp/exp19/main.cpp -o CMakeFiles/exp19.dir/main.cpp.s

# Object files for target exp19
exp19_OBJECTS = \
"CMakeFiles/exp19.dir/main.cpp.o"

# External object files for target exp19
exp19_EXTERNAL_OBJECTS =

exp19: CMakeFiles/exp19.dir/main.cpp.o
exp19: CMakeFiles/exp19.dir/build.make
exp19: /usr/local/lib/libopencv_gapi.so.4.6.0
exp19: /usr/local/lib/libopencv_highgui.so.4.6.0
exp19: /usr/local/lib/libopencv_ml.so.4.6.0
exp19: /usr/local/lib/libopencv_objdetect.so.4.6.0
exp19: /usr/local/lib/libopencv_photo.so.4.6.0
exp19: /usr/local/lib/libopencv_stitching.so.4.6.0
exp19: /usr/local/lib/libopencv_video.so.4.6.0
exp19: /usr/local/lib/libopencv_videoio.so.4.6.0
exp19: /usr/local/lib/libopencv_imgcodecs.so.4.6.0
exp19: /usr/local/lib/libopencv_dnn.so.4.6.0
exp19: /usr/local/lib/libopencv_calib3d.so.4.6.0
exp19: /usr/local/lib/libopencv_features2d.so.4.6.0
exp19: /usr/local/lib/libopencv_flann.so.4.6.0
exp19: /usr/local/lib/libopencv_imgproc.so.4.6.0
exp19: /usr/local/lib/libopencv_core.so.4.6.0
exp19: CMakeFiles/exp19.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dnq/Working/learn_C++/OpenCV/exp/exp19/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable exp19"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exp19.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exp19.dir/build: exp19

.PHONY : CMakeFiles/exp19.dir/build

CMakeFiles/exp19.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exp19.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exp19.dir/clean

CMakeFiles/exp19.dir/depend:
	cd /home/dnq/Working/learn_C++/OpenCV/exp/exp19 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dnq/Working/learn_C++/OpenCV/exp/exp19 /home/dnq/Working/learn_C++/OpenCV/exp/exp19 /home/dnq/Working/learn_C++/OpenCV/exp/exp19 /home/dnq/Working/learn_C++/OpenCV/exp/exp19 /home/dnq/Working/learn_C++/OpenCV/exp/exp19/CMakeFiles/exp19.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exp19.dir/depend

