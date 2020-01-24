#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 5

//char message[BUFSIZE+1];

void readKeyboard(char c[BUFSIZE+1])
{
   printf("--- Enter command with length 5: ---\n12345\n");
   int run = 1;
   //char c[BUFSIZE+1];
   size_t pos = 0;
   while(run && pos<BUFSIZE+1){
      ssize_t res = read(STDIN_FILENO, c+pos, BUFSIZE+1-pos);
      if (res>0){
         pos += res;
      } else {
         run = 0;
      }
   }

   c[pos] = '\0'; //terminating null
}



//void sendMessage(char* message){
   
//}

int main()
{
   char message[BUFSIZE+1];
   while(1){
      
      readKeyboard(message);
      printf("Message: %s", message);
      //char message = readKeyboard(BUFSIZE);
      //sendMessage(message);
   }
}
