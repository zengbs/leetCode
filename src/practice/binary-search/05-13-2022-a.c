


int search(int* nums, int numsSize, int target){

   int l = -1;
   int r = numsSize;

   int m;

   while( l+1 != r ){

      m = l + (r-l)/2;

      if ( nums[m] < target ) l = m;
      else                    r = m;

   }

   return r;
}