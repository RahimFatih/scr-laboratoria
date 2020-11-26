#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h> 
#include <string.h> 
#include <sys/wait.h> 
#include <stdlib.h>

#define BUFFSIZE 512


int main(int argc, char* argv[])
{

int file_desc[2];
char buf[BUFFSIZE];


if(pipe(file_desc) == -1)
{
        printf("Blad podczas tworzenia potoku. \n");
}
else
{
        printf("Potok zostal utworzony pomyslnie. \n");
}

int id = fork();

if(id < 0)
{
        printf("Nie utworzono procesu potomnego. \n");
}
else if(id == 0)
{
        close(file_desc[1]);

        while(read(file_desc[0], &buf, BUFFSIZE)>0){
	printf("#%s#\n", buf);
	}
        close(file_desc[0]);


}
else
{       printf("Witam! Jestem procesem nadrzędnym. \n");
        close(file_desc[0]);


        if ( argc != 2 ) 
        {
                printf("Nieprawidlowa liczba argumentow \n");
        }
        else
        {
                FILE *filepointer = fopen( argv[1], "r" );
                write(file_desc[1], buf, BUFFSIZE);
                close(file_desc[1]);
        }
}


return 0;
}