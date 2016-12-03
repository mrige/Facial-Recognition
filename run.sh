
#complle cpp file
g++ `pkg-config --cflags opencv` main.cpp `pkg-config --libs opencv` -o easyprog

#run program
./easyprog face1
