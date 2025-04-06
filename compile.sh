rm -rf screen

g++ *.cpp classes/*.cpp -o screen src/glad.c -Iinclude -lglfw -lGL -lm -ldl -lGLU

sleep 1
./screen
