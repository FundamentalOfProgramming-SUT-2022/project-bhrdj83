#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *clipboard ;

void getstr(char *dest, int n) {
    scanf("%s", dest + n) ;
    //printf("%s\n", dest) ;
}

void getstring(char *dest, int n) {
    char c ;
    int i = n ;
    scanf("%c", &c) ;
    while(c != ' ') {
        dest[i] = c ;
        i++ ;
        scanf("%c", &c) ;
    }
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
    //getchar() ;
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
        case 4 :
            v = strcmp(fileatr, "--str1") ;
            break ;
        case 5 :
            v = strcmp(fileatr, "--str2") ;
            break ;
    }
    if(v){
        printf("invalid command\n") ;
        //printf("%s\n", fileatr) ;
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

void undofunc(char *completename) {
    char undocompletename[100] = {0}, c;
    strcpy(undocompletename, completename) ;
    memcpy(undocompletename, "undo/", 5) ;
    FILE *currentfile ;
    FILE *backup ;
    currentfile = fopen(completename, "r") ;
    backup = fopen(undocompletename, "w") ;
    c = fgetc(currentfile) ;
    while(!feof(currentfile)) {
        fputc(c, backup) ;
        c = fgetc(currentfile) ;
    }
    fclose(currentfile) ;
    fclose(backup) ;
}

void crfile_withoutspace() {
    //printf("ok") ;
    int slashcounter = 0, i, j, flag ;
    char wsname[100], completename[100] = "root/", dirname[100] = "root/", undocompletename[100] = "undo/", undodirname[100] = "undo/" ;
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
                else{
                    dirname[j + 5] = wsname[j] ;
                    undodirname[j + 5] = wsname[j] ;
                }
            }
            else {
                dirname[j + 5] = wsname[j] ;
                undodirname[j + 5] = wsname[j] ;
            }
        }
        mkdir(dirname) ;
        mkdir(undodirname) ;
        strcpy(dirname, "root/") ;
        strcpy(dirname, "undo/") ;
    }
    for(i = 0 ; wsname[i] != '\0' ; i++) {
        completename[i + 5] = wsname[i] ;
        undocompletename[i + 5] = wsname[i] ;
    }
    FILE *newfile ;
    FILE *oldfile ;
    if(newfile = fopen(completename, "r")) {
        printf("file already exists!\n") ;
    }
    else {
        newfile = fopen(completename, "w") ;
        oldfile = fopen(undocompletename, "w") ;
        printf("new file created successfuly!\n") ;
        fclose(oldfile) ;
    }
    fclose(newfile) ;
}

void crfile_withspace() {
    char c, completename[100] = "root/", dirname[100] = {0}, undocompletename[100] = "undo/", undodirname[100] = {0} ;
    int i = 0, slashcounter = 0, flag, j ;
    scanf("%c", &c) ;
    while(c != '\"') {
        completename[i + 5] = c ;
        undocompletename[i + 5] = c ;
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
                else {
                    dirname[j] = completename[j] ;
                    undodirname[j] = undocompletename[j] ;
                }
            }
            else {
                dirname[j] = completename[j] ;
                undodirname[j] = undocompletename[j] ;
            }
        }
        mkdir(dirname) ;
        mkdir(undodirname) ;
    }
    FILE *newfile ;
    FILE *oldfile ;
    if(newfile = fopen(completename, "r")) {
        printf("file already exists!\n") ;
    }
    else {
        newfile = fopen(completename, "w") ;
        oldfile = fopen(undocompletename, "w") ;
        printf("new file created successfuly!\n") ;
        fclose(oldfile) ;
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
    char completename[100] = {0}, c ;
    char *str = (char*)calloc(1000000, sizeof(char)) ;
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
            getstring(str, 1) ;
        }
    }
    if(invalid_command(3))
        return ;
    else {
        scanf("%d:%d", &linepose, &charpose) ;
    }
    undofunc(completename) ;
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
    undofunc(completename) ;
    if(removefunc(completename, linepose, charpose, rmsize, direction))
        printf("removed string from file successfuly!\n") ;
}

int copyfunc(char *completename, int linepose, int charpose, int cpsize, int direction) {
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
    memset(clipboard, 0, sizeof(clipboard)) ;
    //puts(clipboard) ;
    if(direction == 1) {
        for(i = 0 ; i < cpsize ; i++) {
            clipboard[i] = after[i] ;
        }
    }
    else {
        for(i = 0 ; i < cpsize ; i++ ) {
            clipboard[i] = before[beforecounter - cpsize + i] ;
        }
    }
    //printf("%c\n", clipboard[10]) ;
    return 1 ;
}

void copystr() {
    char completename[100] = {0} ;
    int linepose, charpose, i, j, cpsize, direction ;
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
    if((cpsize = Flag(1)) == 0)
        return ;
    if((direction = Flag(2)) == 0)
        return ;
    if(copyfunc(completename, linepose, charpose, cpsize, direction))
        printf("copied string successfuly!\n") ;
}

void cutstr() {
    char completename[100] = {0} ;
    int linepose, charpose, i, j, cpsize, direction ;
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
    if((cpsize = Flag(1)) == 0)
        return ;
    if((direction = Flag(2)) == 0)
        return ;
    if(copyfunc(completename, linepose, charpose, cpsize, direction))
        if(removefunc(completename, linepose, charpose, cpsize, direction))
            printf("cut string from file successfuly!\n") ;
}

void pastestr() {
    char completename[100] = {0}, c ;
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
    undofunc(completename) ;
    myfile = fopen(completename, "w") ;
    fprintf(myfile, "%s", before) ;
    write_str(myfile, clipboard) ;
    fprintf(myfile, "%s", after) ;
    fclose(myfile) ;
    printf("file updated successfuly!\n") ;
}

void compare() {
    char name1[100] = {0}, name2[100] = {0}, line1[1000] = {0}, line2[1000] = {0} ;
    int line_counter = 0, firstline, lastline, i ;
    if(iswithspace()) 
        getname_withspace(name1) ;
    else{
        strcpy(name1, "root/") ;
        getstr(name1, 5) ;
    }
    if(iswithspace()) 
        getname_withspace(name2) ;
    else{
        strcpy(name2, "root/") ;
        getstr(name2, 5) ;
    }
    FILE *file1 ;
    FILE *file2 ;
    file1 = fopen(name1, "r") ;
    file2 = fopen(name2, "r") ;
    if(!file1) {
        printf("file1 doesn't exist\n") ;
        fclose(file1) ;
        fclose(file2) ;
        return ;
    }
    if(!file2) {
        printf("file2 doesn't exist\n") ;
        fclose(file1) ;
        fclose(file2) ;
        return ;
    }
    /*fgets(line1, 1000, file1) ;
    fgets(line2, 1000, file2) ;*/
    while(!feof(file1) && !feof(file2)) {
        fgets(line1, 1000, file1) ;
        fgets(line2, 1000, file2) ;
        line_counter++ ;
        if(strcmp(line1, line2)) {
            printf("============ #%d ============\n", line_counter) ;
            printf("%s", line1) ;
            printf("%s", line2) ;
        }
        memset(line1, 0, sizeof(line1)) ;
        memset(line2, 0, sizeof(line2)) ;
        /*fgets(line1, 1000, file1) ;
        fgets(line2, 1000, file2) ;*/
    }
    printf("\n") ;
    if(!feof(file1)) {
        fclose(file2) ;
        firstline = line_counter + 1 ;
        while(!feof(file1)) {
            line_counter++ ;
            fgets(line1,1000, file1) ;
        }
        lastline = line_counter ;
        fclose(file1) ;
        file1 = fopen(name1, "r") ;
        for(i = 1 ; i < firstline ; i++)
            fgets(line1, 1000, file1) ;
        printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n", firstline, lastline) ;
        memset(line1, 0, sizeof(line1)) ;
        //fgets(line1, 1000, file1) ;
        while(!feof(file1)) {
            fgets(line1, 1000, file1) ;
            printf("%s", line1) ;
            memset(line1, 0, sizeof(line1)) ;
            //fgets(line1, 1000, file1) ;
        }
        printf("\n") ;
        fclose(file1) ;
    }
    else if(!feof(file2)) {
        fclose(file1) ;
        firstline = line_counter + 1 ;
        while(!feof(file2)) {
            line_counter++ ;
            fgets(line2,1000, file2) ;
        }
        lastline = line_counter ;
        fclose(file2) ;
        file2 = fopen(name2, "r") ;
        for(i = 1 ; i < firstline ; i++)
            fgets(line2, 1000, file2) ;
        printf("<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<\n", firstline, lastline) ;
        memset(line2, 0, sizeof(line2)) ;
        //fgets(line2, 1000, file2) ;
        while(!feof(file2)) {
            fgets(line2, 1000, file2) ;
            printf("%s", line2) ;
            memset(line2, 0, sizeof(line2)) ;
            //fgets(line2, 1000, file2) ;
        }
        printf("\n") ;
        fclose(file2) ;
    }
}

void undo() {
    char completename[100] = {0}, undocompletename[100] = {0}, c ;
    int i ;
    if(invalid_command(1)) 
        return ;
    else {
        if(iswithspace()) 
            getname_withspace(completename) ;
        else{
            strcpy(completename, "root/") ;
            getstr(completename, 5) ;
        }
        strcpy(undocompletename, completename) ;
        memcpy(undocompletename, "undo/", 5) ;
    }
    //printf("%s\n", completename) ;
    //printf("%s\n", undocompletename) ;
    FILE *currentfile ;
    FILE *tempfile ;
    FILE *oldfile ;
    currentfile = fopen(completename, "r") ;
    if(!currentfile) {
        printf("file doesn't exist\n") ;
        fclose(currentfile) ;
        return ;
    }
    tempfile = fopen("temp.txt", "w") ;
    c = fgetc(currentfile) ;
    while(!feof(currentfile)) {
        fputc(c, tempfile) ;
        c = fgetc(currentfile) ;
    }
    fclose(currentfile) ;
    fclose(tempfile) ;
    currentfile = fopen(completename, "w") ;
    oldfile = fopen(undocompletename, "r") ;
    c = fgetc(oldfile) ;
    while(!feof(oldfile)) {
        fputc(c, currentfile) ;
        c = fgetc(oldfile) ;
    }
    fclose(currentfile) ;
    fclose(oldfile) ;
    oldfile = fopen(undocompletename, "w") ;
    tempfile = fopen("temp.txt", "r") ;
    c = fgetc(tempfile) ;
    while(!feof(tempfile)) {
        fputc(c, oldfile) ;
        c = fgetc(tempfile) ;
    }
    fclose(oldfile) ;
    fclose(tempfile) ;
    printf("undo successfuly\n") ;
}

void wildcard(char *completename, char *strin, char *before, int i) {
    char after[1000] = {0}, c, cprev = 1, option[100] = {0} ;
    int j = 0, charcounter, firstnum, flag ;
    int atop = 0, allop = 0, countop = 0, bywordop = 0, timesfound, atnum, wordfirstnum, wordcounter ;
    while(strin[i] != 0) {
        if(strin[i] == '\\') {
            i++ ;
            if(strin[i] == 'n')
                after[j] = '\n' ;
            else if(after[i] == '\"')
                after[j] = '\"' ;
            else if(after[i] == '*')
                after[j] = '*' ;
            else
                after[j] = '\\' ;
        }
        else
            after[j] = strin[i] ;
        i++ ;
        j++ ;
    }
    c = getchar() ;
    while(c != '\n') {
        memset(option, 0, 100) ;
        scanf("%s", option) ;
        if(!strcmp(option, "-count"))
            countop = 1 ;
        else if(!strcmp(option, "-at")) {
            atop = 1 ;
            scanf("%d", &atnum) ;
        }
        else if(!strcmp(option, "-all"))
            allop = 1 ;
        else if(!strcmp(option, "-byword"))
            bywordop = 1 ;
        else {
            printf("invalid command\n") ;
            return ;
        }
        c = getchar() ;
    }
    FILE *myfile ;
    myfile = fopen(completename, "r") ;
    if(!myfile) {
        printf("file doesn't exist\n") ;
        fclose(myfile) ;
        return ;
    }
    if(countop == 0 && atop == 0 && allop == 0 && bywordop == 0) {
    if(strlen(after) == 0) {
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == before[0]) {
                flag = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1 && c != ' ' && c != EOF && c != '\0') {
                    printf("string starts at character number %d\n", firstnum) ;
                    return ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        printf("couldn't find the string\n") ;
    }
    else if(strlen(before) == 0) {
        int wordfirstchar = 1 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ') {
                wordfirstchar = charcounter + 1 ;
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
            else if(c == after[0] && cprev != ' ' && cprev != EOF && cprev != '\0') {
                flag = 1 ;
                for(i = 0 ; i < strlen(after) ; i++) {
                    if(c != after[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    cprev = c ;
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    printf("string starts at character number %d\n", wordfirstchar) ;
                    return ;
                }
            }
            else {
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        printf("couldn't find the string\n") ;
    }
    else {
        int flag1 = 0, flag2 = 0 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            flag1 = 0 ;
            if(c == before[0]) {
                flag1 = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag1 == 1) {
                    while(!feof(myfile)) {
                        flag2 = 0 ;
                        if(c == ' ' || c == '\0') {
                        c = fgetc(myfile) ;
                        charcounter++ ;
                        break ;
                        }
                        else if(c == after[0]) {
                            flag2 = 1 ;
                            for(i = 0 ; i < strlen(after) ; i++) {
                            if(c != after[i] || feof(myfile)) {
                                flag2 = 0 ;
                                break ;
                            }
                            c = fgetc(myfile) ;
                            charcounter++ ;
                            }
                            if(flag2 == 1) {
                                break ;
                            }
                        }
                        else {
                            cprev = c ;
                            c = fgetc(myfile) ;
                            charcounter++ ;
                        }
                    } 
                    if (flag2 == 1) {
                        printf("string starts at character number %d\n", firstnum) ;
                        return ;
                    }       
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        printf("couldn't find the string\n") ;
    }
    }
    else if(countop == 1 && atop == 0 && allop == 0 && bywordop == 0) {
    timesfound = 0 ;
    if(strlen(after) == 0) {
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == before[0]) {
                flag = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1 && c != ' ' && c != EOF && c != '\0') {
                    timesfound++ ;
                    continue ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
    }
    else if(strlen(before) == 0) {
        int wordfirstchar = 1 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ') {
                wordfirstchar = charcounter + 1 ;
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
            else if(c == after[0] && cprev != ' ' && cprev != EOF && cprev != '\0') {
                flag = 1 ;
                for(i = 0 ; i < strlen(after) ; i++) {
                    if(c != after[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    cprev = c ;
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    timesfound++ ;
                    continue ;
                }
            }
            else {
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
    }
    else {
        int flag1 = 0, flag2 = 0 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            flag1 = 0 ;
            if(c == before[0]) {
                flag1 = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag1 == 1) {
                    while(!feof(myfile)) {
                        flag2 = 0 ;
                        if(c == ' ' || c == '\0') {
                        c = fgetc(myfile) ;
                        charcounter++ ;
                        break ;
                        }
                        else if(c == after[0]) {
                            flag2 = 1 ;
                            for(i = 0 ; i < strlen(after) ; i++) {
                            if(c != after[i] || feof(myfile)) {
                                flag2 = 0 ;
                                break ;
                            }
                            c = fgetc(myfile) ;
                            charcounter++ ;
                            }
                            if(flag2 == 1) {
                                break ;
                            }
                        }
                        else {
                            cprev = c ;
                            c = fgetc(myfile) ;
                            charcounter++ ;
                        }
                    } 
                    if (flag2 == 1) {
                        timesfound++ ;
                        continue ;
                    }       
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
    }
    printf("string appeared %d times\n", timesfound) ;
    }
    else if(countop == 0 && atop == 1 && allop == 0 && bywordop == 0) {
    timesfound = 0 ;
    if(strlen(after) == 0) {
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == before[0]) {
                flag = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1 && c != ' ' && c != EOF && c != '\0') {
                    timesfound++ ;
                    if(timesfound == atnum) {
                        printf("string starts at character number %d\n", firstnum) ;
                        return ;
                    }
                    continue ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        printf("-1\n") ;
    }
    else if(strlen(before) == 0) {
        int wordfirstchar = 1 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ') {
                wordfirstchar = charcounter + 1 ;
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
            else if(c == after[0] && cprev != ' ' && cprev != EOF && cprev != '\0') {
                flag = 1 ;
                for(i = 0 ; i < strlen(after) ; i++) {
                    if(c != after[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    cprev = c ;
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    timesfound++ ;
                    if(timesfound == atnum) {
                        printf("string starts at character number %d\n", wordfirstchar) ;
                        return ;
                    }
                    continue ;
                }
            }
            else {
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        printf("-1\n") ;
    }
    else {
        int flag1 = 0, flag2 = 0 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            flag1 = 0 ;
            if(c == before[0]) {
                flag1 = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag1 == 1) {
                    while(!feof(myfile)) {
                        flag2 = 0 ;
                        if(c == ' ' || c == '\0') {
                        c = fgetc(myfile) ;
                        charcounter++ ;
                        break ;
                        }
                        else if(c == after[0]) {
                            flag2 = 1 ;
                            for(i = 0 ; i < strlen(after) ; i++) {
                            if(c != after[i] || feof(myfile)) {
                                flag2 = 0 ;
                                break ;
                            }
                            c = fgetc(myfile) ;
                            charcounter++ ;
                            }
                            if(flag2 == 1) {
                                break ;
                            }
                        }
                        else {
                            cprev = c ;
                            c = fgetc(myfile) ;
                            charcounter++ ;
                        }
                    } 
                    if (flag2 == 1) {
                        timesfound++ ;
                        if(timesfound == atnum) {
                            printf("string starts at character number %d\n", firstnum) ;
                            return ;
                        }
                        continue ;
                    }       
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        printf("-1\n") ;
    }
    }
    else if(countop == 0 && atop == 0 && allop == 1 && bywordop == 0) {
    timesfound = 0 ;
    if(strlen(after) == 0) {
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == before[0]) {
                flag = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1 && c != ' ' && c != EOF && c != '\0') {
                    timesfound++ ;
                    if(timesfound == 1)
                        printf("%d", firstnum) ;
                    else
                        printf(", %d", firstnum) ;
                    continue ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound == 0)
            printf("couldn't find the string\n") ;        
        else
            printf("\n") ;
    }
    else if(strlen(before) == 0) {
        int wordfirstchar = 1 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ') {
                wordfirstchar = charcounter + 1 ;
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
            else if(c == after[0] && cprev != ' ' && cprev != EOF && cprev != '\0') {
                flag = 1 ;
                for(i = 0 ; i < strlen(after) ; i++) {
                    if(c != after[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    cprev = c ;
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    timesfound++ ;
                    if(timesfound == 1)
                        printf("%d", wordfirstchar) ;
                    else
                        printf(", %d", wordfirstchar) ;
                    continue ;
                }
            }
            else {
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound == 0)
            printf("couldn't find the string\n") ;        
        else
            printf("\n") ;
    }
    else {
        int flag1 = 0, flag2 = 0 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            flag1 = 0 ;
            if(c == before[0]) {
                flag1 = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag1 == 1) {
                    while(!feof(myfile)) {
                        flag2 = 0 ;
                        if(c == ' ' || c == '\0') {
                        c = fgetc(myfile) ;
                        charcounter++ ;
                        break ;
                        }
                        else if(c == after[0]) {
                            flag2 = 1 ;
                            for(i = 0 ; i < strlen(after) ; i++) {
                            if(c != after[i] || feof(myfile)) {
                                flag2 = 0 ;
                                break ;
                            }
                            c = fgetc(myfile) ;
                            charcounter++ ;
                            }
                            if(flag2 == 1) {
                                break ;
                            }
                        }
                        else {
                            cprev = c ;
                            c = fgetc(myfile) ;
                            charcounter++ ;
                        }
                    } 
                    if (flag2 == 1) {
                        timesfound++ ;
                        if(timesfound == 1)
                            printf("%d", firstnum) ;
                        else
                            printf(", %d", firstnum) ;
                        continue ;
                    }       
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound == 0)
            printf("couldn't find the string\n") ;        
        else
            printf("\n") ;
    }
    }
    else if(countop == 0 && atop == 0 && allop == 0 && bywordop == 1) {
    wordcounter = 1 ;
    if(strlen(after) == 0) {
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ')
                wordcounter++ ;
            if(c == before[0]) {
                flag = 1 ;
                wordfirstnum = wordcounter ;
                c = fgetc(myfile) ;
                charcounter++ ;
                for(i = 1 ; i < strlen(before) ; i++) {
                    if(c == ' ')
                        wordcounter++ ;
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1 && c != ' ' && c != EOF && c != '\0') {
                    printf("string starts at word number %d\n", wordfirstnum) ;
                    return ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        printf("couldn't find the string\n") ;
    }
    else if(strlen(before) == 0) {
        int wordfirstchar = 1 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ') {
                wordcounter++ ;
                wordfirstchar = charcounter + 1 ;
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
            else if(c == after[0] && cprev != ' ' && cprev != EOF && cprev != '\0') {
                flag = 1 ;
                wordfirstnum = wordcounter ;
                c = fgetc(myfile) ;
                charcounter++ ;
                for(i = 1 ; i < strlen(after) ; i++) {
                    if(c == ' ')
                        wordcounter++ ;
                    if(c != after[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    cprev = c ;
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    printf("string starts at word number %d\n", wordfirstnum) ;
                    return ;
                }
            }
            else {
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        printf("couldn't find the string\n") ;
    }
    else {
        int flag1 = 0, flag2 = 0 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            flag1 = 0 ;
            if(c == ' ')
                wordcounter++ ;
            if(c == before[0]) {
                flag1 = 1 ;
                wordfirstnum = wordcounter ;
                c = fgetc(myfile) ;
                charcounter++ ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c == ' ')
                        wordcounter++ ;
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag1 == 1) {
                    while(!feof(myfile)) {
                        flag2 = 0 ;
                        if(c == ' ' || c == '\0') {
                        c = fgetc(myfile) ;
                        charcounter++ ;
                        break ;
                        }
                        else if(c == after[0]) {
                            flag2 = 1 ;
                            for(i = 0 ; i < strlen(after) ; i++) {
                            if(c != after[i] || feof(myfile)) {
                                flag2 = 0 ;
                                break ;
                            }
                            c = fgetc(myfile) ;
                            charcounter++ ;
                            }
                            if(flag2 == 1) {
                                break ;
                            }
                        }
                        else {
                            cprev = c ;
                            c = fgetc(myfile) ;
                            charcounter++ ;
                        }
                    } 
                    if (flag2 == 1) {
                        printf("string starts at word number %d\n", wordfirstnum) ;
                        return ;
                    }       
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        printf("couldn't find the string\n") ;
    }
    }
    else if(countop == 0 && atop == 1 && allop == 0 && bywordop == 1) {
    timesfound = 0 ;
    wordcounter = 1 ;
    if(strlen(after) == 0) {
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ')
                wordcounter++ ;
            if(c == before[0]) {
                flag = 1 ;
                wordfirstnum = wordcounter ;
                c = fgetc(myfile) ;
                charcounter++ ;
                for(i = 1 ; i < strlen(before) ; i++) {
                    if(c == ' ')
                        wordcounter++ ;
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1 && c != ' ' && c != EOF && c != '\0') {
                    timesfound++ ;
                    if(timesfound == atnum) {
                        printf("string starts at word number %d\n", wordfirstnum) ;
                        return ;
                    }
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        printf("couldn't find the string\n") ;
    }
    else if(strlen(before) == 0) {
        int wordfirstchar = 1 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ') {
                wordcounter++ ;
                wordfirstchar = charcounter + 1 ;
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
            else if(c == after[0] && cprev != ' ' && cprev != EOF && cprev != '\0') {
                flag = 1 ;
                wordfirstnum = wordcounter ;
                c = fgetc(myfile) ;
                charcounter++ ;
                for(i = 1 ; i < strlen(after) ; i++) {
                    if(c == ' ')
                        wordcounter++ ;
                    if(c != after[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    cprev = c ;
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    timesfound++ ;
                    if(timesfound == atnum) {
                        printf("string starts at word number %d\n", wordfirstnum) ;
                        return ;
                    }
                }
            }
            else {
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        printf("couldn't find the string\n") ;
    }
    else {
        int flag1 = 0, flag2 = 0 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            flag1 = 0 ;
            if(c == ' ')
                wordcounter++ ;
            if(c == before[0]) {
                flag1 = 1 ;
                wordfirstnum = wordcounter ;
                c - fgetc(myfile) ;
                charcounter++ ;
                firstnum = charcounter ;
                for(i = 1 ; i < strlen(before) ; i++) {
                    if(c == ' ')
                        wordcounter++ ;
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag1 == 1) {
                    while(!feof(myfile)) {
                        flag2 = 0 ;
                        if(c == ' ' || c == '\0') {
                        if(c == ' ')
                            wordcounter++ ;
                        c = fgetc(myfile) ;
                        charcounter++ ;
                        break ;
                        }
                        else if(c == after[0]) {
                            flag2 = 1 ;
                            c = fgetc(myfile) ;
                            charcounter++ ;
                            for(i = 1 ; i < strlen(after) ; i++) {
                            if(c == ' ')
                                wordcounter++ ;
                            if(c != after[i] || feof(myfile)) {
                                flag2 = 0 ;
                                break ;
                            }
                            c = fgetc(myfile) ;
                            charcounter++ ;
                            }
                            if(flag2 == 1) {
                                break ;
                            }
                        }
                        else {
                            cprev = c ;
                            c = fgetc(myfile) ;
                            charcounter++ ;
                        }
                    } 
                    if (flag2 == 1) {
                        printf("string starts at word number %d\n", wordfirstnum) ;
                        return ;
                    }       
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        printf("couldn't find the string\n") ;
    }
    }
    else if(countop == 0 && atop == 0 && allop == 1 && bywordop == 1) {
    timesfound = 0 ;
    wordcounter = 1 ;
    if(strlen(after) == 0) {
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ')
                wordcounter++ ;
            if(c == before[0]) {
                flag = 1 ;
                wordfirstnum = wordcounter ;
                c = fgetc(myfile) ;
                charcounter++ ;
                for(i = 1 ; i < strlen(before) ; i++) {
                    if(c == ' ')
                        wordcounter++ ;
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1 && c != ' ' && c != EOF && c != '\0') {
                    timesfound++ ;
                    if(timesfound == 1)
                        printf("%d", wordfirstnum) ;
                    else
                        printf(", %d", wordfirstnum) ;
                    continue ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound == 0)
            printf("couldn't find the string\n") ;        
        else
            printf("\n") ;
    }
    else if(strlen(before) == 0) {
        int wordfirstchar = 1 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ') {
                wordcounter++ ;
                wordfirstchar = charcounter + 1 ;
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
            else if(c == after[0] && cprev != ' ' && cprev != EOF && cprev != '\0') {
                flag = 1 ;
                wordfirstnum = wordcounter ;
                c = fgetc(myfile) ;
                charcounter++ ;
                for(i = 1 ; i < strlen(after) ; i++) {
                    if(c == ' ')
                        wordcounter++ ;
                    if(c != after[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    cprev = c ;
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    timesfound++ ;
                    if(timesfound == 1)
                        printf("%d", wordfirstnum) ;
                    else
                        printf(", %d", wordfirstnum) ;
                    continue ;
                }
            }
            else {
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound == 0)
            printf("couldn't find the string\n") ;        
        else
            printf("\n") ;
    }
    else {
        int flag1 = 0, flag2 = 0 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            flag1 = 0 ;
            if(c == ' ')
                wordcounter++ ;
            if(c == before[0]) {
                flag1 = 1 ;
                wordfirstnum = wordcounter ;
                c = fgetc(myfile) ;
                charcounter++ ;
                for(i = 1 ; i < strlen(before) ; i++) {
                    if(c == ' ')
                        wordcounter++ ;
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag1 == 1) {
                    while(!feof(myfile)) {
                        flag2 = 0 ;
                        if(c == ' ' || c == '\0') {
                        if(c == ' ')
                            wordcounter++ ;
                        c = fgetc(myfile) ;
                        charcounter++ ;
                        break ;
                        }
                        else if(c == after[0]) {
                            flag2 = 1 ;
                            c = fgetc(myfile) ;
                            charcounter++ ;
                            for(i = 1 ; i < strlen(after) ; i++) {
                            if(c == ' ')
                                wordcounter++ ;
                            if(c != after[i] || feof(myfile)) {
                                flag2 = 0 ;
                                break ;
                            }
                            c = fgetc(myfile) ;
                            charcounter++ ;
                            }
                            if(flag2 == 1) {
                                break ;
                            }
                        }
                        else {
                            cprev = c ;
                            c = fgetc(myfile) ;
                            charcounter++ ;
                        }
                    } 
                    if (flag2 == 1) {
                        timesfound++ ;
                        if(timesfound == 1)
                            printf("%d", wordfirstnum) ;
                        else
                            printf(", %d", wordfirstnum) ;
                        continue ;
                    }       
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound == 0)
            printf("couldn't find the string\n") ;        
        else
            printf("\n") ;
    }
    }
}

void find() {
    char completename[100] = {0}, strin[1000] = {0}, before[1000] = {0}, after[1000] = {0}, c, option[100] = {0} ;
    int atop = 0, allop = 0, countop = 0, bywordop = 0, charcounter, firstnum, timesfound, atnum, wordfirstnum, wordcounter ;
    if(invalid_command(2))
        return ;
    else {
        if((c = str_space()) == '\"'){
            getstr_withspace(strin) ;
        }
        else {
            strin[0] = c ;
            getstring(strin, 1) ;
        }
    }
    //printf("%s\n", strin) ;
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
    int i = 0, j = 0 ;
    while(strin[i] != 0) {
        if(strin[i] == '\\') {
            i++ ;
            if(strin[i] == 'n')
                before[j] = '\n' ;
            else if(strin[i] == '\"')
                before[j] = '\"' ;
            else if(strin[i] == '*')
                before[j] = '*' ;
            else
                before[j] = '\\' ;
        }
        else if(strin[i] == '*') {
            wildcard(completename, strin, before, ++i) ;
            return ;
        }
        else
            before[j] = strin[i] ;
        i++ ;
        j++ ;
    }
    c = getchar() ;
    while(c != '\n') {
        memset(option, 0, 100) ;
        scanf("%s", option) ;
        if(!strcmp(option, "-count"))
            countop = 1 ;
        else if(!strcmp(option, "-at")) {
            atop = 1 ;
            scanf("%d", &atnum) ;
        }
        else if(!strcmp(option, "-all"))
            allop = 1 ;
        else if(!strcmp(option, "-byword"))
            bywordop = 1 ;
        else {
            printf("invalid command\n") ;
            return ;
        }
        c = getchar() ;
    }
    FILE *myfile ;
    myfile = fopen(completename, "r") ;
    if(!myfile) {
        printf("file doesn't exist\n") ;
        fclose(myfile) ;
        return ;
    }
    if(countop == 0 && atop == 0 && allop == 0 && bywordop == 0) {
    charcounter = 1 ;
    c = fgetc(myfile) ;
    int flag = 0 ;
    while(!feof(myfile)) {
        if(c == before[0]) {
            flag = 1 ;
            firstnum = charcounter ;
            for(i = 0 ; i < strlen(before) ; i++) {
                if(c != before[i] || feof(myfile)) {
                    flag = 0 ;
                    break ;
                }
                c = fgetc(myfile) ;
                charcounter++ ;
            }
            if(flag == 1) {
                printf("string starts at character number %d\n", firstnum) ;
                return ;
            }
        }
        else {
            c = fgetc(myfile) ;
            charcounter++ ;
        }
    }
    printf("couldn't find the string\n") ;
    }
    else if(countop == 1 && atop == 0 && allop == 0 && bywordop == 0) {
        timesfound = 0  ;
        c = fgetc(myfile) ;
        int flag = 0 ;
        while(!feof(myfile)) {
            if(c == before[0]) {
                flag = 1 ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        c = fgetc(myfile) ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                }
                if(flag == 1) {
                    timesfound++ ;
                    //c = fgetc(myfile) ;
                    continue ;
                }
            }
            else {
                c = fgetc(myfile) ;
            }
        }
        printf("string appeard in file %d times\n", timesfound) ;
    } 
    else if(countop == 0 && atop == 1 && allop == 0 && bywordop == 0) {
        charcounter = 1 ;
        timesfound = 0 ;
        c = fgetc(myfile) ;
        int flag = 0 ;
        while(!feof(myfile)) {
            if(c == before[0]) {
                flag = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    timesfound++ ;
                    if(timesfound == atnum) {
                        printf("string starts at character number %d\n", firstnum) ;
                        return ;
                    }
                    else
                        continue ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        printf("-1\n") ;
    }
    else if(countop == 0 && atop == 0 && allop == 1 && bywordop == 0) {
        charcounter = 1 ;
        timesfound = 0 ;
        c = fgetc(myfile) ;
        int flag = 0 ;
        while(!feof(myfile)) {
            if(c == before[0]) {
                flag = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    timesfound++ ;
                    if(timesfound == 1)
                        printf("%d", firstnum) ;
                    else    
                        printf(", %d", firstnum) ;
                    continue ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound == 0)
            printf("couldn't find the string\n") ;
        else 
            printf("\n") ;
    }
    else if(countop == 0 && atop == 0 && allop == 0 && bywordop == 1) {
        charcounter = 1 ;
        wordcounter = 1 ;
        c = fgetc(myfile) ;
        int flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ')
                wordcounter++ ;
            if(c == before[0]) {
                flag = 1 ;
                wordfirstnum = wordcounter ;
                c = fgetc(myfile) ;
                charcounter++ ;
                for(i = 1 ; i < strlen(before) ; i++) {
                    if(c == ' ')
                        wordcounter++ ;
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    printf("string starts at word number %d\n", wordfirstnum) ;
                    return ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        printf("couldn't find the string\n") ;
    }
    else if(countop == 0 && atop == 1 && allop == 0 && bywordop == 1) {
        charcounter = 1 ;
        wordcounter = 1 ;
        timesfound = 0 ;
        c = fgetc(myfile) ;
        int flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ')
                wordcounter++ ;
            if(c == before[0]) {
                flag = 1 ;
                wordfirstnum = wordcounter ;
                c = fgetc(myfile) ;
                charcounter++ ;
                for(i = 1 ; i < strlen(before) ; i++) {
                    if(c == ' ')
                        wordcounter++ ;
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    timesfound++ ;
                    if(timesfound == atnum) {
                        printf("string starts at word number %d\n", wordfirstnum) ;
                        return ;
                    }
                    else
                        continue ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        printf("-1\n") ;
    }
    else if(countop == 0 && atop == 0 && allop == 1 && bywordop == 1) {
        charcounter = 1 ;
        wordcounter = 1 ;
        timesfound = 0 ;
        c = fgetc(myfile) ;
        int flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ')
                wordcounter++ ;
            if(c == before[0]) {
                flag = 1 ;
                wordfirstnum = wordcounter ;
                c = fgetc(myfile) ;
                charcounter++ ;
                for(i = 1 ; i < strlen(before) ; i++) {
                    if(c == ' ')
                        wordcounter++ ;
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    timesfound++ ;
                    if(timesfound == 1)
                        printf("%d", wordfirstnum) ;
                    else    
                        printf(", %d", wordfirstnum) ;
                    continue ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound == 0)
            printf("couldn't find the string\n") ;
        else 
            printf("\n") ;
    }
    else
        printf("wrong combination of attributes\n") ;
}

void replacewildcard(char *completename, char *strin, char *before, int i, char *str2) {
    char after[1000] = {0}, c, cprev = 1, option[100] = {0} ;
    char *filebefore = (char*)calloc(1000000, sizeof(char)) ;
    char *fileafter = (char*)calloc(1000000, sizeof(char)) ;
    int j = 0, charcounter, firstnum, flag ;
    int atop = 0, allop = 0, timesfound, atnum, wordfirstnum, wordcounter ;
    while(strin[i] != 0) {
        if(strin[i] == '\\') {
            i++ ;
            if(strin[i] == 'n')
                after[j] = '\n' ;
            else if(after[i] == '\"')
                after[j] = '\"' ;
            else if(after[i] == '*')
                after[j] = '*' ;
            else
                after[j] = '\\' ;
        }
        else
            after[j] = strin[i] ;
        i++ ;
        j++ ;
    }
    c = getchar() ;
    while(c != '\n') {
        memset(option, 0, 100) ;
        scanf("%s", option) ;
        if(!strcmp(option, "-at")) {
            atop = 1 ;
            scanf("%d", &atnum) ;
        }
        else if(!strcmp(option, "-all"))
            allop = 1 ;
        else {
            printf("invalid command\n") ;
            return ;
        }
        c = getchar() ;
    }
    FILE *myfile ;
    myfile = fopen(completename, "r") ;
    if(!myfile) {
        printf("file doesn't exist\n") ;
        fclose(myfile) ;
        return ;
    }
    if(atop == 1 && allop == 1) {
        printf("wrong combination of attributes\n") ;
        return ;
    }
    else if(allop == 1) {
    undofunc(completename) ;
    timesfound = 0 ;
    if(strlen(after) == 0) {
        while(1) {
        timesfound = 0 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == before[0]) {
                flag = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1 && c != ' ' && c != EOF && c != '\0') {
                    timesfound++ ;
                    break ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound != 1) {
            break ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "r") ;
        for(i = 0 ; i < firstnum - 1 ; i++) {
            filebefore[i] = fgetc(myfile) ;
        }
        c = fgetc(myfile) ;
        while(c != ' ' && !feof(myfile)) {
            c = fgetc(myfile) ;
        }
        i = 0 ;
        while(!feof(myfile)) {
            fileafter[i] = c ;
            //printf("%c", fileafter[i]) ;
            i++ ;
            c = fgetc(myfile) ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "w") ;
        fprintf(myfile, "%s", filebefore) ;
        write_str(myfile, str2) ;
        fprintf(myfile, "%s", fileafter) ;
        fclose(myfile) ;
        myfile = fopen(completename, "r") ;
        memset(filebefore, 0, 1000000) ;
        memset(fileafter, 0, 1000000) ;
        }
        printf("file updated successfuly\n") ;
    }
    else if(strlen(before) == 0) {
        int wordfirstchar ;
        while(1) {
        timesfound = 0 ;
        wordfirstchar = 1 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ') {
                wordfirstchar = charcounter + 1 ;
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
            else if(c == after[0] && cprev != ' ' && cprev != EOF && cprev != '\0') {
                flag = 1 ;
                for(i = 0 ; i < strlen(after) ; i++) {
                    if(c != after[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    cprev = c ;
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    timesfound++ ;
                    break ;
                }
            }
            else {
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound != 1) {
            break ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "r") ;
        for(i = 0 ; i < wordfirstchar - 1 ; i++) {
            filebefore[i] = fgetc(myfile) ;
        }
        for(i = wordfirstchar ; i < charcounter ; i++)
            c = fgetc(myfile) ;
        i = 0 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            fileafter[i] = c ;
            i++ ;
            c = fgetc(myfile) ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "w") ;
        fprintf(myfile, "%s", filebefore) ;
        write_str(myfile, str2) ;
        fprintf(myfile, "%s", fileafter) ;
        fclose(myfile) ;
        myfile = fopen(completename, "r") ;
        memset(filebefore, 0, 1000000) ;
        memset(fileafter, 0, 1000000) ;
        }
        printf("file updated successfuly\n") ;
    }
    else {
        int flag1, flag2 ;
        while(1) {
        flag1 = 0 ;
        flag2 = 0 ;
        timesfound = 0 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            flag1 = 0 ;
            if(c == before[0]) {
                flag1 = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag1 == 1) {
                    while(!feof(myfile)) {
                        flag2 = 0 ;
                        if(c == ' ' || c == '\0') {
                        c = fgetc(myfile) ;
                        charcounter++ ;
                        break ;
                        }
                        else if(c == after[0]) {
                            flag2 = 1 ;
                            for(i = 0 ; i < strlen(after) ; i++) {
                            if(c != after[i] || feof(myfile)) {
                                flag2 = 0 ;
                                break ;
                            }
                            c = fgetc(myfile) ;
                            charcounter++ ;
                            }
                            if(flag2 == 1) {
                                break ;
                            }
                        }
                        else {
                            cprev = c ;
                            c = fgetc(myfile) ;
                            charcounter++ ;
                        }
                    } 
                    if (flag2 == 1) {
                        timesfound++ ;
                        break ;
                    }       
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound != 1) {
            break ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "r") ;
        for(i = 0 ; i < firstnum - 1 ; i++) {
            filebefore[i] = fgetc(myfile) ;
        }
        for(i = firstnum ; i < charcounter ; i++) {
            c = fgetc(myfile) ;
        }
        i = 0 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            fileafter[i] = c ;
            i++ ;
            c = fgetc(myfile) ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "w") ;
        fprintf(myfile, "%s", filebefore) ;
        write_str(myfile, str2) ;
        fprintf(myfile, "%s", fileafter) ;
        fclose(myfile) ;
        myfile = fopen(completename, "r") ;
        memset(filebefore, 0, 1000000) ;
        memset(fileafter, 0, 1000000) ;
        }
        printf("file updated successfuly\n") ;
    }
    }
    else if(atop == 1) {
    undofunc(completename) ;
    timesfound = 0 ;
    if(strlen(after) == 0) {
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == before[0]) {
                flag = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1 && c != ' ' && c != EOF && c != '\0') {
                    timesfound++ ;
                    if(timesfound == atnum) {
                        break ;
                    }
                    continue ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound != atnum) {
            printf("coundn't find the string\n") ;
            return ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "r") ;
        for(i = 0 ; i < firstnum - 1 ; i++) {
            filebefore[i] = fgetc(myfile) ;
        }
        c = fgetc(myfile) ;
        while(c != ' ' && !feof(myfile)) {
            c = fgetc(myfile) ;
        }
        i = 0 ;
        while(!feof(myfile)) {
            fileafter[i] = c ;
            //printf("%c", fileafter[i]) ;
            i++ ;
            c = fgetc(myfile) ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "w") ;
        fprintf(myfile, "%s", filebefore) ;
        write_str(myfile, str2) ;
        fprintf(myfile, "%s", fileafter) ;
        fclose(myfile) ;
        printf("file updated successfuly\n") ;
    }
    else if(strlen(before) == 0) {
        int wordfirstchar = 1 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ') {
                wordfirstchar = charcounter + 1 ;
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
            else if(c == after[0] && cprev != ' ' && cprev != EOF && cprev != '\0') {
                flag = 1 ;
                for(i = 0 ; i < strlen(after) ; i++) {
                    if(c != after[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    cprev = c ;
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    timesfound++ ;
                    if(timesfound == atnum) {
                        break ;
                    }
                    continue ;
                }
            }
            else {
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound != atnum) {
            printf("couldn't find the string\n") ;
            return ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "r") ;
        for(i = 0 ; i < wordfirstchar - 1 ; i++) {
            filebefore[i] = fgetc(myfile) ;
        }
        for(i = wordfirstchar ; i < charcounter ; i++)
            c = fgetc(myfile) ;
        i = 0 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            fileafter[i] = c ;
            i++ ;
            c = fgetc(myfile) ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "w") ;
        fprintf(myfile, "%s", filebefore) ;
        write_str(myfile, str2) ;
        fprintf(myfile, "%s", fileafter) ;
        fclose(myfile) ;
        printf("file updated successfuly\n") ;
    }
    else {
        int flag1 = 0, flag2 = 0 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            flag1 = 0 ;
            if(c == before[0]) {
                flag1 = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag1 == 1) {
                    while(!feof(myfile)) {
                        flag2 = 0 ;
                        if(c == ' ' || c == '\0') {
                        c = fgetc(myfile) ;
                        charcounter++ ;
                        break ;
                        }
                        else if(c == after[0]) {
                            flag2 = 1 ;
                            for(i = 0 ; i < strlen(after) ; i++) {
                            if(c != after[i] || feof(myfile)) {
                                flag2 = 0 ;
                                break ;
                            }
                            c = fgetc(myfile) ;
                            charcounter++ ;
                            }
                            if(flag2 == 1) {
                                break ;
                            }
                        }
                        else {
                            cprev = c ;
                            c = fgetc(myfile) ;
                            charcounter++ ;
                        }
                    } 
                    if (flag2 == 1) {
                        timesfound++ ;
                        if(timesfound == atnum) {
                            break ;
                        }
                        continue ;
                    }       
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound != atnum) {
            printf("couldn't find the string\n") ;
            return ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "r") ;
        for(i = 0 ; i < firstnum - 1 ; i++) {
            filebefore[i] = fgetc(myfile) ;
        }
        for(i = firstnum ; i < charcounter ; i++) {
            c = fgetc(myfile) ;
        }
        i = 0 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            fileafter[i] = c ;
            i++ ;
            c = fgetc(myfile) ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "w") ;
        fprintf(myfile, "%s", filebefore) ;
        write_str(myfile, str2) ;
        fprintf(myfile, "%s", fileafter) ;
        fclose(myfile) ;
        printf("file updated successfuly\n") ;
    }
    }
    else {
    undofunc(completename) ;
    timesfound = 0 ;
    if(strlen(after) == 0) {
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == before[0]) {
                flag = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1 && c != ' ' && c != EOF && c != '\0') {
                    timesfound++ ;
                    break ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound != 1) {
            printf("coundn't find the string\n") ;
            return ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "r") ;
        for(i = 0 ; i < firstnum - 1 ; i++) {
            filebefore[i] = fgetc(myfile) ;
        }
        c = fgetc(myfile) ;
        while(c != ' ' && !feof(myfile)) {
            c = fgetc(myfile) ;
        }
        i = 0 ;
        while(!feof(myfile)) {
            fileafter[i] = c ;
            //printf("%c", fileafter[i]) ;
            i++ ;
            c = fgetc(myfile) ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "w") ;
        fprintf(myfile, "%s", filebefore) ;
        write_str(myfile, str2) ;
        fprintf(myfile, "%s", fileafter) ;
        fclose(myfile) ;
        printf("file updated successfuly\n") ;
    }
    else if(strlen(before) == 0) {
        int wordfirstchar = 1 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        flag = 0 ;
        while(!feof(myfile)) {
            if(c == ' ') {
                wordfirstchar = charcounter + 1 ;
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
            else if(c == after[0] && cprev != ' ' && cprev != EOF && cprev != '\0') {
                flag = 1 ;
                for(i = 0 ; i < strlen(after) ; i++) {
                    if(c != after[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    cprev = c ;
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    timesfound++ ;
                    break ;
                }
            }
            else {
                cprev = c ;
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound != 1) {
            printf("couldn't find the string\n") ;
            return ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "r") ;
        for(i = 0 ; i < wordfirstchar - 1 ; i++) {
            filebefore[i] = fgetc(myfile) ;
        }
        for(i = wordfirstchar ; i < charcounter ; i++)
            c = fgetc(myfile) ;
        i = 0 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            fileafter[i] = c ;
            i++ ;
            c = fgetc(myfile) ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "w") ;
        fprintf(myfile, "%s", filebefore) ;
        write_str(myfile, str2) ;
        fprintf(myfile, "%s", fileafter) ;
        fclose(myfile) ;
        printf("file updated successfuly\n") ;
    }
    else {
        int flag1 = 0, flag2 = 0 ;
        charcounter = 1 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            flag1 = 0 ;
            if(c == before[0]) {
                flag1 = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(before) ; i++) {
                    if(c != before[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag1 == 1) {
                    while(!feof(myfile)) {
                        flag2 = 0 ;
                        if(c == ' ' || c == '\0') {
                        c = fgetc(myfile) ;
                        charcounter++ ;
                        break ;
                        }
                        else if(c == after[0]) {
                            flag2 = 1 ;
                            for(i = 0 ; i < strlen(after) ; i++) {
                            if(c != after[i] || feof(myfile)) {
                                flag2 = 0 ;
                                break ;
                            }
                            c = fgetc(myfile) ;
                            charcounter++ ;
                            }
                            if(flag2 == 1) {
                                break ;
                            }
                        }
                        else {
                            cprev = c ;
                            c = fgetc(myfile) ;
                            charcounter++ ;
                        }
                    } 
                    if (flag2 == 1) {
                        timesfound++ ;
                        break ;
                    }       
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        if(timesfound != 1) {
            printf("couldn't find the string\n") ;
            return ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "r") ;
        for(i = 0 ; i < firstnum - 1 ; i++) {
            filebefore[i] = fgetc(myfile) ;
        }
        for(i = firstnum ; i < charcounter ; i++) {
            c = fgetc(myfile) ;
        }
        i = 0 ;
        c = fgetc(myfile) ;
        while(!feof(myfile)) {
            fileafter[i] = c ;
            i++ ;
            c = fgetc(myfile) ;
        }
        fclose(myfile) ;
        myfile = fopen(completename, "w") ;
        fprintf(myfile, "%s", filebefore) ;
        write_str(myfile, str2) ;
        fprintf(myfile, "%s", fileafter) ;
        fclose(myfile) ;
        printf("file updated successfuly\n") ;
    }
    }
}

void replace() {
    char completename[100] = {0}, str1[1000] = {0}, str1out[1000] = {0}, str2[1000] = {0}, c, option[100] = {0} ;
    char *before = (char*)calloc(1000000, sizeof(char)) ;
    char *after = (char*)calloc(1000000, sizeof(char)) ;
    int atop = 0, allop = 0, charcounter, firstnum, timesfound, atnum, wordfirstnum, wordcounter ;
    if(invalid_command(4))
        return ;
    else {
        if((c = str_space()) == '\"'){
            getstr_withspace(str1) ;
        }
        else {
            str1[0] = c ;
            getstring(str1, 1) ;
        }
    }
    if(invalid_command(5))
        return ;
    else {
        if((c = str_space()) == '\"'){
            getstr_withspace(str2) ;
        }
        else {
            str2[0] = c ;
            getstring(str2, 1) ;
        }
    }
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
    int i = 0, j = 0 ;
    while(str1[i] != 0) {
        if(str1[i] == '\\') {
            i++ ;
            if(str1[i] == 'n')
                str1out[j] = '\n' ;
            else if(str1[i] == '\"')
                str1out[j] = '\"' ;
            else if(str1[i] == '*')
                str1out[j] = '*' ;
            else
                str1out[j] = '\\' ;
        }
        else if(str1[i] == '*') {
            replacewildcard(completename, str1, str1out, ++i, str2) ;
            return ;
        }
        else
            str1out[j] = str1[i] ;
        i++ ;
        j++ ;
    }
    c = getchar() ;
    while(c != '\n') {
        memset(option, 0, 100) ;
        scanf("%s", option) ;
        if(!strcmp(option, "-at")) {
            atop = 1 ;
            scanf("%d", &atnum) ;
        }
        else if(!strcmp(option, "-all"))
            allop = 1 ;
        else {
            printf("invalid command\n") ;
            return ;
        }
        c = getchar() ;
    }
    FILE *myfile ;
    myfile = fopen(completename, "r") ;
    if(!myfile) {
        printf("file doesn't exist\n") ;
        fclose(myfile) ;
        return ;
    }
    if(atop == 1 && allop == 1) {
        printf("wrong combination of attributes\n") ;
        return ;
    }
    else if(allop == 1) {
        undofunc(completename) ;
        int flag ;
        while(1) {
            charcounter = 1 ;
            timesfound = 0 ;
            c = fgetc(myfile) ;
            flag = 0 ;
            while(!feof(myfile)) {
                if(c == str1out[0]) {
                    flag = 1 ;
                    firstnum = charcounter ;
                    for(i = 0 ; i < strlen(str1out) ; i++) {
                        if(c != str1out[i] || feof(myfile)) {
                            flag = 0 ;
                            break ;
                        }
                        c = fgetc(myfile) ;
                        charcounter++ ;
                    }
                    if(flag == 1) {
                        timesfound++ ;
                        break ;
                    }
                }
                else {
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
            }
            fclose(myfile) ;
            if(timesfound == 0) {
                printf("file updated successfuly\n") ;
                return ;
            }
            myfile = fopen(completename, "r") ;
            for(i = 0 ; i < firstnum - 1 ; i++) {
                before[i] = fgetc(myfile) ;
            }
            for(i = 0 ; i < strlen(str1out) ; i++)
                c = fgetc(myfile) ;
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
            write_str(myfile, str2) ;
            fprintf(myfile, "%s", after) ;
            fclose(myfile) ;
            myfile = fopen(completename, "r") ;
            memset(before, 0, 1000000) ;
            memset(after, 0, 1000000) ;
        }
    }
    else if(atop == 1) {
        charcounter = 1 ;
        timesfound = 0 ;
        c = fgetc(myfile) ;
        int flag = 0 ;
        while(!feof(myfile)) {
            if(c == str1out[0]) {
                flag = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(str1out) ; i++) {
                    if(c != str1out[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    timesfound++ ;
                    if(timesfound == atnum) {
                        //printf("string starts at character number %d\n", firstnum) ;
                        break ;
                    }
                    else
                        continue ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        fclose(myfile) ;
        if(timesfound != atnum) {
            printf("couldn't find the string\n") ;
            return ;
        }
        undofunc(completename) ;
        myfile = fopen(completename, "r") ;
        for(i = 0 ; i < firstnum - 1 ; i++) {
            before[i] = fgetc(myfile) ;
        }
        for(i = 0 ; i < strlen(str1out) ; i++)
            c = fgetc(myfile) ;
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
        write_str(myfile, str2) ;
        fprintf(myfile, "%s", after) ;
        fclose(myfile) ;
        printf("file updated successfuly\n") ;
    }
    else {
        charcounter = 1 ;
        timesfound = 0 ;
        c = fgetc(myfile) ;
        int flag = 0 ;
        while(!feof(myfile)) {
            if(c == str1out[0]) {
                flag = 1 ;
                firstnum = charcounter ;
                for(i = 0 ; i < strlen(str1out) ; i++) {
                    if(c != str1out[i] || feof(myfile)) {
                        flag = 0 ;
                        break ;
                    }
                    c = fgetc(myfile) ;
                    charcounter++ ;
                }
                if(flag == 1) {
                    timesfound++ ;
                    break ;
                }
            }
            else {
                c = fgetc(myfile) ;
                charcounter++ ;
            }
        }
        fclose(myfile) ;
        if(timesfound == 0) {
            printf("couldn't find the string\n") ;
            return ;
        }
        undofunc(completename) ;
        myfile = fopen(completename, "r") ;
        for(i = 0 ; i < firstnum - 1 ; i++) {
            before[i] = fgetc(myfile) ;
        }
        for(i = 0 ; i < strlen(str1out) ; i++)
            c = fgetc(myfile) ;
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
        write_str(myfile, str2) ;
        fprintf(myfile, "%s", after) ;
        fclose(myfile) ;
        printf("file updated successfuly\n") ;
    }
}

int main () {
    char command[100] ;
    clipboard = (char*)calloc(1000000, sizeof(char)) ;
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
        else if(!strcmp(command, "copystr")) 
            copystr() ;
        else if(!strcmp(command, "cutstr"))
            cutstr() ;
        else if(!strcmp(command, "pastestr"))
            pastestr() ;
        else if(!strcmp(command, "compare"))
            compare() ;
        else if(!strcmp(command, "find"))
            find() ;
        else if(!strcmp(command, "replace"))
            replace() ;
        else if(!strcmp(command, "undo"))
            undo() ;
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