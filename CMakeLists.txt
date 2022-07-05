cmake_minimum_required (VERSION 3.23)
project(
	"bake"
	VERSION
	1.0
	LANGUAGES
	CXX
)

set (CMAKE_FOLDER ./)
set (sources
	src/main.cpp
)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
add_executable(bake ${sources})
