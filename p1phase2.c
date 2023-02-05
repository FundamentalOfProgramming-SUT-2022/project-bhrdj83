#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.c"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

char *clipboard ;


/*void getstr(char *dest) {
    char c ;
    c = getch() ;
    int i = 0 ;
    textcolor(WHITE) ;
    textbackground(BLACK) ;
    while(c != ' ' && c != '\n') {
        dest[i] = c ;
        printf("%c", c) ;
        c = getch() ;
        i++ ;
    }
    if(c == ' ')
        printf("%c", c) ;
} 

void getname(char *dest) {
    char temp ;
    int i = 0 ;
    textcolor(WHITE) ;
    textbackground(BLACK) ;
    temp = getch() ;
    printf("%c", temp) ;
    if(temp == '\"') {
        temp = getch() ;
        printf("%c", temp) ;
        while(temp != '\"') {
            dest[i] = temp ;
            i++ ;
            temp = getch() ;
            printf("%c", temp) ;
        }
    }
    else {
        //dest[0] = c ;
        while(temp != ' ' && temp != '\n') {
            dest[i] = temp ;
            temp = getch() ;
            if(temp != ' ')
                printf("%c", temp) ;
        }
    }
}*/

void getstr(char *dest, int n) {
    textcolor(WHITE) ;
    textbackground(BLACK) ;
    scanf("%s", dest + n) ;
    //printf("%s\n", dest) ;
}

void getstr1(char *dest, int n) {
    textcolor(WHITE) ;
    textbackground(BLACK) ;
    printf("ok") ;
    scanf("%s", dest + n) ;
    //printf("%s\n", dest) ;
}

void getname_withspace(char *dest) {
    textcolor(WHITE) ;
    textbackground(BLACK) ;
    strcpy(dest, "root/") ;
    char c ;
    int i = 0 ;
    cscanf("%c", &c) ;
    while(c != '\"') {
        dest[i + 5] = c ;
        i++ ;
        cscanf("%c", &c) ;
    }
}

int count_text_lines(char *text) {
    int linecount = 1 ;
    for(int i = 0 ; i < strlen(text) ; i++) {
        if(text[i] == '\n')
            linecount++ ;
    }
    return linecount ;
}


void printscr(char *text, char *completename, char *mode, char savecon, int firstline) {
    gotoxy(1,1) ;
    clrscr() ;
    //gotoxy(1,1) ;
    int i, j = 0, x = 0, y = 0, linecounter = 1 ;
    textcolor(WHITE) ;
    textbackground(BLACK) ;
    for(j = 0 ; linecounter < firstline && j < strlen(text) ; j++) {
        if(text[j] == '\n')
            linecounter++ ;
    }
    for(i = 0 ; i < 28 ; i++) {
        if(text[j] != 0) {
            printf("%3d ", i + firstline) ;
            while(text[j] != '\n' && text[j] != 0) {
                cprintf("%c", text[j]) ;
                j++ ;
            }
            cprintf("\n") ;
            j++ ;
        }
        else
            cprintf("~\n") ;
    }
    textbackground(LIGHTBLUE) ;
    cprintf("  %s  ", mode) ;
    textbackground(LIGHTGRAY) ;
    textcolor(BLACK) ;
    cprintf("  %s   %c", completename, savecon) ;
    for(i = 6 + strlen(completename) ; i < 100 ; i++)
        printf(" ") ;
    cprintf("\n") ;
    textbackground(BLACK) ;
}

void printscr1(char *text, char *completename, char *mode, char savecon, int firstline) {
    int i, j = 0, x = 0, y = 0, linecounter = 1 ;
    memset(text, 0, 1000000) ;
    strcpy(mode, "Normal") ;
    FILE *myfile ;
    myfile = fopen(completename, "r") ;
    i = 0 ;
    char c = fgetc(myfile) ;
    while(!feof(myfile)) {
        text[i] = c ;
        c = fgetc(myfile) ;
        i++ ;
    }
    fclose(myfile) ;
    gotoxy(1,1) ;
    clrscr() ;
    //gotoxy(1,1) ;
    textcolor(WHITE) ;
    textbackground(BLACK) ;
    for(j = 0 ; linecounter < firstline && j < strlen(text) ; j++) {
        if(text[j] == '\n')
            linecounter++ ;
    }
    for(i = 0 ; i < 28 ; i++) {
        if(text[j] != 0) {
            printf("%3d ", i + firstline) ;
            while(text[j] != '\n' && text[j] != 0) {
                cprintf("%c", text[j]) ;
                j++ ;
            }
            cprintf("\n") ;
            j++ ;
        }
        else
            cprintf("~\n") ;
    }
    textbackground(LIGHTBLUE) ;
    cprintf("  %s  ", mode) ;
    textbackground(LIGHTGRAY) ;
    textcolor(BLACK) ;
    cprintf("  %s   %c", completename, savecon) ;
    for(i = 6 + strlen(completename) ; i < 100 ; i++)
        printf(" ") ;
    cprintf("\n") ;
    textbackground(BLACK) ;
}

int iswithspace() {
    textcolor(WHITE) ;
    textbackground(BLACK) ;
    int i ;
    char crstr[100] = {0} ;
    //printf("ok") ;
    
    getchar() ;
    //printf("ok") ;
    i = 0 ;
    scanf("%c", &crstr[0]) ;
    while(crstr[i] != '/') {
        i++ ;
        scanf("%c", &crstr[i]) ;
    }
    //printf("%s", crstr) ;
    if(!(strcmp(crstr, "root/"))) {
        //printf("ok") ;
        return 0 ;
    }
    else
        return 1 ;
}

int main() {
    clipboard = (char*)calloc(1000000, sizeof(char)) ;
    char c, str[100], mode[100] = "Normal", completename[100] = "temp", savecon = '+', command[100], temp ;
    char *text = (char*)calloc(1000000, sizeof(char)) ;
    int i, j, counter, linecounter, firstline = 1, flag, endline, endchar ;
    int x = 0 ;
    int y = 0 ;
    FILE *myfile ;
    /*for(i = 0 ; i < 60 ; i+= 2) {
        text[i] = i / 2 + 1 ;
        text[i + 1] = '\n' ;
    }*/
    text = "1\n2\n3\n4\n5\n6\n71\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n1\n26\n27\n28\n29\n30" ;
    linecounter = count_text_lines(text) ;
    printscr(text, completename, mode, savecon, 1) ;
    gotoxy(5,1) ;
    while(1) {
        //clrscr() ;
        //printf("helloworld\nhow are you\nhyooo") ;
        x = wherex() ;
        y = wherey() ;
        c = getch() ;
        switch(c) {
            case 'j' :
                if(y == 24 && (firstline + 27 < linecounter)) {
                    firstline++ ;
                    printscr(text, completename, mode, savecon, firstline) ;
                    counter = 1 ;
                    for(i = 0 ; i < strlen(text) ; i++) {
                        if(text[i] == '\n')
                            counter++ ;
                        if(counter == y + firstline - 1)
                            break ;
                    }
                    if(text[i] == '\n')
                        i++ ;
                    j = 5 ;
                    while(text[i] != '\n' && text[i] != 0) {
                        i++ ;
                        j++ ;
                    }
                    if(x > j)
                        gotoxy(j, y) ;
                    else
                        gotoxy(x, y) ;
                }
                else if(y < 28) {
                    counter = 1 ;
                    for(i = 0 ; i < strlen(text) ; i++) {
                        if(text[i] == '\n')
                            counter++ ;
                        if(counter == y + firstline)
                            break ;
                    }
                    if(text[i] == '\n')
                        i++ ;
                    j = 5 ;
                    while(text[i] != '\n' && text[i] != 0) {
                        i++ ;
                        j++ ;
                    }
                    if(x > j)
                        gotoxy(j, ++y) ;
                    else
                        gotoxy(x, ++y) ;
                }
                break ;
            case 'k' :
                if(y == 5 && firstline > 1) {
                    firstline-- ;
                    printscr(text, completename, mode, savecon, firstline) ;
                    counter = 1 ;
                    for(i = 0 ; i < strlen(text) ; i++) {
                        if(text[i] == '\n')
                            counter++ ;
                        if(counter == y + firstline - 1)
                            break ;
                    }
                    if(text[i] == '\n')
                        i++ ;
                    j = 5 ;
                    while(text[i] != '\n' && text[i] != 0) {
                        i++ ;
                        j++ ;
                    }
                    if(x > j)
                        gotoxy(j, y) ;
                    else
                        gotoxy(x, y) ;
                }
                else if(y > 1) {
                    counter = 1 ;
                    for(i = 0 ; i < strlen(text) ; i++) {
                        if(text[i] == '\n')
                            counter++ ;
                        if(counter == y + firstline - 2)
                            break ;
                    }
                    if(text[i] == '\n')
                        i++ ;
                    j = 5 ;
                    while(text[i] != '\n' && text[i] != 0) {
                        i++ ;
                        j++ ;
                    }
                    if(x > j)
                        gotoxy(j, --y) ;
                    else
                        gotoxy(x, --y) ;
                }
                break ;
            case 'h' :
                if(x > 5) {
                    gotoxy(--x, y) ;
                }
                break ;
            case 'l' :
                counter = 1 ;
                for(i = 0 ; i < strlen(text) ; i++) {
                    if(text[i] == '\n')
                        counter++ ;
                    if(counter == y + firstline - 1)
                        break ;
                }
                if(text[i] == '\n')
                    i++ ;
                for(j = i ; j < i + x - 5; j++) ;
                if(text[j] != '\n' && text[j] != 0)
                    gotoxy(++x, y) ;
                break ;
            case ':' :
                gotoxy(1, 30) ;
                //clrscr() ;
                //textcolor(WHITE) ;
                //textbackground(BLACK) ;
                //cputs("hello world") ;
                memset(command, 0, 100) ;
                getstr(command, 0) ;
                if(!strcmp(command, "open")) {
                    //printf("%s", command) ;
                    if(savecon == '-') {

                    }
                    else {
                        //printf("ok") ;
                        memset(completename, 0, 100) ;
                        if(iswithspace()) 
                            getname_withspace(completename) ;
                        else{
                            //printf("ok") ;
                            strcpy(completename, "root/") ;
                            //printf("ok") ;
                            getstr(completename, 5) ;
                            //printf("ok") ;
                        }
                        
                        textcolor(WHITE) ;
                        textbackground(BLACK) ;
                        //gotoxy(5, 1) ;
                        //printf("%s", completename) ;
                        memset(text, 0, 1000000) ;
                        //printf("ok") ;
                        savecon = '+' ;
                        strcpy(mode, "Normal") ;
                        firstline = 1 ;
                        myfile = fopen(completename, "r") ;
                        i = 0 ;
                        temp = fgetc(myfile) ;
                        while(!feof(myfile)) {
                            text[i] = temp ;
                            temp = fgetc(myfile) ;
                            i++ ;
                        }
                        fclose(myfile) ;
                        //printf("ok") ;
                        linecounter = count_text_lines(text) ;
                        printscr(text, completename, mode, '+', 1) ;
                        gotoxy(5, 1) ;
                    }
                }
                break ;
            /*case 'v' :
                int startline = y, startchar = x ;
                while(1) {
                    temp = getch() ;
                    switch(temp) {
                        case 'j' :
                            if(y == 24 && (firstline + 27 < linecounter)) {
                            firstline++ ;
                            printscr(text, completename, mode, savecon, firstline) ;
                            counter = 1 ;
                            for(i = 0 ; i < strlen(text) ; i++) {
                                if(text[i] == '\n')
                                    counter++ ;
                                if(counter == y + firstline - 1)
                                    break ;
                            }
                            if(text[i] == '\n')
                                i++ ;
                            j = 5 ;
                            while(text[i] != '\n' && text[i] != 0) {
                                i++ ;
                                j++ ;
                            }
                            if(x > j)
                                gotoxy(j, y) ;
                            else
                                gotoxy(x, y) ;
                            }
                else if(y < 28) {
                    counter = 1 ;
                    for(i = 0 ; i < strlen(text) ; i++) {
                        if(text[i] == '\n')
                            counter++ ;
                        if(counter == y + firstline)
                            break ;
                    }
                    if(text[i] == '\n')
                        i++ ;
                    j = 5 ;
                    while(text[i] != '\n' && text[i] != 0) {
                        i++ ;
                        j++ ;
                    }
                    if(x > j)
                        gotoxy(j, ++y) ;
                    else
                        gotoxy(x, ++y) ;
                }
                break ;
            case 'k' :
                if(y == 5 && firstline > 1) {
                    firstline-- ;
                    printscr(text, completename, mode, savecon, firstline) ;
                    counter = 1 ;
                    for(i = 0 ; i < strlen(text) ; i++) {
                        if(text[i] == '\n')
                            counter++ ;
                        if(counter == y + firstline - 1)
                            break ;
                    }
                    if(text[i] == '\n')
                        i++ ;
                    j = 5 ;
                    while(text[i] != '\n' && text[i] != 0) {
                        i++ ;
                        j++ ;
                    }
                    if(x > j)
                        gotoxy(j, y) ;
                    else
                        gotoxy(x, y) ;
                }
                else if(y > 1) {
                    counter = 1 ;
                    for(i = 0 ; i < strlen(text) ; i++) {
                        if(text[i] == '\n')
                            counter++ ;
                        if(counter == y + firstline - 2)
                            break ;
                    }
                    if(text[i] == '\n')
                        i++ ;
                    j = 5 ;
                    while(text[i] != '\n' && text[i] != 0) {
                        i++ ;
                        j++ ;
                    }
                    if(x > j)
                        gotoxy(j, --y) ;
                    else
                        gotoxy(x, --y) ;
                }
                break ;
            case 'h' :
                if(x > 5) {
                    gotoxy(--x, y) ;
                }
                break ;
            case 'l' :
                counter = 1 ;
                for(i = 0 ; i < strlen(text) ; i++) {
                    if(text[i] == '\n')
                        counter++ ;
                    if(counter == y + firstline - 1)
                        break ;
                }
                if(text[i] == '\n')
                    i++ ;
                for(j = i ; j < i + x - 5; j++) ;
                if(text[j] != '\n' && text[j] != 0)
                    gotoxy(++x, y) ;
                break ;
            case 'c' :
                endline = y ;
                endchar = x ;
                break ;
            case 'd' :
                endline = y ;
                endchar = x ;
                break ;
            }
            if(temp == 'c' || temp == 'd')
                break ;
        }
        if(temp == 'c') {*/

        }
    }

    return 0 ;
}