# PYTHON = /usr/lib/python3.6/config-3.6m-x86_64-linux-gnu/python-config.py --ldflags
default: xclicker

clicker-lib.o: clicker-lib.c clicker-lib.h
	g++ -Wall -c $< -o $@

python-wrapper.o: python-wrapper.cpp python-wrapper.hpp
	g++ -Wall -c $< -o $@

xclicker: main.cpp clicker-lib.o python-wrapper.o
	g++ -Wall $^ -o $@ -lX11 -lpython3.6m


