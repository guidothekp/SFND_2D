# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/local/anaconda3/bin/cmake

# The command to remove a file.
RM = /usr/local/anaconda3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/kamesh/work/development/SFND_2D_kk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kamesh/work/development/SFND_2D_kk/build

# Include any dependencies generated for this target.
include CMakeFiles/2D_feature_tracking.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/2D_feature_tracking.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2D_feature_tracking.dir/flags.make

CMakeFiles/2D_feature_tracking.dir/src/matching2D_Student.cpp.o: CMakeFiles/2D_feature_tracking.dir/flags.make
CMakeFiles/2D_feature_tracking.dir/src/matching2D_Student.cpp.o: ../src/matching2D_Student.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kamesh/work/development/SFND_2D_kk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/2D_feature_tracking.dir/src/matching2D_Student.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/2D_feature_tracking.dir/src/matching2D_Student.cpp.o -c /Users/kamesh/work/development/SFND_2D_kk/src/matching2D_Student.cpp

CMakeFiles/2D_feature_tracking.dir/src/matching2D_Student.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2D_feature_tracking.dir/src/matching2D_Student.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kamesh/work/development/SFND_2D_kk/src/matching2D_Student.cpp > CMakeFiles/2D_feature_tracking.dir/src/matching2D_Student.cpp.i

CMakeFiles/2D_feature_tracking.dir/src/matching2D_Student.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2D_feature_tracking.dir/src/matching2D_Student.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kamesh/work/development/SFND_2D_kk/src/matching2D_Student.cpp -o CMakeFiles/2D_feature_tracking.dir/src/matching2D_Student.cpp.s

CMakeFiles/2D_feature_tracking.dir/src/MidTermProject_Camera_Student.cpp.o: CMakeFiles/2D_feature_tracking.dir/flags.make
CMakeFiles/2D_feature_tracking.dir/src/MidTermProject_Camera_Student.cpp.o: ../src/MidTermProject_Camera_Student.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kamesh/work/development/SFND_2D_kk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/2D_feature_tracking.dir/src/MidTermProject_Camera_Student.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/2D_feature_tracking.dir/src/MidTermProject_Camera_Student.cpp.o -c /Users/kamesh/work/development/SFND_2D_kk/src/MidTermProject_Camera_Student.cpp

CMakeFiles/2D_feature_tracking.dir/src/MidTermProject_Camera_Student.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2D_feature_tracking.dir/src/MidTermProject_Camera_Student.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kamesh/work/development/SFND_2D_kk/src/MidTermProject_Camera_Student.cpp > CMakeFiles/2D_feature_tracking.dir/src/MidTermProject_Camera_Student.cpp.i

CMakeFiles/2D_feature_tracking.dir/src/MidTermProject_Camera_Student.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2D_feature_tracking.dir/src/MidTermProject_Camera_Student.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kamesh/work/development/SFND_2D_kk/src/MidTermProject_Camera_Student.cpp -o CMakeFiles/2D_feature_tracking.dir/src/MidTermProject_Camera_Student.cpp.s

# Object files for target 2D_feature_tracking
2D_feature_tracking_OBJECTS = \
"CMakeFiles/2D_feature_tracking.dir/src/matching2D_Student.cpp.o" \
"CMakeFiles/2D_feature_tracking.dir/src/MidTermProject_Camera_Student.cpp.o"

# External object files for target 2D_feature_tracking
2D_feature_tracking_EXTERNAL_OBJECTS =

2D_feature_tracking: CMakeFiles/2D_feature_tracking.dir/src/matching2D_Student.cpp.o
2D_feature_tracking: CMakeFiles/2D_feature_tracking.dir/src/MidTermProject_Camera_Student.cpp.o
2D_feature_tracking: CMakeFiles/2D_feature_tracking.dir/build.make
2D_feature_tracking: /usr/local/lib/libopencv_gapi.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_stitching.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_alphamat.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_aruco.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_barcode.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_bgsegm.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_bioinspired.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_ccalib.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_cvv.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_dnn_objdetect.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_dnn_superres.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_dpm.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_face.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_freetype.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_fuzzy.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_hdf.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_hfs.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_img_hash.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_intensity_transform.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_line_descriptor.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_mcc.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_quality.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_rapid.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_reg.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_rgbd.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_saliency.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_sfm.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_stereo.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_structured_light.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_superres.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_surface_matching.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_tracking.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_videostab.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_wechat_qrcode.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_xfeatures2d.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_xobjdetect.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_xphoto.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_shape.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_highgui.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_datasets.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_plot.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_text.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_ml.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_phase_unwrapping.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_optflow.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_ximgproc.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_video.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_videoio.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_dnn.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_imgcodecs.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_objdetect.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_calib3d.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_features2d.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_flann.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_photo.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_imgproc.4.5.2.dylib
2D_feature_tracking: /usr/local/lib/libopencv_core.4.5.2.dylib
2D_feature_tracking: CMakeFiles/2D_feature_tracking.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kamesh/work/development/SFND_2D_kk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable 2D_feature_tracking"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2D_feature_tracking.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2D_feature_tracking.dir/build: 2D_feature_tracking

.PHONY : CMakeFiles/2D_feature_tracking.dir/build

CMakeFiles/2D_feature_tracking.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/2D_feature_tracking.dir/cmake_clean.cmake
.PHONY : CMakeFiles/2D_feature_tracking.dir/clean

CMakeFiles/2D_feature_tracking.dir/depend:
	cd /Users/kamesh/work/development/SFND_2D_kk/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kamesh/work/development/SFND_2D_kk /Users/kamesh/work/development/SFND_2D_kk /Users/kamesh/work/development/SFND_2D_kk/build /Users/kamesh/work/development/SFND_2D_kk/build /Users/kamesh/work/development/SFND_2D_kk/build/CMakeFiles/2D_feature_tracking.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/2D_feature_tracking.dir/depend

