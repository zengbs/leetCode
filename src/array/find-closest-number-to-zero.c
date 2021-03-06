#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


int findClosestNumber(int* nums, int numsSize){

   int closestDistance = INT_MAX;
   int value           = INT_MAX;
   int index;

   for( int i=0;i<numsSize;i++ ){


      // choose the smaller number between two numbers that have different distance to zero
      // --> e.g. +2 and -1
      if ( closestDistance > abs(nums[i]) ){
         if ( value > abs(nums[i]) ) { value = abs(nums[i]); index = i; }

         // update the closest distance
         closestDistance = abs(nums[i]);
      }

      // choose the larger numer between two identical closest number
      // --> e.g. -1 and +1
      if( closestDistance == abs(nums[i]) ){
         if ( value <= nums[i] )     { value = abs(nums[i]); index = i; }
      }

   }

   return nums[index];
}

int main (){

   int arr[] = { 1,-1};

   int ans = findClosestNumber(arr, sizeof(arr)/sizeof(arr[0]));

   printf("%d\n", ans);

   return 0;
}
