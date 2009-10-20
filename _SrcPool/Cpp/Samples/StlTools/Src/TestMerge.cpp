//: C06:MergeTest.cpp
// Test merging in sorted ranges.
//{L} Generators
/*Thinking in C++ Vol 2 - Practical Programming
 */
#include <algorithm>
#include "PrintSequence.h"
#include "Generators.h"
using namespace std;
 
 /*Merging sorted ranges
 In main( ), instead of creating two separate arrays, both ranges are created end to end in the array a. (This will come in handy for the inplace_merge.) The first call to merge( ) places the result in a different array, b. For comparison, set_union( ) is also called, which has the same signature and similar behavior, except that it removes duplicates from the second set. Finally, inplace_merge( ) combines both parts of a.
  */
int main() {
const int SZ = 15;
int a[SZ*2] = {0};
// Both ranges go in the same array:
generate(a, a + SZ, SkipGen(0, 2));
a[3] = 4;
a[4] = 4;
generate(a + SZ, a + SZ*2, SkipGen(1, 3));
print(a, a + SZ, "range1", " ");
print(a + SZ, a + SZ*2, "range2", " ");
int b[SZ*2] = {0}; // Initialize all to zero
merge(a, a + SZ, a + SZ, a + SZ*2, b);
print(b, b + SZ*2, "merge", " ");
// Reset b
for(int i = 0; i < SZ*2; i++)
b[i] = 0;
inplace_merge(a, a + SZ, a + SZ*2);
print(a, a + SZ*2, "inplace_merge", " ");
int* end = set_union(a, a + SZ, a + SZ, a + SZ*2, b);
print(b, end, "set_union", " ");
} ///:~
