//#include <stdio.h>

//x * y + !x * z;
int main() 
{
    int a = 13;
    int b = 25;
    int c = 100;
    int d = 200;
    int e;
    /*
    int x;

    e = c == 100 ? a : b;
    printf("%d\n", e);
    e = c != 100 ? a : b;
    printf("%d\n", e);
    e = d == 200 ? a : b;
    printf("%d\n", e);
    e = d != 200 ? a : b;
    printf("%d\n", e);
    printf("-------------\n");
    x = c == 100;
    e = x * a + !x * b;
    printf("%d\n", e);
    x = c != 100;
    e = x * a + !x * b;
    printf("%d\n", e);
    x = d == 200;
    e = x * a + !x * b;
    printf("%d\n", e);
    x = d != 200;
    e = x * a + !x * b;
    printf("%d\n", e);*/
    
    if (c == 13)
        e = a;
    else
        e = b;
    
    if (c == 13) {
        e = a;
        e = a + b;
    }
    else {
        e = b;
        e = b + c;
    }

    e = c == 13 ? a : b;
    
    return 0;
}