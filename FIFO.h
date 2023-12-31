#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define true 1
#define false 0

void FIFO(int n, int *arr, int pageFrame, int **pageFrameArr, char *pageFaultArr)
{
    int curr = 0;
    int oldestPageIndex = 0;

    // The first page
    pageFrameArr[0][0] = arr[0];
    pageFaultArr[0] = '*';
    curr++;

    // Other pages
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < curr; j++)
            pageFrameArr[j][i] = pageFrameArr[j][i - 1];

        // Check if the page is existing (Yes -> no page fault, No -> page fault)
        bool existing = false;
        for (int j = 0; j < curr; j++)
        {
            if (pageFrameArr[j][i] == arr[i])
                existing = true;
        }

        if (!existing)
        {
            if (curr < pageFrame)
            {
                pageFrameArr[curr][i] = arr[i];
                curr++;
            }
            else
            {
                pageFrameArr[oldestPageIndex][i] = arr[i];
                oldestPageIndex = (oldestPageIndex + 1) % pageFrame;
            }

            pageFaultArr[i] = '*';
        }
    }
}
