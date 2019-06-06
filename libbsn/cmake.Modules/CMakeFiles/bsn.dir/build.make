# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/les-06/Documentos/odvbsn/libbsn

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/les-06/Documentos/odvbsn/libbsn/cmake.Modules

# Include any dependencies generated for this target.
include CMakeFiles/bsn.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bsn.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bsn.dir/flags.make

# Object files for target bsn
bsn_OBJECTS =

# External object files for target bsn
bsn_EXTERNAL_OBJECTS = \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/communication/TCPReceive.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/communication/TCPSend.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/configuration/SensorConfiguration.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/filters/MovingAverage.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/generator/Markov.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/goalmodel/Context.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/goalmodel/Task.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/control/BloodpressureControlCommand.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/control/CentralHubControlCommand.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/control/ECGControlCommand.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/control/OximeterControlCommand.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/control/ThermometerControlCommand.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/data/ResourceUpdate.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/data/SensorData.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/info/ContextInfo.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/info/MonitorContextInfo.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/info/MonitorTaskInfo.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/info/PatientStatusInfo.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/info/SensorStatusInfo.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/info/TaskInfo.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/taskMsg/ECG/ECGCollectTaskMsg.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/taskMsg/ECG/ECGFilterTaskMsg.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/taskMsg/ECG/ECGTransferTaskMsg.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/taskMsg/oximeter/OximeterCollectTaskMsg.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/taskMsg/oximeter/OximeterFilterTaskMsg.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/taskMsg/oximeter/OximeterTransferTaskMsg.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/taskMsg/sphygmomanometer/BloodpressureCollectTaskMsg.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/taskMsg/sphygmomanometer/BloodpressureFilterTaskMsg.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/taskMsg/sphygmomanometer/BloodpressureTransferTaskMsg.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/taskMsg/thermometer/ThermometerCollectTaskMsg.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/taskMsg/thermometer/ThermometerFilterTaskMsg.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/msg/taskMsg/thermometer/ThermometerTransferTaskMsg.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/operation/Operation.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/processor/Processor.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/range/Range.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/resource/Battery.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/sensorfault/RandomSensorFault.cpp.o" \
"/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn-core.dir/src/time/TimeData.cpp.o"

libbsn.so: CMakeFiles/bsn-core.dir/src/communication/TCPReceive.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/communication/TCPSend.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/configuration/SensorConfiguration.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/filters/MovingAverage.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/generator/Markov.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/goalmodel/Context.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/goalmodel/Task.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/control/BloodpressureControlCommand.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/control/CentralHubControlCommand.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/control/ECGControlCommand.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/control/OximeterControlCommand.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/control/ThermometerControlCommand.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/data/ResourceUpdate.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/data/SensorData.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/info/ContextInfo.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/info/MonitorContextInfo.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/info/MonitorTaskInfo.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/info/PatientStatusInfo.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/info/SensorStatusInfo.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/info/TaskInfo.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/taskMsg/ECG/ECGCollectTaskMsg.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/taskMsg/ECG/ECGFilterTaskMsg.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/taskMsg/ECG/ECGTransferTaskMsg.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/taskMsg/oximeter/OximeterCollectTaskMsg.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/taskMsg/oximeter/OximeterFilterTaskMsg.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/taskMsg/oximeter/OximeterTransferTaskMsg.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/taskMsg/sphygmomanometer/BloodpressureCollectTaskMsg.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/taskMsg/sphygmomanometer/BloodpressureFilterTaskMsg.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/taskMsg/sphygmomanometer/BloodpressureTransferTaskMsg.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/taskMsg/thermometer/ThermometerCollectTaskMsg.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/taskMsg/thermometer/ThermometerFilterTaskMsg.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/msg/taskMsg/thermometer/ThermometerTransferTaskMsg.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/operation/Operation.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/processor/Processor.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/range/Range.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/resource/Battery.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/sensorfault/RandomSensorFault.cpp.o
libbsn.so: CMakeFiles/bsn-core.dir/src/time/TimeData.cpp.o
libbsn.so: CMakeFiles/bsn.dir/build.make
libbsn.so: /usr/local/lib/libopendavinci.so
libbsn.so: /usr/lib/x86_64-linux-gnu/librt.a
libbsn.so: CMakeFiles/bsn.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX shared library libbsn.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bsn.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bsn.dir/build: libbsn.so

.PHONY : CMakeFiles/bsn.dir/build

CMakeFiles/bsn.dir/requires:

.PHONY : CMakeFiles/bsn.dir/requires

CMakeFiles/bsn.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bsn.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bsn.dir/clean

CMakeFiles/bsn.dir/depend:
	cd /home/les-06/Documentos/odvbsn/libbsn/cmake.Modules && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/les-06/Documentos/odvbsn/libbsn /home/les-06/Documentos/odvbsn/libbsn /home/les-06/Documentos/odvbsn/libbsn/cmake.Modules /home/les-06/Documentos/odvbsn/libbsn/cmake.Modules /home/les-06/Documentos/odvbsn/libbsn/cmake.Modules/CMakeFiles/bsn.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bsn.dir/depend

