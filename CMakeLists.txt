cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INSTALL_PREFIX "./")
set(DOWNLOAD_EXTRACT_TIMESTAMP true)

# 使用接口库
add_library(compiler_flags INTERFACE)
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,AppleClang,Clang,LCC,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:MSVC,CXX>")
target_compile_options(
	compiler_flags 
	INTERFACE
	"$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wunused;-Wextra;-Wformat=2;-Werror>>"
	"$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)


project(tutorial VERSION 1.1)

configure_file(config.h.in config.h)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()
add_executable(tutorial test_sqrt.cpp)
target_link_libraries(tutorial PUBLIC compiler_flags GTest::gtest_main)
target_include_directories(tutorial PUBLIC ${PROJECT_BINARY_DIR})

include(GoogleTest)
gtest_discover_tests(tutorial)

install(
	TARGETS
		tutorial
	DESTINATION
		bin
)


install(
	FILES
		"${PROJECT_BINARY_DIR}/config.h"
	DESTINATION
		include
)


# 添加测试
#enable_testing() # 启动测试·
#function(do_test target args result)
#	add_test(NAME COMP${args} COMMAND ${target} ${args})	# 添加一个测试
#	set_tests_properties( # 设置测试的属性
#		COMP${args}
#		PROPERTIES 
#			PASS_REGULAR_EXPRESSION 
#			${result}	
#	)
#			
#endfunction()
#
#do_test(tutorial 9 3)
#do_test(tutorial 16 4)
#do_test(tutorial 100 10)
#do_test(tutorial 0.0001 0.01)



