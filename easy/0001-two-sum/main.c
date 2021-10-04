#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>


//#define DEBUG

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){

    // Step-1: find the maximum and minimun values
    int max = INT_MIN;
    int min = INT_MAX;

    for (int i=0; i<numsSize; i++)
    {
      if (nums[i] > max) max = nums[i];
      if (nums[i] < min) min = nums[i];
    }
    // Step-2: add `abs(min)+1` to each element in `num`
    for (int i=0; i<numsSize; i++)
    {
      nums[i] += abs(min);

#     ifdef DEBUG
      printf("%d\n", nums[i]);
#     endif
    }

    // Step-3: add `2*(abs(min)+1)` to `target`
    target += 2*(abs(min));

    // Step-4: add `abs(min)+1` to `max`, `min`
    max += abs(min);
    min += abs(min);

#   ifdef DEBUG
    printf("max = %d, min = %d\n", max, min);
#   endif
    // Step-5: create a hash tabel with `max+1` in size and initialize with zero
    int hashTable[max+1];

    for (int i=0; i<max+1; i++) hashTable[i] = -1;

    int j = 0;
    bool duplicate = false;

    // Step-6: fill `i+1` in the hash table
    for (int i=0; i<numsSize; i++)
    {

       if ( hashTable[nums[i]] == -1 ) hashTable[nums[i]] = i;
       else
       {
         duplicate = true;
         j = i;
       }

#     ifdef DEBUG
      printf("hashTable[%d] = %d\n", nums[i], hashTable[nums[i]]);
#     endif
    }

    // Step-7:
    int *returnArry = NULL;

    bool second = false;

    for (int i=0; i<numsSize; i++)
    {
      if ( target-nums[i] >= 0 && target-nums[i]<max+1 &&  hashTable[target-nums[i]] != -1)
      {
#       ifdef DEBUG
        printf("idx of hashTable[] = target - nums[%d] = %d - %d = %d\n", i, target, nums[i], target-nums[i]);
#       endif

        *returnSize = 2;
        returnArry = (int*)malloc(*returnSize * sizeof(int));

        if (second && duplicate) returnArry[1] = j;
        else                     returnArry[0] = i;

        second = true;
      }

      //printf("%d %d\n", i, j);
    }

    // Step-8:
    return returnArry;
}


int main ()
{
  int numsSize    =  4;
  int target      = -7;

  int *nums       = malloc(numsSize*sizeof(int));
  int *returnArry = NULL;
  int  returnSize;


  nums[0] =  -3;
  nums[1] =   7;
  nums[2] =  -4;
  nums[3] =  15;
  //nums[4] =  4;

  returnArry = twoSum(nums, numsSize, target, &returnSize);

  if ( returnArry ) for (int i=0; i<returnSize; i++) printf("%d\n", returnArry[i]);
  else              printf("No answer!\n");


  return 0;
}
