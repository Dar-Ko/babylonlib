/*
In mathematics Mathematics is commonly defined as the study of patterns of structure, change, and space; more informally, one might say it is the study of "figures and numbers". In the formalist view, it is the investigation of axiomatically defined abstract structures using symbolic logic and mathematical notation; other views are described in Philosophy of mathematics. Mathematics might be seen as a simple extension of spoken and written languages, with an extremely precisely defined vocabulary and grammar, for the purpose of describing and exploring physical and conceptual relationships.
..... Click the link for more information. , the greatest common divisor (gcd) or highest common factor (hcf) of two integers The integers consist of the positive natural numbers (1, 2, 3, …) the negative natural numbers (-1, -2, -3, ...) and the number zero. The set of all integers is usually denoted in mathematics by Z (or Z in blackboard bold, ), which stands for Zahlen (German for "numbers"). They are also known as the whole numbers, although that term is also used to refer only to the positive integers (with or without zero). Like the natural numbers, the integers form a countably infinite set. The branch of mathematics which includes the study of the integers is called number theory.
..... Click the link for more information.  which are not both zero is the largest integer that divides In mathematics, a divisor of an integer n, also called a factor of n, is an integer which evenly divides n without leaving a remainder. For example, 7 is a divisor of 42 because 42/7 = 6. We also say 42 is divisible by 7 or 7 divides 42 and we usually write 7 | 42. Divisors can be positive or negative. The positive divisors of 42 are .
..... Click the link for more information.  both numbers.
The greatest common divisor of a and b is written as gcd(a, b), or sometimes simply as (a, b). For example, gcd(12, 18) = 6, gcd(-4, 14) = 2 and gcd(5, 0) = 5. Two numbers are called coprime In mathematics, the integers a and b are said to be coprime or relatively prime iff they have no common factor other than 1 and -1, or equivalently, if their greatest common divisor is 1.

For example, 6 and 35 are coprime, but 6 and 27 are not because they are both divisible by 3. 1 is coprime to every integer; 0 is coprime only to 1 and -1.

A fast way to determine whether two numbers are coprime is given by the Euclidean algorithm.
..... Click the link for more information. or relatively prime if their greatest common divisor equals 1. For example, 9 and 28 are relatively prime.

The greatest common divisor is useful for reducing fractions In common usage a fraction is any part of a unit.

In mathematics:


A vulgar fraction is a rational number written as one integer (the numerator) divided by a non-zero integer (the denominator). The line that separates the numerator and the denominator is called the Vinculum. Sub-categories of vulgar fraction include:


..... Click the link for more information.  to be in lowest terms An irreducible fraction is a fraction a/b, where the numerator a is an integer and the denominator b is a positive integer, such that there is not another fraction c/d with c smaller in absolute value than a and 0<d<b, and c and d are integers, that represents the same number. To say that a fraction is irreducible and to say that it is in lowest terms are synonymous.
..... Click the link for more information. . Consider for instance

where we cancelled 14, the greatest common divisor of 42 and 56.

Calculating the gcd While the gcd of two numbers can in principle be computed by determining the prime factorizations In mathematics, a prime number, or prime for short, is a natural number whose only distinct positive divisors are 1 and itself; otherwise it is called a composite number. The number 1 is neither prime nor composite; a factor of 1 is of no interest in any product. The property of being a prime is called primality.

The sequence of prime numbers begins


2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113

..... Click the link for more information.  of the two numbers and comparing factors, this is never done in practice, because it is too slow. A much more efficient method is the Euclidean algorithm The Euclidean algorithm (also called Euclid's algorithm) is an algorithm to determine the greatest common divisor (gcd) of two integers. It is one of the oldest algorithms known, since it appeared in Euclid's Elements around 300 BC. The algorithm does not require factoring.

Algorithm and implementationGiven two natural numbers a and b, check if b is zero. If yes, a is the gcd. If not, repeat the process using b and the modulo of a and b as the two inputs. In Scheme, the algorithm can be naturally expressed as:
 (define (gcd a b) (if (= b 0) a (gcd b (modulo a b))))

..... Click the link for more information. . An extended version The extended Euclidean algorithm is a version of the Euclidean algorithm; its input are two integers a and b and the algorithm computes their greatest common divisor (gcd) as well as integers x and y such that ax + by = gcd(a, b). This works because the steps of Euclid's algorithm always deal with sums of multiples of a and b.
..... Click the link for more information.  of this algorithm can also compute integers p and q such that a·p + b·q = gcd(a, b).

Properties Every common divisor of a and b is a divisor of gcd(a, b).

gcd(a, b), where a and b are not both zero, may be defined alternatively and equivalently as follows: it is the smallest positive integer d which can be written in the form a·p + b·q where p and q are integers.

If gcd(a, b) = d and a divides the product b·c, then a/d divides c.

If m is any integer, then gcd(m·a, m·b) = m·gcd(a, b) and gcd(a + m·b, b) = gcd(a, b). If m is a nonzero common divisor of a and b, then gcd(a/m, b/m) = gcd(a, b)/m.

The gcd of three numbers can be computed as gcd(a, b, c) = gcd(gcd(a, b), c) = gcd(a, gcd(b, c)).

gcd(a, b) is closely related to the least common multiple In arithmetic and number theory the least common multiple or lowest common multiple (lcm) or smallest common multiple of two integers a and b is the smallest positive integer that is a multiple of both a and b. If there is no such positive integer, e.g., if a = 0 or b = 0, then lcm(a, b) is defined to be zero.
..... Click the link for more information.  lcm(a, b): we have

gcd(a, b)·lcm(a, b) = a·b.
Furthermore, the following versions of distributivity In mathematics, and in particular in abstract algebra, distributivity is a property of binary operations that generalises the distributive law from elementary algebra. For example:
4 · (2 + 3) = (4 · 2) + (4 · 3)
In the left-hand side of the above equation, the 4 multiplies the sum of 2 and 3; on the right-hand side, it multiplies the 2 and the 3 individually, with the results added afterwards. Because these give the same final answer (20), we say that multiplication by 4 distributes over addition of 2 and 3. Since we could have put any real numbers in place of 4, 2, and 3 above, and still gotten a true equation, we say that multiplication of real numbers distributes over addition of real numbers.
..... Click the link for more information.  hold true:
gcd(a, lcm(b, c)) = lcm(gcd(a, b), gcd(a, c))
lcm(a, gcd(b, c)) = gcd(lcm(a, b), lcm(a, c)).
Geometrically, gcd(a, b) is the number of points with integral coordinates on the straight line joining the points (0, 0) and (a, b), excluding (0, 0).


The gcd in commutative rings The greatest common divisor can more generally be defined for elements of an arbitrary commutative ring In ring theory, a branch of abstract algebra, a ring is an algebraic structure in which addition and multiplication are defined and have similar properties to those familiar from the integers.


History See Ring theory

Definition and notation A ring is an abelian group (R, +), together with a second binary operation * such that for all a, b and c in R,
a * (b*c) = (a*b) * c [Associativity]
a * (b+c) = (a*b) + (a*c) [* Pre-Distributive over +]
(a+b) * c = (a*c) + (b*c) [* Post-Distributive over +]

..... Click the link for more information. .
If R is a commutative ring, and a and b are in R, then an element of c of R is called a common divisor of a and b if it divides both a and b (that is, if there are elements x and y in R such that c·x = a and c·y = b). If c is a common divisor of a and b, and every common divisor of a and b divides c, then c is called a greatest common divisor of a and b.

Note that gcd(a, b) need not be unique, but if R is an integral domain

In abstract algebra, an integral domain, is a commutative ring with 0 ? 1 in which the product of any two non-zero elements is always non-zero. Integral domains are generalizations of the integers and provide a natural setting for studying divisibility.

Alternatively and equivalently, integral domains may be defined as commutative rings in which the zero ideal is prime, or as the subrings of fields.
..... Click the link for more information.  then any two gcd's of a and b must be associate elements

In abstract algebra, an integral domain, is a commutative ring with 0 ? 1 in which the product of any two non-zero elements is always non-zero. Integral domains are generalizations of the integers and provide a natural setting for studying divisibility.

Alternatively and equivalently, integral domains may be defined as commutative rings in which the zero ideal is prime, or as the subrings of fields.
..... Click the link for more information. . Also, a and b need not have a gcd at all unless R is a unique factorization domain In mathematics, a unique factorization domain (UFD) is, roughly speaking, a commutative ring in which every element can be uniquely written as a product of prime elements, analogous to the fundamental theorem of arithmetic for the integers.

Formally, a unique factorization domain is defined to be an integral domain R in which every non-zero non-unit x of R can be written as a product of irreducible elements of
..... Click the link for more information. . If R is a Euclidean domain In abstract algebra, a Euclidean domain (also called a Euclidean ring) is a type of ring in which the Euclidean algorithm can be used.

More precisely, a Euclidean domain is an integral domain D for which can be defined a function v mapping nonzero elements of D to non-negative integers and possessing the following properties:

For all nonzero a and b in D, v(ab) = v(a).
If a and b are in D and b is nonzero, then there are q and r in D such that a = qb + r and either r = 0 or v(r) < v(b).

..... Click the link for more information.  then a form of the Euclidean algorithm can be used to compute the gcd.
*/
/*----------------------------------------------------------------------------
 * binary greatest common divisor by Silver and Terzian.  See Knuth
 * both inputs must be >= 0
 The Greatest Common Divisor, GCD for short, of two positive integers can be computed with Euclid's division algorithm. Let the given numbers be a and b, a >= b. Euclid's division algorithm has the following steps:

Compute the remainder c of dividing a by b.
If the remainder c is zero, b is the greatest common divisor.
If c is not zero, replace a with b and b with the remainder c. Go back to step (1).

 */
int GreatestCommonDivisor(int u, int v)
{
  int k, t, f;

  if (u < 0 || v < 0)
    return( 1 );                       /* error if u < 0 or v < 0 */
  k = 0, f = 1;
  while ((u%2 == 0) && (v%2 == 0)) {
    k++;
    u >>= 1;
    v >>= 1;
    f *= 2;
  }
  if (u & 1) {
    t = -v;
    goto B4;
  }
  else
    t = u;
B3:
  if (t > 0)
    t >>= 1;
  else
    t = -((-t) >> 1);
B4:
  if (t%2 == 0)
    goto B3;

  if (t > 0)
    u = t;
  else
    v = -t;
  if ((t = u-v) != 0)
    goto B3;
  return( u*f );
}
// <B style="color:black;background-color:#A0FFFF">Function</B> Name:<B style="color:black;background-color:#ffff66">Greatest Common Divisor </B><B style="color:black;background-color:#A0FFFF">Function</B>
// Description: Finds the <B style="color:black;background-color:#ffff66">greatest common divisor</B> of the solution fraction
In mathematics, a divisor of an integer n, also called a factor of n, is an integer which evenly divides n without leaving a remainder.

In mathematics Mathematics is commonly defined as the study of patterns of structure, change, and space; more informally, one might say it is the study of "figures and numbers". In the formalist view, it is the investigation of axiomatically defined abstract structures using symbolic logic and mathematical notation; other views are described in Philosophy of mathematics. Mathematics might be seen as a simple extension of spoken and written languages, with an extremely precisely defined vocabulary and grammar, for the purpose of describing and exploring physical and conceptual relationships.
..... Click the link for more information. , the greatest common divisor (gcd) or highest common factor (hcf) of two integers The integers consist of the positive natural numbers (1, 2, 3, …) the negative natural numbers (-1, -2, -3, ...) and the number zero. The set of all integers is usually denoted in mathematics by Z (or Z in blackboard bold, ), which stands for Zahlen (German for "numbers"). They are also known as the whole numbers, although that term is also used to refer only to the positive integers (with or without zero). Like the natural numbers, the integers form a countably infinite set. The branch of mathematics which includes the study of the integers is called number theory.
..... Click the link for more information.  which are not both zero is the largest integer that divides In mathematics, a divisor of an integer n, also called a factor of n, is an integer which evenly divides n without leaving a remainder. For example, 7 is a divisor of 42 because 42/7 = 6. We also say 42 is divisible by 7 or 7 divides 42 and we usually write 7 | 42. Divisors can be positive or negative. The positive divisors of 42 are .
..... Click the link for more information.  both numbers.


    int GreatestCommonDivisor(int a, int b){


        if (a < 0) {
        a = (a * -1);
    }


        if (b < 0) {
        b = (b * -1);
    }
    //assert(b != 0);
    int rem = a % b;


        while(rem !=0 ){
        a = b;
        b = rem;
        rem = a % b;
    }
    return b;
}
