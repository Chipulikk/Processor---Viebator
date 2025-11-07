#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int NUM_OF_INST = 3;
int INST_LEN = 10;
const char INST [3][10] = {"PUSH", "POP", "SUM"};
int CODE [30];


int Comp (FILE *byte);

int InstCheck (char *input);
//////////////////////////

int main ()
{
FILE *code = fopen ("code.txt", "r"); //проверка а открытие

Comp(code);

int i = 0;
printf("\nAfter scanning:\n");
for (i; i < 10; i++)
    {
    printf ("#%d = [%d]\n", i, CODE[i]);
    }
return 0;

}

int Comp (FILE *byte)
    {
    char a[20];
    int i = 0;
    int c = 0;
    for (i; fscanf(byte, "%s", a) != EOF; i++)
        {
        printf ("#%d:   %s\n", i, a);
        CODE[i] = InstCheck(a);     //Массив с командами
        }

    return i;
    }

//-----------------------------------------------------------------

int InstCheck (char *input)     //Инст лен, нам оф инст надо будет задефайнить
    {
    int i = 0;
    for (i; i < NUM_OF_INST; i++)
        {
        if (strcmp ((const char*) input, INST[i]) == 0)
            return i + 1; //ВОзвращает сразу код команды
        }
    int a = atoi(input);
    if (a == 0) //несуществующая команда, надо что то сделать
        return 0;

    return a;
    }


