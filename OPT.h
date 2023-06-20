#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

void OPT(int n, int *arr, int pageFrame, int **pageFrameArr, char *pageFaultArr)
{
    // gán giá trị đầu tiên của mảng vào page frame
    pageFrameArr[0][0] = arr[0];
    // gán giá trị đầu tiên của mảng vào page fault
    pageFaultArr[0] = '*';
    for (int i = 1; i < n; ++i)
    {
        int check = false;
        for (int j = 0; j < pageFrame; ++j)
        {
            if (arr[i] == pageFrameArr[j][i])
            {
                check = true;
                break;
            }
        }
        if (check)
        {
            pageFaultArr[i] = ' ';
            for (int j = 0; j < pageFrame; ++j)
            {
            }
        }
        else
        {
            pageFaultArr[i] = '*';
            for (int j = 0; j < pageFrame; ++j)
            {
                if (pageFrameArr[j][i] == -1)
                {
                    pageFrameArr[j][i] = arr[i];
                    break;
                }
            }
        }
    }
    // duyệt từ phần tử thứ 2 của mảng
    // 2 1 5 2 0 5 0 4 0 0 7
    // 2 2 2 2 0 0 0 0 0 0 7
    //   1 1 1 1 1 1 4 4 4 4
    //     5 5 5 5 5 5 5 5 5
    // * * *   *     *     *
    // Number of Page Fault: 6
}
