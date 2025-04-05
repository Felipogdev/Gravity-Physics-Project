rm -rf screen

g++ *.cpp classes/*.cpp -o screen src/glad.c -Iinclude -lglfw -lGL -lm -ldl

sleep 1
./screen
