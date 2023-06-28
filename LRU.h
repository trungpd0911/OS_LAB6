#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define true 1
// #define false 0

// void printResult(int pageFrame, int n, int *resultArray, int *arr, bool *pageFault, int *replaced)
// {
//     printf("t\t");
//     for (int i = 0; i < n; i++)
//         printf("%d\t", i);
//     printf("\n");

//     printf("ref\t\t");
//     for (int i = 0; i < n; i++)
//         printf("%d\t", arr[i]);
//     printf("\n");

//     for (int i = 0; i < pageFrame; i++)
//     {
//         printf("f\t\t");
//         for (int j = 0; j < n; j++)
//             printf("%d\t", resultArray[i * n + j]);
//         printf("\n");
//     }

//     printf("hit\t\t");
//     for (int i = 0; i < n; i++)
//         printf("%d\t", pageFault[i]);
//     printf("\n");

//     printf("v\t\t");
//     for (int i = 0; i < n; i++)
//         printf("%d\t", replaced[i]);
//     printf("\n");
// }

void LRU(int n, int *arr, int pageFrame)
{
    int ref[100] = {-1};
    bool *pageFault = (bool*) malloc(n * sizeof(bool));
    int *replaced = (int*) malloc(n * sizeof(int));
    int *resultArray = (int*) malloc((pageFrame * n) * sizeof(int));
    int curr = 0;

    for (int i = 0; i < pageFrame * n; i++)
        resultArray[i] = -1;

    // The first page
    resultArray[0] = arr[0];
    ref[arr[0]] = 0;

    // Other pages
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < curr; j++)
            resultArray[j * n + i] = resultArray[(j - 1) * n + i];

        // Check if the page is existing (If yes -> no page fault)
        bool existing = false;
        for (int j = 0; j < curr; j++)
        {
            if (resultArray[j * n + i] == arr[i])
                existing = true;
        }

        if (!existing)
        {
            // No page fault
            if (curr < pageFrame)
            {
                resultArray[curr * n + i] = arr[i];
                curr++;
            }
            // Page fault
            else
            {
                int minRefIndex = 0;
                for (int j = 1; j < curr; j++)
                {
                    if (ref[resultArray[j * n + i]] < ref[resultArray[minRefIndex * n + i]])
                    {
                        minRefIndex = j;
                    }
                }
                resultArray[minRefIndex * n + i] = arr[i];
            }
        }

        // Update reference
        ref[arr[i]] = i;
    }

    printResult(pageFrame, n, resultArray, arr, pageFault, replaced);

    free(resultArray);
    free(pageFault);
    free(replaced);
}