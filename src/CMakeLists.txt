cmake_minimum_required(VERSION 2.8)	 # Проверка версии CMake.
					# Если версия установленой программы

project(Calc)			# Название проекта

set( Calc_source calc.cpp )
add_library( calc STATIC ${Calc_source} )		
