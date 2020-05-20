gcc -std=c99 -O3 -march=native -mtune=native -floop-optimize -funroll-loops -funroll-all-loops -fno-guess-branch-probability -c knn.c utils.c
gcc -std=c99 -O3 -march=native -mtune=native -floop-optimize -funroll-all-loops -fno-guess-branch-probability main.c knn.o utils.o -o main
