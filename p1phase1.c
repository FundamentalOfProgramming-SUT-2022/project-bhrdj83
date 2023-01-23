#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void getstr(char *dest, int n) {
    scanf("%s", dest + n) ;
}

void getname_withspace(char *dest) {
    strcpy(dest, "root/") ;
    char c ;
    int i = 0 ;
    scanf("%c", &c) ;
    while(c != '\"') {
        dest[i + 5] = c ;
        i++ ;
        scanf("%c", &c) ;
    }
}

int invalid_command() {
    char fileatr[100] = {0} ;
    getstr(fileatr, 0) ;
    if(strcmp(fileatr, "--file")){
        printf("invalid command\n") ;
        char c ;
        while((c = getchar()) != '\n') ;
        return 1 ;
    }
    else
        return 0 ;
}

int iswithspace() {
    int i ;
    char crstr[100] = {0} ;
    
    getchar() ;
    i = 0 ;
    scanf("%c", &crstr[0]) ;
    while(crstr[i] != '/') {
        i++ ;
        scanf("%c", &crstr[i]) ;
    }
    if(!(strcmp(crstr, "root/")))
        return 0 ;
    else
        return 1 ;
}

void crfile_withoutspace() {
    //printf("ok") ;
    int slashcounter = 0, i, j, flag ;
    char wsname[100], completename[100] = "root/", dirname[100] = "root/" ;
    getstr(wsname, 0) ;
    for(i = 0 ; wsname[i] != '\0' ; i++)
        if(wsname[i] == '/')
            slashcounter++ ;
    for (i = 0 ; i < slashcounter ; i++){
        flag = 0 ;
        for ( j = 0 ; flag < i + 1 ; j++){
            if (wsname[j] == '/'){
                if(++flag >= i + 1)
                    break ;
                else
                    dirname[j + 5] = wsname[j] ;
            }
            else
                dirname[j + 5] = wsname[j] ;
        }
        mkdir(dirname) ;
        strcpy(dirname, "root/") ;
    }
    for(i = 0 ; wsname[i] != '\0' ; i++)
        completename[i + 5] = wsname[i] ;
    FILE *newfile ;
    if(newfile = fopen(completename, "r")) {
        printf("file already exists!\n") ;
    }
    else {
        newfile = fopen(completename, "w") ;
        printf("new file created successfuly!\n") ;
    }
    fclose(newfile) ;
}

void crfile_withspace() {
    char c, completename[100] = "root/", dirname[100] = {0} ;
    int i = 0, slashcounter = 0, flag, j ;
    scanf("%c", &c) ;
    while(c != '\"') {
        completename[i + 5] = c ;
        if(c == '/')
            slashcounter++ ;
        i++ ;
        scanf("%c", &c) ;
    }
    /*i = 0 ;
    while(completename[i] != '\"'){
        printf("%c", completename[i]) ;
        i++ ;
    }*/
    for (i = 1 ; i < slashcounter + 1 ; i++){
        flag = 0 ;
        for ( j = 0 ; flag < i + 1 ; j++){
            if (completename[j] == '/'){
                if(++flag >= i + 1)
                    break ;
                else
                    dirname[j] = completename[j] ;
            }
            else
                dirname[j] = completename[j] ;
        }
        mkdir(dirname) ;
    }
    FILE *newfile ;
    if(newfile = fopen(completename, "r")) {
        printf("file already exists!\n") ;
    }
    else {
        newfile = fopen(completename, "w") ;
        printf("new file created successfuly!\n") ;
    }
    fclose(newfile) ;
}

void createfile() {
    if (invalid_command()) ;
    else {
        if(iswithspace())
            crfile_withspace() ;
        else
            crfile_withoutspace() ;
    }
}

void cat() {
    char completename[100] = {0}, linestr[1000] = {0} ;
    if (invalid_command()) ;
    else {
        if(iswithspace()) 
            getname_withspace(completename) ;
        else{
            strcpy(completename, "root/") ;
            getstr(completename, 5) ;
        }
        //puts(completename) ;
        FILE *myfile ;
        myfile = fopen(completename, "r") ;
        if(!myfile)
            printf("file doesn't exist!\n") ;
        else {
            char c ;
            while(!feof(myfile)) {
                c = fgetc(myfile) ;
                printf("%c", c) ;
            }
            printf("\n") ;
        }
        fclose(myfile) ;
    }
}

int main () {
    char command[100] ;
    while(1) {
        getstr(command, 0) ;
        if (!strcmp(command, "createfile")) 
            createfile() ;
        else if(!strcmp(command, "cat"))
            cat() ;
        else if(!strcmp(command, "exit")) 
            break ;
        else {
            printf("invalid command\n") ;
            char c ;
            while((c = getchar()) != '\n') ;
        }
    }
    return 0 ;
}