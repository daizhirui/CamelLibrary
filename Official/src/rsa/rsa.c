/**
* @brief Greatest Common Dividor
* @param a Number 1.
* @param b Number 2.
* @return The greatest common dividor of number 1 and number 2.
*/
long long gcd(long long a, long long b)
{
    long long c;
    if ( a > b ) {
        c = a;
        a = b;
        b = c;
    }
    while ( a != 0 ) {
        c = a;
        a = b % a;
        b = c;
    }
    return b;
}
