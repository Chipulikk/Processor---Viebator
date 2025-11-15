#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int NUM_OF_INST = 3;
int INST_LEN = 10;
int NO_ARG_FUNC = 2;
const char INST [3][10] = {"PUSH", "POP", "SUM"};
int CODE [30];


int ERRS = 0;

enum Errors
{
COM_NAME_ERROR = 1,
ARG_ERROR = 2,
};


int Comp (FILE *byte);

int FuncCheck (char *input/*, FILE *byte*/);

int ComCheck (char *input, FILE *byte);

int ArgCheck (int scnd);

void ErrChange (int err);


///////////////////////////////////////////

int main ()
{
    FILE *code = fopen ("code.txt", "r");

    int size = Comp(code);

    int i = 0;
    printf("\nAfter scanning:\n");
    for (i; i < size; i++)          //в текущем примере в конце может появиться лишний 0: это из за -12 в байте
        {
        printf ("#%d = [%d]\n", i, CODE[i]);
        }


    FILE *compil = fopen ("compilled.txt", "w");
    for (i = 0; i < size; i++)
        fprintf(compil, "%d ", CODE [i]);

    fclose (compil);
    fclose (code);

    printf ("\n[ошибки E = %d,    колво строк S = %d]\n", ERRS, size);
    return 0;
}

//////////////////////////////////////////

int Comp (FILE *byte)   //Возвращает количество команд
    {
    char a[20];
    int i = 0; // кол строк
    int c = 0;
    int n = 0; //кол во команд
    //int size = 0; это была переменная за размер считанного, не пригодилась

    for (i; fscanf(byte, "%s", a) != EOF; i++, n++)
    {
        if (ComCheck (a, byte))
        {
            printf ("#%d:   %s\n", i, a);
            CODE[i] = FuncCheck(a);                                   //Массив с командами

            if ( (CODE [i] < NO_ARG_FUNC)  &&  (CODE[i] > 0) )      //это задефайненное число, обозначающее начало команд без аргумента
            {
                i++;
                fscanf (byte, "%d", &c);
                CODE [i] = ArgCheck (c);                            //Сам не понимаюэтот маневр (почему сразу не присваиваю c)
                    printf ("\t#%d: ARG: %d\n\n", i, c);
            }

        }

        else
        {
            i--;
            n--;
        }
    }

    return i;
    }

//--------------------------------------------------------

int FuncCheck (char *input/*, FILE *comp*/)
    {
    int i = 0;
    for (i; i < NUM_OF_INST; i++)
        {
        if (strcmp ((const char*) input, INST[i]) == 0)
            return i + 1; //ВОзвращает сразу код команды
        }

        ErrChange(COM_NAME_ERROR);
        return 0;  //Функция вызывается только тогда, когда вызывается команда, поэтому
                                //этот ретерн сработает, только если там какая то залупень
    }

//--------------------------------------------

int ComCheck (char *input, FILE *byte)
{
    if (input [0] == 'O' && input[1] == 'V' && input[2] == 'C' && input[3] == 'H' && input[4] == 'O' && input[5] == 'S')
    {
        while (fgetc(byte) != '\n');
        return 0;
    }
    return 1;
}

//-------------------------------------

int ArgCheck (int scnd)
{
    if (scnd == 0)
        ErrChange (ARG_ERROR);

    return scnd;
}

//-----------------------------------

void ErrChange (int err)
{
    if (! (err & ERRS))
        ERRS += err;
}

//fprintf (comp, "\nUnexpected name of function\n")
