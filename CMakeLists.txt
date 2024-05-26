cmake_minimum_required(VERSION 3.25)
project(Veridia)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/release/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/release/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/release/bin)

if(WIN32)
    if(MSVC)
        add_compile_options(/source-charset:utf-8)
    elseif(CMAKE_COMPILER_IS_GNUCC)
        execute_process(COMMAND PowerShell "[System.Text.Encoding]::Default.BodyName" OUTPUT_VARIABLE USER_CHARSET OUTPUT_STRIP_TRAILING_WHITESPACE)
        add_compile_options(-fexec-charset=${USER_CHARSET})
    elseif (CMAKE_COMPILER_IS_GNUCXX)
        execute_process(COMMAND PowerShell "[System.Text.Encoding]::Default.BodyName" OUTPUT_VARIABLE USER_CHARSET OUTPUT_STRIP_TRAILING_WHITESPACE)
        add_compile_options(-fexec-charset=${USER_CHARSET})
    endif ()
endif ()

add_executable(FileChainRead ${PROJECT_SOURCE_DIR}/src/FSR/FileChainRead.cpp)