#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define ROZMIAR_BUFOR 256

int main() {

    pid_t pid;
    int fileDesc[2], in_fileDesc, n;
    char bufor[ROZMIAR_BUFOR];
    char nazwaPliku[32];
    
    if(pipe(fileDesc) < 0) {

        fprintf(stderr, "Blad tworzenia potoku\n");
        return 1;
    }

    pid = fork();

    if(pid == 0) {
        //child
        close(fileDesc[1]);
        close(0);
        dup(fileDesc[0]);
        close(fileDesc[0]);

        execlp("display", "display", "-", NULL);
    }
    else {
        //parent
        close(fileDesc[0]);
        printf("Podaj sciezke obrazu");
        scanf("%s", nazwaPliku);

        if((in_fileDesc = open(nazwaPliku, O_RDONLY)) < 0) {
            
            fprintf(stderr, "Nie udalo sie otworzyc pliku\n");
            return 2;
        }
        
        while((n = read(in_fileDesc, &bufor, ROZMIAR_BUFOR)) > 0) {
    
            if(write(fileDesc[1], &bufor, n) < 0) {
                fprintf(stderr, "Nie udalo sie zapisac do potoku\n");
                return 3;
            }  
        }
        close(in_fileDesc);
    } 
}
