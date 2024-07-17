//-----------CHECK-IF-FILE-IS-.txt------------------

#define DATA 11
#include <bits/posix2_lim.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#define WORD_LENGTH 64

void isTexrFile() {
    char extension[]     = ".txt";
    int fd_file;
    char *fileName = "file1.txt";
    struct stat stat;

    // Open file
    fd_file = open(fileName, O_RDONLY);
    if (fd_file < 0) {
        printf("Errore apertura file");
        /*
        printf("FILE: %s\n", fullpath);
        perror("Open file:");
        result.nb_files = -1;
        return (&result);
        */
    }
    int lastindex = strlen(fileName);
    // Get file info
    int ret = fstat(fd_file, &stat);
    // Check if it is a regular file and if it is a .txt file
    if (S_ISREG(stat.st_mode) && 
        fileName[lastindex-1] == extension[3] &&
        fileName[lastindex-2] == extension[2] &&
        fileName[lastindex-3] == extension[1] &&
        fileName[lastindex-4] == extension[0]) {
        
        // do something on file
    }
}

// conto il numero di righe che iniziano con una lettera minuscola e che hanno un numero di occorrenze del caratter c pari o superiore a occ
void contaOccorrenzeCarattere() {
    int dimLine, count_letters, nread, fd, ris, occ;
    char read_char, err[128], line_buffer[256], c;


    dimLine = 0;
    count_letters = 0;
    while ((nread = read(fd, &read_char, sizeof(char))) != 0) {
        if (nread < 0) {
            sprintf(err, "(PID %d) impossibile leggere dal file", getpid());
            perror(err);
            ris = -1;
            break;
        } else {
            if(read_char == '\n'){
                line_buffer[dimLine++] = '\0';
                if(line_buffer[0] >= 'a' && line_buffer[0] <= 'z'){
                    for(int i=0;i<dimLine;i++){
                        if(line_buffer[i] == c) count_letters++;
                    }
                    if (count_letters >= occ) ris++;
                }
                dimLine = 0;
                count_letters = 0;
            }
            else{
                line_buffer[dimLine++] = read_char;
            }  
        }
    }
}


void leggiFileperRiga() {
    int dimLine, count_letters, nread, fd;
    char read_char, err[128], line_buffer[256];

    // conto il numero di righe che iniziano con una lettera minuscola e che hanno un numero di occorrenze del caratter c pari o superiore a occ
    dimLine = 0;
    count_letters = 0;
    while ((nread = read(fd, &read_char, sizeof(char))) != 0) {
        if (nread < 0) {
            sprintf(err, "Impossibile leggere dal file");
            perror(err);
            break;
        } else {
            if(read_char == '\n'){
                line_buffer[dimLine++] = '\0';

                // esegui operazioni sulla linea

                dimLine = 0;
                count_letters = 0;
            }
            else{
                line_buffer[dimLine++] = read_char;
            }  
        }
    }
}

//funzione che controlla se il file contiene la parola specificata
int fileContieneParola(char *file, char *parola){
    // rightFile vale 1 se il file contiene la parola, -1 se il file non esiste, -2 se il file non contiene la parola
    int rightFile = -1, fd, nread;
    char read_char, err[128], word_buffer[WORD_LENGTH], separatori[32];

    /* Verifico file */
    if ((fd = open(file, O_RDONLY)) < 0) {
        perror("Errore apertura file sorgente");
        
    }
    else{
        /* Se il file esiste */
        int count_letters = 0;
        rightFile = -2;
        strcpy(separatori, " \t\r\n.,;:'\"()-`*&^#@!$\\|[]{}?/");

        //leggo un carattere alla volta
        while ((nread = read(fd, &read_char, sizeof(char))) != 0) {
            if (nread < 0) {
                sprintf(err, "(PID %d) impossibile leggere dal file", getpid());
                perror(err);
                break;
            } else {
                int fineParola = -1;

                for(int i=0;i<strlen(separatori); i++){
                    if(read_char == separatori[i]){
                        fineParola = 0;
                        break;
                    }
                }
                if (fineParola == 0) {
                    word_buffer[count_letters] = '\0';
                    if (strcmp(word_buffer, parola)==0) { 
                        // parola uguale
                        rightFile = 1;
                        break;
                    }
                    count_letters = 0;
                } else { // carattere
                    word_buffer[count_letters] = read_char;
                    count_letters++;
                }
            }
        } //while read
        if (rightFile) {
            printf("Il file %s contiene la parola %s\n", file, parola);
        }
        else{
            printf("Il file %s contiene la parola %s\n", file, parola);
        }
                
        close(fd);
    }

    return rightFile;
}

int eliminaOccorrenzeParola(char *file, char *parola){
    int res = 0, fd, fd_temp, nread;
    char separatori[32], fileTemp[256], read_char, err[256], word_buffer[64];

    /* Verifico file */
    if ((fd = open(file, O_RDONLY)) < 0) {
        perror("Errore apertura file sorgente");
        res = -1;
    }

    /* Se il file esiste */
    if (res == 0) {
        /* Creo il file temporaneo */
        fileTemp[0] = '\0';
        strcat(fileTemp, file);
        strcat(fileTemp, "_temp");
        if ((fd_temp = open(fileTemp, O_CREAT | O_WRONLY, 0777)) < 0) {
            perror("Errore apertura file");
            res = -1;
        } else { // Se il file temporaneo è stato creato correttamente
            /* Eliminazione della parola */

            int count_letters = 0;
            while ((nread = read(fd, &read_char, sizeof(char))) != 0) {
                if (nread < 0) {
                    sprintf(err, "(PID %d) impossibile leggere dal file", getpid());
                    perror(err);
                    res = -1;
                    break;
                } else {
                    int fineParola = 0;
                    for(int i=0;i<strlen(separatori); i++){
                        if(read_char == separatori[i]){
                            fineParola = 1;
                            break;
                        }
                    }
                    if (fineParola) {
                        word_buffer[count_letters] = '\0';
                        if (strcmp(word_buffer, parola)) { // parola diversa
                            write(fd_temp, &word_buffer, strlen(word_buffer));
                        } else {
                            res++;
                        }
                        count_letters = 0;

                        write(fd_temp, &read_char, 1);
                    } else { // carattere
                        word_buffer[count_letters] = read_char;
                        count_letters++;
                    }
                }
            }
        }
    }
    if (res >= 0) {
        printf("Nel file %s sono state eliminate %d occorrenze della parola %s\n", file, res, parola);
    }

    close(fd);
    close(fd_temp);

    // Rinomino il file temporaneo, sovrascrivendo il file originale
    rename(fileTemp, file);

    return res;
}

//formato gg/mm/aaaa
int checkData(char data[DATA]){
    int res = -1;


    if( strlen(data) == 10 &&
        data[2] == '/' && data[5] == '/'  &&
        data[0]>= '0' && data[0] <= '9' &&
        data[1]>= '0' && data[1] <= '9' &&
        data[3]>= '0' && data[3] <= '9' &&
        data[4]>= '0' && data[4] <= '9' &&
        data[6]>= '0' && data[6] <= '9' &&
        data[7]>= '0' && data[7] <= '9' &&
        data[8]>= '0' && data[8] <= '9' &&
        data[9]>= '0' && data[9] <= '9'
    ) res = 0;


    return res;
}
