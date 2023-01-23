#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void getstr(char *dest) {
    scanf("%s", dest) ;
}

void invalid_command() {
    printf("invalid command\n") ;
    char c ;
    while((c = getchar()) != '\n') ;
}

void crfile_withoutspace() {
    //printf("ok") ;
    int slashcounter = 0, i, j, flag ;
    char wsname[100], compeletename[100] = "root/", dirname[100] = "root/" ;
    getstr(wsname) ;
    for(i = 0 ; wsname[i] != '\0' ; i++)
        if(wsname[i] == '/')
            slashcounter++ ;
    for (i = 0 ; i < slashcounter ; i++){
        flag = 0 ;
        for ( j = 0 ; flag < i + 1 ; j++){
            if (wsname[j] == '/'){
                if(++flag >= i + 1)
                    break ;
            }
            else
                dirname[j + 5] = wsname[j] ;
        }
        mkdir(dirname) ;
    }
    for(i = 0 ; wsname[i] != '\0' ; i++)
        compeletename[i + 5] = wsname[i] ;
    FILE *newfile ;
    if(newfile = fopen(compeletename, "r")) {
        printf("file already exists!") ;
    }
    else {
        newfile = fopen(compeletename, "w") ;
        printf("new file created successfuly!\n") ;
    }
    fclose(newfile) ;
}

void crfile_withspace() {
    
}

void createfile() {
    int i ;
    char fileatr[100] = {0}, crstr[100] = {0} ;
    //printf("ok2\n") ;
    getstr(fileatr) ;
    if (strcmp(fileatr, "--file"))
        invalid_command() ;
    else {
        getchar() ;
        i = 0 ;
        scanf("%c", &crstr[0]) ;
        while(crstr[i] != '/') {
            i++ ;
            scanf("%c", &crstr[i]) ;
        }
        if((strcmp(crstr, "root/")) && (strcmp(crstr, "\"root/")))
            invalid_command() ;
        else if(!(strcmp(crstr, "root/")))
            crfile_withoutspace() ;
        else
            crfile_withspace() ;
    }
}

int main () {
    char command[100] ;
    while(1) {
        getstr(command) ;
        if (!strcmp(command, "createfile")) 
            createfile() ;
        else if(!strcmp(command, "exit")) 
            break ;
        else 
            invalid_command() ;
    }
    return 0 ;
}