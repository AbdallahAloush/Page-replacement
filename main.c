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
            return i; // function returns 1 on hit
        // we can make the function append to the array in case of miss
    }
    // TODO: call replacement algorithm
    return -1; // function returns 0 on miss
}

/*
We can think of a better algorithm to implement getting the maximum index
but since we deal with small arrays it won't make much of a difference
*/
// O(n) algorithm
int maxIndex(int *array, int arraySize)
{
    int indexMax = 0;
    int maximumElement = array[0];
    for (int i = 0; i < arraySize; i++)
    {
        if (array[i] > maximumElement)
        {
            maximumElement = array[i];
            indexMax = i;
        }
    }
    return indexMax;
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
    int j = 0;           // Another variable for operating on frames array
    int hMResult;        // Used to store the result of the hit miss function
    int nextReplace = 0; // Index of the element in the frames array that is going to be replaced

    //  We took the number of pages as an argument to be able to loop on it
    for (int i = 0; i < numberOfPages; i++)
    {
        hMResult = hitMiss(framesArray, j, pagesArray[i]);
        if (hMResult == -1 && j < numberOfFrames) // if the frames array is not full and miss
        {
            // Adding the element to the array
            framesArray[j++] = pagesArray[i];

            // Printing
            printf("%02d     ", pagesArray[i]);
            printArr(framesArray, j);
        }
        else if (hMResult == -1) // if the frames array is full and miss
        {
            // Replacing the element that has been in the array the longest
            framesArray[nextReplace] = pagesArray[i];

            // setting the index that is going to be replaced next
            (nextReplace == numberOfFrames - 1) ? nextReplace = 0 : nextReplace++;

            countPageFaults++; // incrementing the number of page faults

            // Printing
            printf("%02d F   ", pagesArray[i]);
            printArr(framesArray, j);
        }
        else // hit case
        {
            // Printing
            printf("%02d     ", pagesArray[i]);
            printArr(framesArray, j);
        }
    }
    // Free both arrays because we won't be needing them
    free(pagesArray);
    free(framesArray);
    return countPageFaults;
}

int LRU(int *pagesArray, int numberOfFrames, int numbeOfPages)
{
    int *framesArray = malloc(sizeof(int) * numberOfFrames);
    int *timeSince = malloc(sizeof(int) * numberOfFrames); // This will be used to store when was each element used
    int countPageFaults = 0;
    int j = 0;           // Another variable for operating on frames array
    int hMResult;        // Used to store the result of the hit miss function
    int nextReplace = 0; // Index of the element in the frames array that is going to be replaced

    for (int i = 0; i < numbeOfPages; i++)
    {
        hMResult = hitMiss(framesArray, j, pagesArray[i]);
        if (j < numberOfFrames && hMResult == -1)
        {
            // miss case
            framesArray[j] = pagesArray[i]; // insert the element in the frames array
            timeSince[j] = 0;
            j++;
            for (int k = 0; k < j; k++) // Incrementing the time since for each element except for the recently initialzied
            {
                timeSince[k]++;
            }
            // Printing
            printf("%02d     ", pagesArray[i]);
            printArr(framesArray, j);
        }

        else if (hMResult == -1)
        {

            nextReplace = maxIndex(timeSince, j);
            framesArray[nextReplace] = pagesArray[i];
            timeSince[nextReplace] = 0;
            countPageFaults++;          // incrementing the number of page faults
            for (int k = 0; k < j; k++) // Incrementing the time since for each element except for the recently initialzied
            {
                if (k != nextReplace)
                    timeSince[k]++;
            }
            // Printing
            printf("%02d F   ", pagesArray[i]);
            printArr(framesArray, j);
        }

        else
        {
            timeSince[hMResult] = 0;    // last referenced input will be equal zero
            for (int k = 0; k < j; k++) // Incrementing the time since for each element except for the recently initialzied
            {
                if (k != hMResult)
                    timeSince[k]++;
            }

            // Printing
            printf("%02d     ", pagesArray[i]);
            printArr(framesArray, j);
        }
    }
    // Free both arrays because we won't be needing them
    free(pagesArray);
    free(framesArray);
    return countPageFaults;
}

int CLOCK(int *pagesArray, int numberOfFrames, int numberOfPages)
{
    int *framesArray = malloc(sizeof(int) * numberOfFrames);
    int *useBit = malloc(sizeof(int) * numberOfFrames);
    int countPageFaults = 0;
    int j = 0;           // Another variable for operating on frames array
    int hMResult;        // Used to store the result of the hit miss function
    int nextReplace = 0; // Index of the element in the frames array that is going to be replaced

    for (int i = 0; i < numberOfPages; i++)
    {
        hMResult = hitMiss(framesArray, j, pagesArray[i]);
        if (j < numberOfFrames && hMResult == -1)
        {
            framesArray[j] = pagesArray[i];
            useBit[j] = 1;
            j++;
            // setting the index that is going to be replaced next
            (nextReplace == numberOfFrames - 1) ? nextReplace = 0 : nextReplace++;

            // Printing
            printf("%02d     ", pagesArray[i]);
            printArr(framesArray, j);
        }
        else if (hMResult == -1)
        {
            countPageFaults++;
            while (useBit[nextReplace] == 1)
            {
                useBit[nextReplace] = 0;
                (nextReplace == numberOfFrames - 1) ? nextReplace = 0 : nextReplace++;
            }

            framesArray[nextReplace] = pagesArray[i];
            useBit[nextReplace] = 1;
            (nextReplace == numberOfFrames - 1) ? nextReplace = 0 : nextReplace++;
            
            // Printing
            printf("%02d F   ", pagesArray[i]);
            printArr(framesArray, j);
        }
        else // hit case
        {
            useBit[hMResult] = 1;
            // Printing
            printf("%02d     ", pagesArray[i]);
            printArr(framesArray, j);
        }
    }

    // Free both arrays because we won't be needing them
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
        countPageFaults = LRU(pages, numberOfFrames, i);
        break;
    case 'C':
    case 'c':
        countPageFaults = CLOCK(pages, numberOfFrames, i);
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
