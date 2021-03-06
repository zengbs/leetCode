
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct node_s {
   int value;
   struct node_s *next;
};

typedef struct node_s node_t;

void addNode( node_t **head, int value ){

   node_t *newNode = (node_t*)malloc(sizeof(node_t));

   newNode->value = value;
   newNode->next  = *head;
   *head = newNode;
}

void deleteNode( node_t **head, node_t *node ){

   node_t dummy;
   node_t *prev, *curr;

   dummy.next = *head;

   prev = &dummy;
   curr = *head;

   while( curr != NULL ){

      if ( curr == node ) {
         prev->next = curr->next;
         free(curr);
         *head = dummy.next;
         break;
      }
      prev = curr;
      curr = curr->next;
   }
}


node_t *searchTarget( node_t *head, int target )
{
   node_t *cur = head;

   while( cur != NULL ){
      if ( cur->value == target ){
         return cur;
      }
      cur = cur->next;
   }

   return NULL;
}




int countKDifference(int* nums, int numsSize, int k)
{
   int hashTableSize = 1000;

   node_t **hashTable = (node_t**)calloc(hashTableSize, sizeof(node_t*));


   // insert array elements into hash map
   for ( int i=0; i<numsSize; i++ )
      addNode( &hashTable[nums[i]%hashTableSize], nums[i] );


   int counter = 0;

   node_t **head, *partner;

   for ( int i=0; i<numsSize; i++ ){

      head   = &hashTable[nums[i]%hashTableSize];

      // count the number of nums[i]-k
      if ( nums[i]-k > 0 ){

         partner = hashTable[(nums[i]-k)%hashTableSize];

         while( partner != NULL ){
            partner = searchTarget( partner, nums[i]-k );
            counter++;
            if (partner != NULL) partner = partner->next;
         }
      }

      // count the number of nums[i]+k
      partner = hashTable[(nums[i]+k)%hashTableSize];

      while( partner != NULL ){
         partner = searchTarget( partner, nums[i]+k );
         counter++;
         if (partner != NULL) partner = partner->next;
      }

      // delete node
      node_t *delete = searchTarget( *head, nums[i] );

      deleteNode( head, delete );

   }

   return counter;
}


int main (){

   int arr[] = { 1, 3 };

   int k = 3;

   int ans = countKDifference(arr, sizeof(arr)/sizeof(arr[0]), k);

   printf("%d\n", ans);

   return 0;
}
