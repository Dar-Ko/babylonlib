//: C06:SetOperations.cpp
// Set operations on sorted ranges.
//{L} Generators 
/*Thinking in C++ Vol 2 - Practical Programming
It s easiest to see the set operations demonstrated using simple vectors of characters. These characters are randomly generated and then sorted, but the duplicates are retained so that you can see what the set operations do when there are duplicates.

After v and v2 are generated, sorted, and printed, the includes( ) algorithm is tested by seeing if the entire range of v contains the last half of v. It does, so the result should always be true. The array v3 holds the output of set_union( ), set_intersection( ), set_difference( ), and set_symmetric_difference( ), and the results of each are displayed so you can ponder them and convince yourself that the algorithms work as promised.

 */
#include <algorithm>
#include <vector>
#include "Generators.h"
#include "PrintSequence.h"
using namespace std;
/*Set operations on sorted ranges

Once ranges have been sorted, you can perform mathematical set operations on them.
*/
int main() 
{
const int SZ = 30;
char v[SZ + 1], v2[SZ + 1];
CharGen g;
generate(v, v + SZ, g);
generate(v2, v2 + SZ, g);
sort(v, v + SZ);
sort(v2, v2 + SZ);
print(v, v + SZ, "v", "");
print(v2, v2 + SZ, "v2", "");
bool b = includes(v, v + SZ, v + SZ/2, v + SZ);
cout.setf(ios::boolalpha);
cout << "includes: " << b << endl;
char v3[SZ*2 + 1], *end;
end = set_union(v, v + SZ, v2, v2 + SZ, v3);
print(v3, end, "set_union", "");
end = set_intersection(v, v + SZ, v2, v2 + SZ, v3);
print(v3, end, "set_intersection", "");
end = set_difference(v, v + SZ, v2, v2 + SZ, v3);
print(v3, end, "set_difference", "");
end = set_symmetric_difference(v, v + SZ,
v2, v2 + SZ, v3);
print(v3, end, "set_symmetric_difference","");
} ///:~
