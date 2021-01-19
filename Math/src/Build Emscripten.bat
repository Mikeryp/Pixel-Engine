@echo off

call emcc -c Functions.cpp -std=c++11 -O3
call emcc -c mat2.cpp -std=c++11 -O3
call emcc -c mat3.cpp -std=c++11 -O3
call emcc -c mat4.cpp -std=c++11 -O3
call emcc -c Quaternion.cpp -std=c++11 -O3
call emcc -c Vector2s.cpp -std=c++11 -O3
call emcc -c Vector2.cpp -std=c++11 -O3
call emcc -c Vector3.cpp -std=c++11 -O3
call emcc -c Vector4.cpp -std=c++11 -O3

call emcc -std=c++11 -O3 Functions.o mat2.o mat3.o mat4.o Quaternion.o Vector2s.o Vector2.o Vector3.o Vector4.o -o Math.bc

del Functions.o
del mat2.o
del mat3.o
del mat4.o
del Quaternion.o
del Vector2s.o
del Vector2.o
del Vector3.o
del Vector4.o