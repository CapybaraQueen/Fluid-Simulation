cmake_minimum_required(VERSION 3.23)
project(FluidSimulationProject)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(FluidSimulation)

target_sources(FluidSimulation
	PRIVATE
		./src/impl/main.cpp
		./src/impl/Physics.cpp
		./src/impl/Fluid.cpp
		./src/impl/Simulation.cpp
	PUBLIC
		FILE_SET myHeaders
		TYPE HEADERS
		BASE_DIRS
			./src/headers
		FILES
			./src/headers/Fluid.h
			./src/headers/Simulation.h
			./src/headers/Physics.h
			./src/headers/TypeU.h
			./src/headers/InitialConditions.h
)
