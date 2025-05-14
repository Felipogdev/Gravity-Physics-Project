rm screen

g++ main.cpp glad/glad.c -Iinclude -I. -o screen -lglfw -ldl -lGL

sleep 1
./screen