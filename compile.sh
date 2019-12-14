g++ -c src/*.cpp -Wall
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

./sfml-app