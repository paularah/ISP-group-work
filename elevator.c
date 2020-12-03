#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


//Here we will define the elevator structure
//It has three main fields, the elevator's currentFloor which starts at 1, its destinationFloor which will depend on the array of values from 2 to 8 and the maxOccupancy which is 10 people.

struct Elevator{
    int currentFloor, destinationFloor, maxOccupancy;
};

void *elevatorFlow(void * floors){

}



int main() {
    
    //We need to have an array that will check for each user floor value from 2-8
    //We can create an array of size 20 and have it generate random floor numbers between 2-8 that our elevator will drop its 10 passengers at.
    //I increased the userDestinations size from 10 to 20 because it brought a "*** stack smashing detected ***: terminated" error message

    int userDestinations[20];
    int j, gen;
    int startingFloor = 1;
    int topFloor = 8;
    
    //This loop will create random user destinations for our 10 passengers between 2 to 8.
    for (j = 1; j < 11; j++)
    {
        //We defined the topFloor and startingFloor and with them we will obtain random values for each passenger using this formula
        userDestinations[j] = (rand() % (topFloor - startingFloor + 2)) + startingFloor;
        printf("\nPassenger %d: Floor %d\n", j, userDestinations[j]);
    }

    //The next part I am not quite sure to implement is how to utilise threads into this. 

    //I was thinking of somehow incorporating the values generated above into the thread function and having it check for each floor number. From there, a sleep() would be called as the passengers leave the elevator.

    pthread_t floorThreads[8];
    
    
    

    return 0;
    
}