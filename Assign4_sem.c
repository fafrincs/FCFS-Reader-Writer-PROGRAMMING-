#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <semaphore.h>

sem_t x,y;
pthread_t r[10],w[10];
int readercount = 0, writercount = 0;
int rc = 0;
int argi;
char **args;
int i;


void *reader(void *);
void *writer(void *);


void *writer(void *i)
{
     int t = (intptr_t) i;
     
     sem_wait(&y);
     
     printf("Writer %d starts writting\n", t);
     sleep(1);
     printf("Writer %d ends writting\n", t);
     sleep(1);
     sem_post(&y);
}

void *reader(void *i)
{
  int t = (intptr_t) i;
  sem_wait(&x);
  rc++;
  if (rc == 1)
  { 
    sem_wait(&y);
  }
  sem_post(&x);
  
  printf("Reader %d starts reading\n", t);
  sleep(1);
  printf("Reader %d ends reading\n", t);
  sleep(1);
  sem_wait(&x);
  rc--;
  if (rc == 0)
  {
    sem_post(&y);
  }
    sem_post(&x);
}

int main( int argc, char  *argv[] )  {

  sem_init(&x,0,1);
  sem_init(&y,0,1); 

  argi = argc;
  args = argv;
  int read[10], write[10];

  if(argc == 11) {
    
       for (i=1;i<argc;i++)
       {
         char *a = args[i];
         int num = atoi(a);
           
           if(num==0)
           {
               readercount++;
               pthread_create(&r[i],NULL,(void *)reader,(void *)(intptr_t) readercount);
               
           }
        
           else if (num==1)
  
           {
             writercount++;
             pthread_create(&w[i],NULL,(void *)writer,(void *)(intptr_t) writercount);
             pthread_join(w[i],NULL);
             
           }

           else
           {
               printf("pass arguments in 0 or 1 format.\n");
           }    

        
       }
       for (i=1;i<11;i++)
       {
           char *a = args[i];
         int num = atoi(a);
         if (num==0)
          {
             pthread_join(r[i],NULL);
             
          }
       }
    
   }
    
   else if( argc > 11 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("Ten argument expected.\n");
   }    
   
  
return 0;
}
