#include <stdio.h>
#include <unistd.h>
#include <ctype.h>      // for method int tolower(int c)

#define SIZE 5

int isVowel(char c) {
    c = tolower(c);
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
        return 1;
    } else {
        return 0;
    }
}

// Does't really work, but whatevs
int rovarspraket(char str[]) {
    for (size_t i = 0; i<SIZE; i++) {
        if (isVowel(str[i])) {
            str[i+1] = 'o';            
        }
    }
    return 0;
}

int readInput() {
    int run = 1;
    char c[SIZE+1];     // space for terminating null
    size_t pos = 0;
    while (run && pos < SIZE)
    {
        ssize_t res = read(STDIN_FILENO, c+pos, SIZE-pos);
        if(res>0){      // if more chars to read
            pos+=res;   // inc pos
        } else {
            run = 0;
        }
    }
    c[pos] = '\0';      // add terminating null
    rovarspraket(c);
    printf("Buffer after read: %s\n", c);
    return 0;
}

int main(){
    while (1)
    {
        readInput();
    }
    
}

