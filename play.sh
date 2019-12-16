g++ -c src/*.cpp
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
rm *.o
./sfml-app