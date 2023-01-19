
**************** FCFS Reader/Writer PROGRAMMING  *********************
                                 === Authors ===

                                  Fahmida Afrin (05961917)
Pair work with Kang-il Park (71778186)
                               === Introduction ===

This folder contains the following files:
1. Assign4_sem.c : FCFS Reader/Writer program using semaphore 
and write those numbers to the shared memory.
2. Assign4_mon.c : FCFS Reader/Writer program using monitor 
3. assign4sem_exe : the compiled executable files of Assign4_sem.c
4. assign4mon_exe: the compiled executable files of Assign4_mon.c
5. Makefile: This is a makefile to compile the three programs.

                            === How to run the program?===

There are two way:
1. Run the Makefile using the following command:	
$ make all

or,

2. Run the following command in command prompt:

$ gcc -o assign4sem_exe Assign4_sem.c -lpthread
./assign4sem_exe 0 1 0 1 0 0 0 0 1 0
$ gcc -o assign4mon_exe Assign4_mon.cpp -lpthread
./assign4sem_exe 0 1 0 1 0 0 0 0 1 0


                         === pseudocode for semaphores solutions ===
void *writer(void *i)
{
     
     
     sem_wait(&y);
     
    //write
  
     sem_post(&y);
}

void *reader(void *i)
{
 
  sem_wait(&x);
  rc++;
  if (rc == 1)
  { 
    sem_wait(&y);
  }
  sem_post(&x);
  
  // read
  sem_wait(&x);
  rc--;
  if (rc == 0)
  {
    sem_post(&y);
  }
    sem_post(&x);
}
begin main:

      
       FOR iteration Arguments
           
           if(Reader)
           {
              
               readercount++;
               pthread_create function for Reader
               
              
            
           }
        
           else 
  
           {
             writercount++;
             pthread_create function for Writer
             pthread_join function for Writer
           }
    end FOR
    FOR iteration Reader
    
        pthread_join function for Reader            
    end FOR
  
   
end main


                          === pseudocode for monitor solutions ===

 

void *writer(void *i)
{
     int t = (intptr_t) i;
     startRead();
     
     endRead();
     
     
}

void *reader(void *i)
{
 
     int t = (intptr_t) i;
     startWrite(i);
     
     endWrite(i);
     
     
  
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
       
        pthread_cond_wait(&monitor.canRead, NULL);
        monitor.waitReadCount--;
    }
}
void endRead(){
    monitor.signalReadCount--;
    if(monitor.signalReadCount == 0){
      
        pthread_cond_signal(&monitor.canRead);
    }
}

void startWrite(){
    if(monitor.isBusy || monitor.signalReadCount > 0){
       
        pthread_cond_wait(&monitor.canWrite, NULL);
    }
    monitor.isBusy = 1;
}
void endWrite(){
    monitor.isBusy = 0;
    if(monitor.waitReadCount > 0){
      
        pthread_cond_signal(&monitor.canRead);
    } else {
        
        pthread_cond_signal(&monitor.canWrite);
    }
}

int initialization(){
    monitor.signalReadCount = 0;
    monitor.waitReadCount = 0;
    monitor.isBusy = 0;
    return 0;
}




begin main:

      
       FOR iteration Arguments
           
           if(Reader)
           {
              
               readercount++;
               pthread_create function for Reader
               
              
            
           }
        
           else 
  
           {
             writercount++;
             pthread_create function for Writer
             pthread_join function for Writer
           }
    end FOR
    FOR iteration Reader
    
        pthread_join function for Reader            
    end FOR
  
   
end main
