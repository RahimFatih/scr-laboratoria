#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>


#define FILE_NAME_SIZE 64
#define BUFF_SIZE 256

int main(){

    char file_name[FILE_NAME_SIZE];
    int file, file_mem;
    struct stat st;
    char *file_memory, buff[BUFF_SIZE];

    while(1){
        file_mem = open("pamiec_wspoldz", O_RDWR | O_CREAT, 0666);/// Utworz pam.Wspoldzielona
 
        printf("\nWprowadz nazwe pliku:\n");/// Zapytaj o nazwe
        scanf("%s", file_name);
 
        file = open(file_name, O_RDONLY, 0666)/// otworz plik
 
        fstat(file, &st);/// Zapisuje dane o pliku do st

        truncate("pamiec_wspoldz", st.st_size )/// Otwórz plik wspoldzielony i zetnij go do rozmiaru pliku mapowaneg

        file_memory = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_mem, 0);///Null-kernel sam decyduje adres mapowanego obszaru
        //st.stize-rozmiar naszego obszaru,prot_read i write- flagi zezwalajace na zczytywanie i nadpisywanie obszaru, Map_shared-obszar dostępny dla innych procesow
        //file_mem-znasza pamiec wspoldzielona,0-offset

        read(file, file_memory, st.st_size);/// Wczytuje plik do zmapowanej pamięci wspoldzielonej
        
        msync(file_memory, st.st_size, MS_SYNC);/// Aktualizuje zmiany, MS_SYNC-aktualizuj i czekaj az skonczy

        while( (read(file_mem, &buff, BUFF_SIZE)) > 0 )/// Czyta plik
            printf("%s", buff );

        munmap(file_memory, st.st_size);/// Zwalnia "odmapowuje" zajętą pamięć

        /// Zamyka pliki
        close(file);
        close(file_mem);
    }


    /// Usuwa segment wsolny
    unlink( "pamiec_wspoldz")

    return 0;
}