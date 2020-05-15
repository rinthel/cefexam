cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 17)
project(cefexam)

set(SOURCE_FILES
    main.cpp
    )

add_executable(cefexam ${SOURCE_FILES})

target_include_directories(cefexam PUBLIC
    /Users/rinthel/Documents/sdk/cef
    )

target_link_libraries(cefexam PUBLIC
        -L/Users/rinthel/Documents/sdk/cef/Debug
        cef_dll_wrapper
        "-Wl,-F/Users/rinthel/Documents/sdk/cef/Debug"
        "-framework \"Chromium Embedded Framework\""
        )
target_compile_options(cefexam PUBLIC -x objective-c++)
target_compile_options(cefexam PUBLIC "-fobjc-arc")

set_target_properties(cefexam PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/info.plist)
add_custom_command(TARGET cefexam POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "/Users/rinthel/Documents/sdk/cef/Debug/Chromium Embedded Framework.framework"
    "${CMAKE_CURRENT_BINARY_DIR}/cefexam.app/Contents/Frameworks/Chromium Embedded Framework.framework"
    )
