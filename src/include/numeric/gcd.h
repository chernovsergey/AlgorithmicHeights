#ifndef GCD_H
#define GCD_H


int64_t extended_GCD( int64_t a, int64_t b, int64_t & x, int64_t & y )
{
    if( a == 0 )
    {
        x = 0;
        y = 1;
        return b;
    }

    int64_t p, q;
    int64_t d = extended_GCD( a % b, b, p, q );
    x = q - ( b / a ) * p;
    y = p;
    return d;
}

#endif // GCD_H
