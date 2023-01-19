#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <semaphore.h>


pthread_t r[10],w[10];
int readercount = 0, writercount = 0;
int rc = 0;
int argi;
char **args;
int i;


void *reader(void *);
void *writer(void *);
void  startRead();
void  startWrite();
void  endRead();
void  endWrite();

void *writer(void *i)
{
     int t = (intptr_t) i;
     startRead();
     printf("Writer %d starts writting\n", t);
     sleep(1);
     endRead();
     printf("Writer %d ends writting\n", t);
     
}

void *reader(void *i)
{
 
     int t = (intptr_t) i;
     startWrite(i);
     printf("Reader %d starts writting\n", t);
     sleep(1);
     endWrite(i);
     printf("Reader %d ends writting\n", t);
     
  
}

struct monitor_rw{
    pthread_cond_t canRead, canWrite;
    int signalReadCount, waitReadCount;
    int isBusy;
};
struct monitor_rw monitor;



void startRead(){
    if(monitor.isBusy==1){
        monitor.waitReadCount++;
        //monitor.canRead.wait();
        pthread_cond_wait(&monitor.canRead, NULL);
        monitor.waitReadCount--;
    }
}
void endRead(){
    monitor.signalReadCount--;
    if(monitor.signalReadCount == 0){
        //monitor.canRead.signal();
        pthread_cond_signal(&monitor.canRead);
    }
}
// Writer
void startWrite(){
    if(monitor.isBusy || monitor.signalReadCount > 0){
        //monitor.canWrite.wait();
        pthread_cond_wait(&monitor.canWrite, NULL);
    }
    monitor.isBusy = 1;
}
void endWrite(){
    monitor.isBusy = 0;
    if(monitor.waitReadCount > 0){
        //monitor.canRead.signal();
        pthread_cond_signal(&monitor.canRead);
    } else {
        //monitor.canWrite.signal();
        pthread_cond_signal(&monitor.canWrite);
    }
}

// Initialization Code
int initialization(){
    monitor.signalReadCount = 0;
    monitor.waitReadCount = 0;
    monitor.isBusy = 0;
    return 0;
}




int main( int argc, char  *argv[] )  {


  argi = argc;
  args = argv;

  if(argc == 11) {
       
       
       for (i=1;i<11;i++)
       {
           char *a = args[i];
           int num = atoi(a);
           if(num==0)
           {
              
               readercount++;
               pthread_create(&r[i],NULL,(void *)reader,(void *)(intptr_t) readercount);
               pthread_join(r[i],NULL);
              
            
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
    
   }
   else if( argc > 11 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("Ten argument expected.\n");
   }    
   
  
return 0;
}
