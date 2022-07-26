
#include <stdio.h>
#include <accctrl.h>


#define BACK 0
#define DIRECTLY 1

#define CORRECT_INPUT 2
#define INCORRECT_INPUT 3


typedef struct _iobuf
{
    char*   _ptr;
    int     _cnt;
    char*   _base;
    int     _flag;
    int     _file;
    int     _charbuf;
    int     _bufsiz;
    char*   _tmpfname;
}  FILE;


int open_file(char* filename)
{
    FILE* input = 0;

    if((input = fopen(filename, "r")) != NULL)
    {
        fclose(input);
        return CORRECT_INPUT;
    }
    
    else
        return INCORRECT_INPUT;
}

int main(int argc, char* argv[])
{
    char* filename = argv[1];

    int input_error = open_file(filename);
    if(input_error == INCORRECT_INPUT)
    {
        printf("File is not founded");
        exit(INCORRECT_INPUT);
    }

    int flag = DIRECTLY;

    if(argv[2][0] == '-' && argv[2][1] == 'r')
        flag = BACK;
    
    if(flag == BACK);
        // sort_back();
    if(flag == DIRECTLY);
        // sort_directly();

    return 0;
}