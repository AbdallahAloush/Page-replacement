#include <stdio.h>
#include <stdlib.h>
#define maxString 16
#define maxArray 128

//! FIFO (int* array, int numberOfFrames)
//! we need a search function
//! array printing function
//! array pasrsing

// This function is used to check if the new page is in the memory or not

int hitMiss(int *array, int arraySize, int key)
{
    for (int i = 0; i < arraySize; i++)
    {
        if (key == array[i])
            return 1; // function returns 1 on hit
        // we can make the function append to the array in case of miss
    }
    // TODO: call replacement algorithm
    return 0; // function returns 0 on miss
}

void printArr(int *array, int numberOfPrints)
{
    for (int i = 0; i < numberOfPrints; i++)
    {
        printf("%02d ", array[i]);
    }
    printf("\n");
}

int FIFO(int *pagesArray, int numberOfFrames, int numberOfPages)
{
    int *framesArray = malloc(sizeof(int) * numberOfFrames);
    int countPageFaults = 0;
    int j = 0;                  // Another variable for operating on frames array
    int nextReplace = 0;        // Index of the element in the frames array that is going to be replaced
    
    //  We took the number of pages as an argument to be able to loop on it
    for (int i = 0; i < numberOfPages; i++)
    {
        if (!hitMiss(framesArray, numberOfFrames, pagesArray[i]) && j < numberOfFrames)     // if the frames array is not full and miss 
        {
            //Adding the element to the array
            framesArray[j++] = pagesArray[i];

            //Printing
            printf("%02d     ", pagesArray[i]);
            printArr(framesArray, j);
        }
        else if (!hitMiss(framesArray, numberOfFrames, pagesArray[i]))          //if the frames array is full and miss 
        {
            //Replacing the element that has been in the array the longest
            framesArray[nextReplace] = pagesArray[i];
            
            //setting the index that is going to be replaced next 
            (nextReplace == numberOfFrames - 1) ? nextReplace = 0 : nextReplace++;
            
            countPageFaults++;          //incrementing the number of page faults
            
            //Printing
            printf("%02d F   ", pagesArray[i]);
            printArr(framesArray, j);
        }
        else            // hit case
        {
            //Printing
            printf("%02d     ", pagesArray[i]);
            printArr(framesArray, j);
        }
    }
    //Free both arrays because we won't be needing them
    free(pagesArray);
    free(framesArray);
    return countPageFaults;
}

int main(int argc, char const *argv[])
{
    int numberOfFrames;
    int tempPageNumber;
    int *pages = malloc(sizeof(int) * maxArray);
    int i = 0; // iteratr for scanning the page numbers as input
    int countPageFaults = 0;
    char replacementAlgo[maxString];

    scanf("%d", &numberOfFrames);
    scanf("%s", replacementAlgo);
    while (1)
    {
        scanf("%d", &tempPageNumber);
        if (tempPageNumber == -1)
            break;
        else
        {
            pages[i] = tempPageNumber;
            i++;
        }
    }

    // Making a switch case to be able to call each function
    // Since the 4 options has distinct first characters we can use switch case instead of using string comparisons
    // I accounted for ssmall letters although it's not in the template shown in the pdf just to be on the safe side
    printf("Replacement Policy = %s", replacementAlgo);
    printf("\n-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    switch (replacementAlgo[0])
    {
    case 'F':
    case 'f':
        countPageFaults = FIFO(pages, numberOfFrames, i);
        break;
    case 'L':
    case 'l':
        /* Call LRU */
        break;
    case 'C':
    case 'c':
        /* Call Clock */
        break;
    case 'O':
    case 'o':
        /* Call optimal*/
        break;
    default:
        printf("Error: make sure to input one of the replacement algorithms");
        break;
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d", countPageFaults);
    return 0;
}
