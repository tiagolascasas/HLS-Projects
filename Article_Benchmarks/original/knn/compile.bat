gcc -std=c99 -Wall -O3 -c knn.c utils.c
gcc -std=c99 -Wall -O3 main.c knn.o utils.o -o main
