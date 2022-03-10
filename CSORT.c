#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<sys/wait.h>
#include <semaphore.h>

#define MAX 7

sem_t mutex;
sem_t mutex2;
sem_t mutex3;

char array[MAX];
char store[MAX];
char isDebug = ' ';

// Our four process functions that will run concurrently
void *func1(); 
void *func2();
void *func3();
void *func4(int index);
void *help();


//function to check if array is sorted
// return true if sorted else false
bool isSorted(char array[],int N);


//convert the passed char array to lower case
void convert2Lower(char array[],int N);



int main(int argc, char** argv){

	//initializing semaphores
	sem_init(&mutex, 0, 1);
	sem_init(&mutex2, 0, 1);
	sem_init(&mutex3, 0, 1);
	
  int shmid;
    key_t key = IPC_PRIVATE;
    int *shm_array;
    int length = MAX;
 
  
    // Calculate segment length
    size_t SHM_SIZE = sizeof(int)*length;
 
    // Create the segment.
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        _exit(1);
    }
 
    // Now we attach the segment to our data space.
    if ((shm_array = shmat(shmid, NULL, 0)) == (int *) -1)
    {
        perror("shmat");
        _exit(1);
    }
  // for debuging process
	printf("Debug mode (y/n)? : ");
	scanf("%c",&isDebug);
	
	printf("Please enter 7 alphabet characters : ");
	scanf("%s",array);
	
	printf("Array before sorting: %s\n",array);


	
    // for lowering the alphabet
	  convert2Lower(array,MAX);
  
     func4(0);
     printf("Array after sorting: %s\n",array);
 
  sem_destroy(&mutex);
	sem_destroy(&mutex2);
	sem_destroy(&mutex3);
  

  /* Detach from the shared memory now that we are
       done using it. */
    if (shmdt(shm_array) == -1)
    {
        perror("shmdt");
        _exit(1);
    }
 
    /* Delete the shared memory segment. */
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        _exit(1);
    }
  
}

void *help()
{
	if(fork()==0)
  {
    func1();    
  }
  else 
  {
    if(fork()==0)
    {
      func2();      
    }
    else
    {
      if(fork()==0)
      {
         func3();         
      }
    }
  }
}

bool isSorted(char array[],int N){

	for (int i=0;i<N-1;i++){
  //  printf("%c",array[i]);
		if (array[i] > array[i+1])
			return false;
		
	}
	return true;

}

void convert2Lower(char array[],int N){

	for (int i=0;i<N;i++){
		if (array[i]>=65 && array[i]<=90)  //
			array[i]+=32;
	
	}


}


void *func1(){
	
	
	while (true){
		
		sem_wait(&mutex);
		sem_wait(&mutex3);
		
		//if array is sorted then post mutex and break loop
		if (isSorted(array,MAX)){
			sem_post(&mutex3);
			sem_post(&mutex);
			break;
		}
		
		
		
		
		
		if (array[0] > array[1]){
			char temp = array[0];
			array[0] = array[1];
			array[1] = temp;
			if (isDebug == 'y')	
				printf("Thread 1 swapped array[0] and array[1] with values %c and %c respectively.\n",array[0],array[1]);
			
		}
		
		if (array[1] > array[2])
    {
			char temp = array[1];
			array[1] = array[2];
			array[2] = temp;
			if (isDebug == 'y')	
				printf("Thread 1 swapped array[1] and array[2] with values %c and %c respectively.\n",array[1],array[2]);	
	
		}
		

		sem_post(&mutex3);
		sem_post(&mutex);

	}
	
	

}

void *func2(){
	
	
	while (true){
	
		sem_wait(&mutex);
		sem_wait(&mutex2);
		
		//if array is sorted then post mutex and break loop
		if (isSorted(array,MAX)){
			sem_post(&mutex2);
			sem_post(&mutex);
			break;
		}
		
		
		if (array[2] > array[3]){
		
			char temp = array[2];
			array[2] = array[3];
			array[3] = temp;

			if (isDebug == 'y')	
				printf("Thread 2 swapped array[2] and array[3] with values %c and %c respectively.\n",array[2],array[3]);	
				
		}
		
		if (array[3] > array[4]){
		
			char temp = array[3];
			array[3] = array[4];
			array[4] = temp;
			if (isDebug == 'y')	
				printf("Thread 2 swapped array[3] and array[4] with values %c and %c respectively.\n",array[3],array[4]);	
				
		}
	//	          printf("Array after sorting: %s\n",array);

		sem_post(&mutex2);
		sem_post(&mutex);
		
	}
	
	
}


void *func4(int index){
   while(isSorted(array,MAX)==false)
   {   
       for(int j=index;j<index+2;j++)
       {
         if(array[j]>array[j+1])
         {
            char temp = array[j];
            array[j] = array[j+1];
            array[j+1] = temp;

            if (isDebug == 'y')	
            printf("Process %d swapped array[%d] and array[%d] with values %c and %c respectively.\n",((j%3)+1),j,j+1,array[j],array[j+1]);	
         }
         if(isSorted(array, MAX))
         {
           break;
         }
       } 
       if(index==4)
       {
         index =0;
       }
       else
       {
         index = index+2;
       }
   }
}


void *func3(){
	
	
	while (true){
	
	
		sem_wait(&mutex2);
		sem_wait(&mutex3);
		
		//if array is sorted then post mutex and break loop
		if (isSorted(array,MAX)){
			sem_post(&mutex3);
			sem_post(&mutex2);
			break;
		}
		
		
		if (array[4] > array[5]){
			char temp = array[4];
			array[4] = array[5];
			array[5] = temp;
			if (isDebug == 'y')	
				printf("Thread 3 swapped array[4] and array[5] with values %c and %c respectively.\n",array[4],array[5]);	
				
		}
		
		if (array[5] > array[6]){
			char temp = array[5];
			array[5] = array[6];
			array[6] = temp;

			if (isDebug == 'y')	
				printf("Thread 3 swapped array[5] and array[6] with values %c and %c respectively.\n",array[5],array[6]);	
			
			
		}
		//          printf("Array after sorting: %s\n",array);

		sem_post(&mutex3);
		sem_post(&mutex2);
		
	}
	
}
