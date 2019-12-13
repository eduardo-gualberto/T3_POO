g++ -c src/*.cpp
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
rm Laser.o Meteoro.o main.o
./sfml-app