# CalcMc - gtkmm
This is calcmc, but with gtkmm (gtk+ binding to c++)

## Compiling
To compile on linux, you need to install gtkmm (version 3, developpement version).
Then, compile: 
```
g++ -c main.cpp `pkg-config gtkmm-3.0 --cflags`
```
And Link:
```
g++ main.o -o main `pkg-config gtkmm-3.0 --libs`
```
