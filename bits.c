/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    int x1 = x & y;
    int x2 = (~x) & (~y);
    x1 = ~x1;
    x2 = ~x2;
    return x1 & x2;
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x) return !y;
    if(!y) return 0;
    return !((x^y) >> 31);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int r = (v>0xFFFF) << 4;
    int s;
    v >>= r;

    s = (v>0xFF) << 3;
    r |= s;
    v >>= s;

    s = (v>0xF) << 2;
    r |= s;
    v >>= s;

    s = (v>3) << 1;
    r |= s;
    v >>= s;
    
    return r | (v>>1);
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int a = (x>>(n<<3)) & 0xFF;
    int b = (x>>(m<<3)) & 0xFF;
    int diff = a^b;
    return x ^ (diff << (n<<3)) ^ (diff << (m<<3));
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned a=0u;
    int i = 32;
    while(i){
        a = (a<<1)|(v&1u);
        v>>=1;
        i--;
    }
    return a;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int b = 1 << 31;
    int a = !!(x&b);
    x = (x&~b) >> n;
    a = a << (31 + (~n + 1));
    return x|a;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int v = ~x;
    int n = !(v >> 16) << 4;
    int count = n;
    v <<= n;

    n = !(v >> 24) << 3;
    count += n;
    v <<= n;

    n = !(v >> 28) << 2;
    count += n;
    v <<= n;

    n = !(v >> 30) << 1;
    count += n;
    v <<= n;

    n = !(v >> 31);
    count += n;
    v <<= n;

    return count + !v;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if(x==0) return 0;
    unsigned s = x & (1u<<31);
    if (s){
        x = ~x + 1;
    }
    int e = 158; //阶数
    while(!(x&(1u<<31))){
        x <<= 1;
        e--;
    }
    unsigned f = (x & 0x7FFFFFFF) >> 8;
    unsigned tail = x & 0xFF;
    if((tail>0x80) | ((tail == 0x80) & (f&1))) f = f + 1;
    return s + (e << 23) + f;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned s = uf & 0x80000000;
    unsigned e = (uf>>23) & 0xFF;
    unsigned f = uf & 0x7FFFFF;

    if(e == 255) return uf;
    if(e == 0) return s | (f<<1);
    e++;
    if(e == 255)
        return s | 0x7F800000;

    return s | (e<<23) | f;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned s = uf2 >> 31;
    unsigned high;
    int e = (uf2 >> 20) & 0x7FF;
    e = e - 1023;
    
    if(e<0) return 0;

    if(e>30) return 0x80000000;

    high = (uf2 & 0xFFFFF) | (0x1 << 20) ;

    int ans;
    if(e > 20){
        ans = (high << (e-20) | (uf1 >> (52-e)));
    }
    else {
        ans = high >> (20-e);
    }
    if(s) ans = -ans;

    return ans;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
