############################
# Compiler Configurations  #
############################

# This variable specifies the name of the compiler that will be used to compile the project.
# By default, it is set to 'gcc', the GNU Compiler Collection.
# You can modify this variable to specify a different compiler if needed.
CC = gcc

# C_FLAGS: Compiler Flags
# This variable stores the compiler flags used during the compilation process.
# Compiler flags are options passed to the compiler to control its behavior, 
# used for optimization level, debugging symbols, and warnings.
# You can customize the compiler flags by adding or modifying options in this variable.
C_FLAGS = -g -Wall 


# This variable stores additional flags to be passed to the linker.
# Modify this variable to include any extra linker flags which you may need.
LINKER_FLAGS =

###################################
# Compiler Inputs  Configurations #
###################################

# SRC_DIRECTORIES is a variable that holds a list of directories where the source 
# files for the project are located. This variable is useful when the project's 
# source files are organized into multiple directories, such as when using a modular 
# or hierarchical project structure.
# 
# Example usage:
# SRC_DIRECTORIES = src/ src_dir/
#
# Each directory listed here should contain source files (*.c, *.s) necessary 
# for building the project. Make will search for source files recursively within these 
# directories when compiling the project.
#
SRC_DIRECTORIES = logging


# This variable stores the paths to the source files.
# Modify this variable to include the paths to your source files
# if they are not located in any directory.
# For example:
# SRC_FILES_PATHES = src1.c src2.c
# This specifies three source files: src1.c, src2.c, and src3.c,
# where src3.c is located in the "subdir" directory relative to the
# current directory.
SRC_FILES_PATHES = main.c 

# INC_DIRECTORIES is a variable that holds a list of directories where header files 
# for the project are located. These directories typically contain header files (*.h) 
# necessary for compiling the source code files. This variable is useful for specifying 
# the search paths for header files during compilation, ensuring that the compiler can 
# locate and include the necessary header files.
# 
# Example usage:
# INC_DIRECTORIES = include/ libs/
#
# Each directory listed here should contain header files (*.h) that are required by the 
# source files in the project. When compiling source files, Make will search for header 
# files recursively within these directories, allowing the source files to include headers 
# using relative paths.
#
# It's important to ensure that the directory paths are terminated with a forward slash (/) 
# to indicate that they are directories, and they should be relative to the location of the 
# Makefile or specified with an absolute path.
INC_DIRECTORIES =  logging

# LIBS_DIRECTORIES is a variable that holds a list of directories where library files 
# for the project are located. These directories typically contain precompiled libraries 
# (*.a, *.so) necessary for linking the project during the build process. This variable 
# is useful for specifying the search paths for library files, ensuring that the linker 
# can locate and link against the necessary libraries.
# 
# Example usage:
# LIBS_DIRECTORIES = libs/ external/
#
# Each directory listed here should contain library files (*.a, *.so) that are required 
# by the project. When linking the project, Make will search for library files recursively 
# within these directories, allowing the linker to include the necessary libraries.
#
LIBS_DIRECTORIES  = 

# EXECUTABLE_FILE is a variable that stores the name of the executable file 
# that will be produced after compiling the source code. This file typically 
# represents the final compiled version of the program that can be executed 
# directly. Ensure that this variable is set to the appropriate name for your 
# executable file, including any necessary file extensions. Example usage: 
# EXECUTABLE_FILE = my_program_name
EXECUTABLE_FILE = log

