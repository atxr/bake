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
set (app
	test/client.cpp
	test/blinding.cpp
	test/hash.cpp
)
set (sources
	src/core/Core.cpp
	src/core/ec.cpp
	src/client/Client.cpp
	src/server/ComputationServer.cpp
	src/server/AuthenticationServer.cpp
)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
link_libraries(OpenSSL::SSL)
include_directories(./src)

foreach(sourcefile ${app})
	string( REPLACE ".cpp" "" appname ${sourcefile} )
	string( REPLACE "test/" "" appname ${appname} )
	add_executable(${appname} ${sourcefile} ${sources})
endforeach(sourcefile ${app})
