all: assign4mon_exe assign4sem_exe
	gcc -o assign4mon_exe Assign4_mon.c -lpthread
	gcc -o assign4sem_exe Assign4_sem.c -lpthread	
assign4mon_exe: Assign4_mon.c
	gcc -o assign4mon_exe Assign4_mon.c -lpthread
assign4sem_exe: Assign4_sem.c
	gcc -o assign4sem_exe Assign4_sem.c -lpthread 
clean:
	rm *.out all
