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

void getstr_withspace(char *dest) {
    char c ;
    int i = 0 ;
    scanf("%c", &c) ;
    while(c != '\"' || dest[i - 1] == '\\') {
        dest[i] = c ;
        i++ ;
        scanf("%c", &c) ;
    }
}

int invalid_command(int mode) {
    int v ;
    char fileatr[100] = {0} ;
    getstr(fileatr, 0) ;
    switch(mode) {
        case 1 :
            v = strcmp(fileatr, "--file") ;
            break ;
        case 2 :
            v = strcmp(fileatr, "--str") ;
            break ;
        case 3 :
            v = strcmp(fileatr, "--pos") ;
            break ;
    }
    if(v){
        printf("invalid command\n") ;
        char c ;
        while((c = getchar()) != '\n') ;
        return 1 ;
    }
    else
        return 0 ;
}

int Flag(int mode) {
    int i ;
    char flagname[100] = {0} ;
    getstr(flagname, 0) ;
    switch(mode) {
        case 1 :
            if(strcmp(flagname, "-size")){
                printf("invalid flag") ;
                return 0 ;
            }
            else {
                scanf("%d", &i) ;
                return i ;
            }
            break ;
        case 2 :
            if(!strcmp(flagname, "-f"))
                return 1 ;
            else if(!strcmp(flagname, "-b"))
                return -1 ;
            else {
                printf("invalid flag") ;
                return 0 ;
            }
            break ;
    }
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

char str_space() {
    char c ;
    getchar() ;
    scanf("%c", &c) ;
    return c ;
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
    if (invalid_command(1)) ;
    else {
        if(iswithspace())
            crfile_withspace() ;
        else
            crfile_withoutspace() ;
    }
}

void write_str(FILE *file, char *string) {
    int i = 0 ;
    while(string[i] != 0) {
        if(string[i] == '\\') {
            i++ ;
            if(string[i] == 'n')
                putc('\n', file) ;
            else if(string[i] == '\"')
                putc('\"', file) ;
            else
                putc('\\', file) ;
        }
        else
            putc(string[i], file) ;
        i++ ;
    }
}

void cat() {
    char completename[100] = {0}, linestr[1000] = {0} ;
    if (invalid_command(1)) ;
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

void insert() {
    char completename[100] = {0}, str[1000] = {0}, c ;
    char *before = (char*)calloc(1000000, sizeof(char)) ;
    char *after = (char*)calloc(1000000, sizeof(char)) ;
    int linepose, charpose, i, j ;
    if(invalid_command(1)) 
        return ;
    else {
        if(iswithspace()) 
            getname_withspace(completename) ;
        else{
            strcpy(completename, "root/") ;
            getstr(completename, 5) ;
        }
    }
    if(invalid_command(2))
        return ;
    else {
        if((c = str_space()) == '\"'){
            getstr_withspace(str) ;
        }
        else {
            str[0] = c ;
            getstr(str, 1) ;
        }
    }
    if(invalid_command(3))
        return ;
    else {
        scanf("%d:%d", &linepose, &charpose) ;
    }
    FILE *myfile ;
    myfile = fopen(completename, "r") ;
    if(!myfile) {
        printf("file doesn't exist!\n") ;
        fclose(myfile) ;
        return ;
    }
    i = 1 ;
    j = 0 ;
    while(i < linepose) {
        c = fgetc(myfile) ;
        if(feof(myfile)) {
            if(i == linepose - 1 && charpose == 0){
                before[j] = '\n' ;
                break ;
            }
            else {
                printf("invalid line position\n") ;
                return ;
            }
        }
        before[j] = c ;
        j++ ;
        if(c == '\n')
            i++ ;
        
    }
    for(i = 0 ; i < charpose ; i++) {
        c = fgetc(myfile) ;
        if(feof(myfile)) {
            printf("invalid character position\n") ;
            return ;
        }
        if(c == '\n') {
            printf("invalid character position\n") ;
            return ;
        }
        before[j] = c ;
        j++ ;
    }
    i = 0 ;
    c = fgetc(myfile) ;
    while(!feof(myfile)) {
        after[i] = c ;
        i++ ;
        c = fgetc(myfile) ;
    }
    fclose(myfile) ;
    myfile = fopen(completename, "w") ;
    fprintf(myfile, "%s", before) ;
    write_str(myfile, str) ;
    fprintf(myfile, "%s", after) ;
    fclose(myfile) ;
    printf("file updated successfuly!\n") ;
}

int removefunc(char *completename, int linepose, int charpose, int rmsize, int direction) {
    char *before = (char*)calloc(1000000, sizeof(char)) ;
    char *after = (char*)calloc(1000000, sizeof(char)) ;
    int i, j, beforecounter = 0 ;
    char c ;
    FILE *myfile ;
    myfile = fopen(completename, "r") ;
    if(!myfile) {
        printf("file doesn't exist!\n") ;
        fclose(myfile) ;
        return 0 ;
    }
    i = 1 ;
    j = 0 ;
    while(i < linepose) {
        c = fgetc(myfile) ;
        if(feof(myfile)) {
            if(i == linepose - 1 && charpose == 0){
                before[j] = '\n' ;
                beforecounter++ ;
                break ;
            }
            else {
                printf("invalid line position\n") ;
                return 0 ;
            }
        }
        before[j] = c ;
        beforecounter++ ;
        j++ ;
        if(c == '\n')
            i++ ;
        
    }
    for(i = 0 ; i < charpose ; i++) {
        c = fgetc(myfile) ;
        if(feof(myfile)) {
            printf("invalid character position\n") ;
            return 0 ;
        }
        if(c == '\n') {
            printf("invalid character position\n") ;
            return 0 ;
        }
        before[j] = c ;
        beforecounter++ ;
        j++ ;
    }
    i = 0 ;
    c = fgetc(myfile) ;
    while(!feof(myfile)) {
        after[i] = c ;
        i++ ;
        c = fgetc(myfile) ;
    }
    fclose(myfile) ;
    /*if(direction == 1) {
        for(i = 0 ; after[i] != 0 ; i++)
            after[i] = after[i + rmsize] ;
    }*/
    if(direction == -1) {
        for(i = beforecounter - 1 ; i >= beforecounter - rmsize ; i--)
            before[i] = 0 ;
        myfile = fopen(completename, "w") ;
        fprintf(myfile, "%s", before) ;
        fprintf(myfile, "%s", after) ;
        fclose(myfile) ;
    }
    else {
        myfile = fopen(completename, "w") ;
        fprintf(myfile, "%s", before) ;
        fprintf(myfile, "%s", after + rmsize) ;
        fclose(myfile) ;
    }
    return 1 ;

}

void removestr() {
    char completename[100] = {0} ;
    int linepose, charpose, i, j, rmsize, direction ;
    if(invalid_command(1)) 
        return ;
    else {
        if(iswithspace()) 
            getname_withspace(completename) ;
        else{
            strcpy(completename, "root/") ;
            getstr(completename, 5) ;
        }
    }
    if(invalid_command(3))
        return ;
    else {
        scanf("%d:%d", &linepose, &charpose) ;
    }
    if((rmsize = Flag(1)) == 0)
        return ;
    if((direction = Flag(2)) == 0)
        return ;
    if(removefunc(completename, linepose, charpose, rmsize, direction))
        printf("removed string from file successfuly!\n") ;
}

int main () {
    char command[100] ;
    while(1) {
        getstr(command, 0) ;
        if (!strcmp(command, "createfile")) 
            createfile() ;
        else if(!strcmp(command, "cat"))
            cat() ;
        else if(!strcmp(command, "insertstr"))
            insert() ;
        else if(!strcmp(command, "removestr")) 
            removestr() ;
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