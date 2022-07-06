cmake_minimum_required (VERSION 3.23)
project(
	"bake"
	VERSION
	1.0
	LANGUAGES
	CXX
)

set (CMAKE_FOLDER ./)
set (name bake)
set (sources
	test/app.cpp
	src/core/ec.cpp
)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
link_libraries(OpenSSL::SSL)
include_directories(./src)
add_executable(${name} ${sources})
