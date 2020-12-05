//gcc main.c -o a.out -lpthread

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MaxPassInEl 10
#define TotalPass 10
#define startingFloor 1
#define topFloor 8

//Structures used
	
	struct elevator{
			
			int maxPass;
			int currentPass;
			int passArr[TotalPass][2];
			int direction;
			int currentFloor;
			//implement destination floor
			};

	struct passenger{
			
			int currentFloor;
			int destFloor;
			//status can be 0=waiting for Elevator, 1= in Elevator, 2=out off Elevator 
			int status;
			};

//Global Varibles

struct elevator *Elv0;
struct passenger* passList[TotalPass];	
pthread_mutex_t lock;	


//Function Prototypes
void *createPass(void *passId);
void *passEntry(void *passId);
void *passExit(void *passId);

//funtion to create all passengers
void *createPass(void *passId){

	int passID = *((int*) passId);

	//new pass is allocated space
	struct passenger *Passanger = (struct passenger*) malloc(sizeof(struct passenger));
	passList[passID]=Passanger;
	//starting floor is 1
	passList[passID]->currentFloor=1;
	printf("Passenger %d Created\n", passID);
	//printf("Dumbass %d", passID);
	free(passId);
}


//Allows passengers to enter elv
void *passEntry(void *passId){

	int passID = *((int*) passId);

	pthread_mutex_lock(&lock);
	
	//if elv is on same floor as pass
	if ((passList[passID]->currentFloor == Elv0->currentFloor)&&(Elv0->currentPass!=MaxPassInEl))
	{	//if pass is awaiting elv
		if(passList[passID]->status==0)
		{
			//pass gets on elv
			Elv0->currentPass++;
			pthread_mutex_unlock(&lock);
			
			//picks random dest for pass
			int tempBuff = (rand() % (topFloor - startingFloor+1))+ startingFloor;
			bool check = true;

			//ensure random dest floor is not current floor
			while(check)
			{

				if(tempBuff == passList[passID]->currentFloor)
				{
					tempBuff = (rand() % (startingFloor - topFloor))+ startingFloor;
				}
				else
				{
					passList[passID]->destFloor= tempBuff;
					printf("Passenger %d got on at floor %d and is going to floor %d\n", passID, passList[passID]->currentFloor,passList[passID]->destFloor);
					passList[passID]->currentFloor = NULL;
					check=false;
				}
			}

			passList[passID]->status=1;
			
		}
	}
	else
	{
	
	//printf("Passenger %d got on floor %d is waiting\n", passID, Elv0->currentFloor);
	pthread_mutex_unlock(&lock);
	}
	
	free(passId);

}



//allows passengers to exit
void *passExit(void *passId){

	int passID = *((int*) passId);

	//if pass at index in on elv
	if(passList[passID]->status==1)
	{
		//if pass at index dest floor is same as elv current
		if( passList[passID]->destFloor == Elv0->currentFloor)
		{
			//lock pass number decrement it and set pass vars to indicate pass has left elv
			pthread_mutex_lock(&lock);
			Elv0->currentPass--;
			pthread_mutex_unlock(&lock);
			passList[passID]->status=2;
			printf("Passenger %d got off at floor %d\n", passID, Elv0->currentFloor);
		}
	
	}
	free(passId);

}

int main(){


	bool control = true;
	
	bool done = false;


		

	//assigns space in memory for working objects	
	Elv0 = (struct elevator*) malloc(sizeof(struct elevator));
	Elv0->currentFloor=1;
	
	pthread_t threadIds[TotalPass];	

	//Creates Passengers
	int i=0;
	for(;i<TotalPass;i++){
	
        	int *iPtr = malloc(sizeof(*iPtr));
		*iPtr = i;
		pthread_create(&threadIds[i], NULL, createPass, iPtr);
	
	}
	
	//joins threads
	i=0;
	for(;i<TotalPass;i++)
	{
       		pthread_join(threadIds[i], NULL);
	}

	while(control)
	{
	

	//Passengers exit the Elv
	i=0;
	for(;i<TotalPass;i++){
	
        	int *iPtr = malloc(sizeof(*iPtr));
		*iPtr = i;
		pthread_create(&threadIds[i], NULL, passExit, iPtr);
	
	}

	
	//joins threads
	i=0;
	for(;i<TotalPass;i++)
	{
       		pthread_join(threadIds[i], NULL);
	}
	

	//Passengers enter the Elv
	i=0;
	for(;i<TotalPass;i++){
	
        	int *iPtr = malloc(sizeof(*iPtr));
		*iPtr = i;
		pthread_create(&threadIds[i], NULL, passEntry, iPtr);
	}

	//joins threads
	i=0;
	for(;i<TotalPass;i++)
	{
       		pthread_join(threadIds[i], NULL);
	}

	
	
	i=0;
	bool finished=true;
	for(;i<TotalPass;i++)
	{
	       


		if( Elv0->currentFloor==topFloor)
		{
			Elv0->direction = -1;
		}
		else if( Elv0->currentFloor==startingFloor)
		{
			Elv0->direction = 1;
		}

		
		i=0;
		for(;i<TotalPass;i++)
		{
			if(passList[i]->status!=2)
			{
				finished = false;
			
			}
		}
	}

		if(finished)
		{
		control=false;
		}

		Elv0->currentFloor = Elv0->direction+Elv0->currentFloor;
		printf("!!!!!Elevator is now at floor %d !!!!!\n",Elv0->currentFloor);
	
	
	}

	
	//Elv0->startingFloor=1;
	//printf("Dumbass %d", Elv0->startingFloor);



}



