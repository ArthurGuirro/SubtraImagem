Trabalho de computação gráfica

O sistema operacional usado foi um Linux base Debian

Para compilar:
  g++ tc1_1.cpp -o tc1_1 $(pkg-config --cflags --libs opencv4) -lglut -lGLU -lGL -lm

Para rodar:
  ./tc1_1
