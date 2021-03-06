// TITLE: merge sorted linked list
// TAG:   linked-list, dummy-node
// LEVEL: easy
// https://www.geeksforgeeks.org/merge-two-sorted-linked-lists/

#include <stdio.h>
#include <stdlib.h>
#include "../include/tools.h"
#include "../include/linkedList.h"


#ifdef SOLUTION
#define METHOD_1
//===============================================
//   rotate a->next
//   src
//   |a|-->|b|-->|N|
//
//   |N|
//   det
//-----------------------------------------------
//   move src forward
//         src
//   |a|   |b|-->|N|
//    ↓
//   |N|
//   det
//-----------------------------------------------
//   move det backward
//   det   src
//   |a|   |b|-->|N|
//    ↓
//   |N|
//===============================================
void moveNode( node_t **src, node_t **det ){

   node_t *curr = *src;

   *src = (*src)->next;

   curr->next = *det;

   *det = curr;
}


//=====================================================
// Step 1:
//                a
//               |2|-->|8|--> NULL
//
//               |3|-->|7|--> NULL
//                b
//
//   |d|-->|N|
//    t
//------------ moveNode( &a, &(tail->next) ) ----------
// Step 2:
//                      a
//                     |8|--> NULL
//
//               |3|-->|7|--> NULL
//                b
//
//   |d|-->|2|-->|N|
//    t
//------------ tail = tail->next ----------
// Step 3:
//                      a
//                     |8|--> NULL
//
//               |3|-->|7|--> NULL
//                b
//
//   |d|-->|2|-->|N|
//          t
//------------ moveNode( &b, &(tail->next) ) ----------
// Step 4:
//                      a
//                     |8|--> NULL
//
//                     |7|--> NULL
//                      b
//
//   |d|-->|2|-->|3|-->|N|
//          t
//------------ tail = tail->next ----------
// Step 5:
//                      a
//                     |8|--> NULL
//
//                     |7|--> NULL
//                      b
//
//   |d|-->|2|-->|3|-->|N|
//                t
//=====================================================
#ifdef METHOD_1
node_t* mergeSortedList( node_t *a, node_t *b )
{
   node_t dummy, *tail;

   tail = &dummy;

   dummy.next = NULL;


   while ( 1 ){

      if ( a == NULL ) { tail->next = b; break; }
      if ( b == NULL ) { tail->next = a; break; }

      if ( a->value <= b->value )
         moveNode( &a, &(tail->next) );
      else
         moveNode( &b, &(tail->next) );

      tail = tail->next;

   }

   return dummy.next;
}
#endif


//=====================================================
// Step 1:
//            a
//           |2|-->|8|--> NULL
//
//           |3|-->|7|--> NULL
//            b
//
//            result = NULL        last = &result
//           *result =            *last =  result
//                               **last =  NULL
//-----------------------------------------------------
// Step 2: *last = &|2| (i.e. result = &|2|)
//
//         result
//           last      a
//           |2|      |8|--> NULL
//            ↓
//           NULL
//
//           |3|-->|7|--> NULL
//            b
//
//            result = &|2|              last = &result
//           *result =  |2|             *last =  result
//                                     **last =  |2|
//-----------------------------------------------------
// Step 3:  last = &((*last)->next);
//
//        result    a
//           |2|   |8|--> NULL
//            ↓
//      last NULL
//
//
//           |3|-->|7|--> NULL
//            b
//
//
//            result = &|2|         last = &(|2|->next)
//           *result =  |2|        *last =   |2|->next
//                                **last =   NULL
//-----------------------------------------------------
// Step 4: *last = &|3| (i.e. |2|->next = &|3|)
//
//        result        a
//           |2|       |8|--> NULL
//            ↓
//       last|3|       |7|--> NULL
//            ↓         b
//           NULL
//
//
//            result = &|2|         last = &(|2|->next)
//           *result =  |2|        *last =   |2|->next
//                                **last =   |3|
//-----------------------------------------------------
// Step 5:  last = &((*last)->next);
//
//        result    a
//           |2|   |8|--> NULL
//            ↓
//           |3|   |7|--> NULL
//            ↓     b
//      last NULL
//
//            result = &|2|         last = &(|3|->next)
//           *result =  |2|        *last =   |3|->next
//                                **last =   NULL
//-----------------------------------------------------
// Step 6: *last = &|7| (i.e. |3|->next = &|7|)
//
//        result    a
//           |2|   |8|--> NULL
//            ↓
//           |3|-->|7|last         (b:NULL)
//                  ↓
//                 NULL
//
//            result = &|2|         last = &(|3|->next)
//           *result =  |2|        *last =   |3|->next
//                                **last =   |7|
//-----------------------------------------------------
// Step 7:  last = &((*last)->next);
//
//        result    a
//           |2|   |8|--> NULL
//            ↓
//           |3|-->|7|             (b:NULL)
//                  ↓
//                 NULL last
//
//            result = &|2|         last = &(|7|->next)
//           *result =  |2|        *last =   |7|->next
//                                **last =   NULL
//-----------------------------------------------------
// Step 8: *last = &|8| (i.e. |7|->next = &|8|)
//
//                 NULL
//                  ↑
//        result    |              (a:NULL)
//           |2|   |8|last
//            ↓     ↑
//           |3|-->|7|             (b:NULL)
//
//
//            result = &|2|         last = &(|7|->next)
//           *result =  |2|        *last =   |7|->next
//                                **last =   |8|
//-----------------------------------------------------
// Step 9:  last = &((*last)->next);
//
//                 NULL last
//                  ↑
//        result    |              (a:NULL)
//           |2|   |8|
//            ↓     ↑
//           |3|-->|7|             (b:NULL)
//
//
//            result = &|2|         last = &(|8|->next)
//           *result =  |2|        *last =   |8|->next
//                                **last =   NULL
//=====================================================
#ifdef METHOD_2
node_t* mergeSortedList( node_t *a, node_t *b )
{
   node_t *result = NULL;
   node_t **last = &result;

   while ( 1 ){

      if ( a == NULL ){
         *last = b;
         break;
      }

      else if ( b == NULL ){
         *last = a;
         break;
      }

      if ( a->value <= b->value ){
         moveNode( &a, last);
      }
      else{
         moveNode( &b, last);
      }


      last = &((*last)->next);
   }

   return result;
}
#endif
#endif

int main(){

   // create list 1
   node_t *list1 = NULL;
   for (int i=9;i>=-5;i--)   addNode( &list1, i );
   printList(list1);

   // create list 2
   node_t *list2 = NULL;
   for (int i=25;i>=0;i-=3) addNode( &list2, i );
   printList(list2);

   // merge sorted list
   node_t *list3 = NULL;
   list3 = mergeSortedList( list1, list2 );

   // print result
   printList(list3);


   // free memory
   freeList(list3);

   return 0;
}
