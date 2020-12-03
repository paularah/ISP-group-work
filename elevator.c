//In this program we will create an elevator in C.
#include <stdio.h>
// Header file when using threads
#include <pthread.h>
//This library below will allow us to use the sleep function
#include <unistd.h>
#include <stdlib.h>


//Here we will define the elevator structure
//It has three main fields, the elevator's currentFloor which starts at 1, its destinationFloor which will depend on the array of values from 2 to 8 and the maxOccupancy which is 10 people.

struct Elevator{
    int currentFloor, destinationFloor, maxOccupancy;
};



int main() {
    
    //We need to have an array that will check for each user floor value from 2-8
    //We can create an array of size 10 and have it generate random floor numbers between 2-8 that our elevator will drop passengers at.


    return 0;
    
}