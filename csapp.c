#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char* byte_pointer;

int bis(int x, int m) {
    // where m is 1, set x to 1
    return x | m;
}

int bic(int x, int m) {
    // where m is 1, set x to 0
    return x & ~m;
}

int bool_or(int x, int y) {
    return bis(x, y);
}

int bool_xor(int x, int y) {
    return bis(bic(x,y), bic(y, x));
}

void show_bytes(byte_pointer start, size_t len) {
    int i;
    for (i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void* x) {
    show_bytes((byte_pointer) &x, sizeof(void*));
}

void show_short(short x) {
    show_bytes((byte_pointer) &x, sizeof(short));
}

void show_long(long x) {
    show_bytes((byte_pointer) &x, sizeof(long));
}

void show_double(double x) {
    show_bytes((byte_pointer)&x, sizeof(double));
}

void inplace_swap(int* a, int* b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void reverse(int arr[], int cnt) {
    int first;
    int last;
    for (first = 0, last = cnt-1; first < last; first++, last--) {
        inplace_swap(&arr[first], &arr[last]);
    }
}

void print_array(int arr[], int cnt) {
    for (int i = 0; i < cnt; i++) {
        printf("%d ,", arr[i]);
    }
    printf("\n");
}

float sum_elements(float a[], unsigned length) {
    int i;
    float result = 0;
    for (i = 0; i <= length - 1; i++) {
        result += a[i];
    }
    return result;
}

int uadd_ok(unsigned x, unsigned y) {
    unsigned sum = x + y;
    return sum >= x;
}

// add without overflow?
int tadd_ok(int x, int y) {
    int sum = x + y;
    if ((sum < 0 && x > 0 && y > 0) || (sum >=0  && x < 0 && y < 0)) {
        return 0;
    }
    return 1;
}

//multiply without overflow?
int tmult_ok(int x, int y) {
    int64_t prod = x * y;
    return (int) x * y == prod;
}

int div16 (int x) {
    int bias = (1 << 4) - 1;

    int mask = x >> 31;

    int applied_bias = bias & mask;

    return (x + applied_bias) >> 4;
}

void print_bits(float f) {
    union { float f; unsigned int u; } x;
    x.f = f;
    for (int i = 31; i >= 0; i--) {
        printf("%d", (x.u >> i) & 1);
        if (i == 31 || i == 23) printf(" ");
    }
    printf("\n");
}

int is_little_endian() {
    int x = 1;
    unsigned char* p_x = (unsigned char*)&x;
    return p_x[0];
}

unsigned int lsb_x_rest_y(unsigned int x, unsigned int y) {

    return (x & 0xFF) | (y & ~(0xFF));
}

unsigned int replace_byte(unsigned int x, int i, unsigned char b) {
    return (x & ~(0xFFu << (i * 8))) | ((unsigned int)b << (i * 8));
}


int get_msb(int x) {
    int shift_val = (sizeof(int) - 1) << 3;
    int xright = x >> shift_val;
    return xright & 0xFF;
}

// any bit of x equals 1
int any_bit_equals_one(int x) {
    return x != 0;
}

int any_bit_equals_zero(int x) {
    return x != -1;
}

int any_bit_in_least_byte_equals_one(int x) {
    return (x & 0xFF) != 0;
}

int any_bit_in_most_byte_equals_zero(int x) {
    return ((x >> ((sizeof(int) - 1) << 3)) & 0xFF) != 0xFF;
}

int int_shifts_are_arithmetic() {
    int x = -1;
    return x >> 1 == x;
}

unsigned srl(unsigned x, int k) {
    //perform shift arithmetically
    unsigned xsra = (int) x >> k;
    int w = 8 * sizeof(int);
    unsigned mask = (1u << (w - k - 1));
    mask = (mask << 1) - 1;

    return xsra & mask;
}

int sra(int x, int k) {
    //perform shift logically
    int xsrl = (unsigned) x >> k;
    int w = 8 * sizeof(int);

    int msb_mask = 1 << (w - 1);
    int sign_bit = x & msb_mask;
    int sign_mask = !(sign_bit) - 1; //gives all ones if sign bit is 1, else 0
    int mask = ~(1u << (w - k - 1));
    mask =  (mask << 1) - 1;

    return xsrl | (sign_mask & mask);

}

//return 1 when any odd bit of x equals 1 else 0, w = 32;
int any_odd_one(unsigned x) {
    return !!(0xAAAAAAAAu & x);
}

//return 1 when x contains an odd number of 1s else 0, w=32;
int odd_ones(unsigned x) {
    x ^= (x >> 16);
    x ^= (x >> 8);
    x ^= (x >> 4);
    x ^= (x >> 2);
    x ^= (x >> 1);
    return x & 1;
}

//generate a mask indicating leftmost 1, w = 32
// e.g. 0xFF00 -> 0x8000
// if x == 0 return 0
int leftmost_one(unsigned x) {
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return x - (x >> 1);
}

int rightmost_one(unsigned x) {
    return x & -x;
}

int int_size_is_32() {
    // set msb of 32-bit machine
    unsigned int set_msb = 1u << 31;
    // shift past msb of 32-bit word
    unsigned int beyond_msb = set_msb << 1;
    // set_msb is nonero when word size is >= 32
    // beyond_msb is zero when word size <= 32

    return set_msb && !beyond_msb;
}

// mark least significant n bits set to 1
int lower_one_mask(int n) {
    return (2u << (n - 1)) - 1;
}

// do rotating left shift. assume 0 <= n < w
unsigned rotate_left(unsigned x, int n) {
    unsigned left_part = x << n;
    unsigned right_part = (x >> 1) >> (31 - n);
    return left_part | right_part;
}

// return 1 when x can be represented as n n-bit, twos complement else 0
// assume 1 <= n <= w
int fit_bits(int x, int n) {
    int shift = 32 - n;
    return ((int)((unsigned)x << shift) >> shift) == x;
}

// decleration of a data type where 4 bytes are packed into an unsigned
typedef unsigned packed_t;

// extract byte from word. return as signed integer
int xbyte(packed_t word, int bytenum) {
    unsigned byte = (word >> (bytenum << 3)) & 0xFF;
    // extned to signed 32 int
    return (int)(byte << 24) >> 24;
}

// copy integer into buffer is space is available
void copy_int(int val, void* buf, int maxbytes) {
    if (maxbytes >= 0 && (size_t)maxbytes >= sizeof(val)) {
        memcpy(buf, (void*) &val, sizeof(val));
    }
}

//addition that saturates to TMin or Tmax
int saturating_add(int x, int y) {
    int sum = (int)((unsigned) x + (unsigned) y);
    int overflow_mask = (~(x ^ y) & (x ^ sum)) >> 31;
    int sign_sum = sum >> 31;

    int sat = (sign_sum & INT_MIN) | (~sign_sum & INT_MAX);

    return (overflow_mask & sat) | (~overflow_mask & sum);
}

//determine whether arguments can be subtracted without overflow
int tsub_ok(int x, int y) {
    int sub = (int)((unsigned) x - (unsigned) y);
    int overflow_mask = ((x ^ y) & (x ^ sub)) >> 31;
    // are the signs bits different? and did the sign bit flip in the result?

    return !overflow_mask;
}

int signed_high_prod(int x, int y);

unsigned unsigned_high_prod(unsigned x, unsigned y) {
    int high_prod = signed_high_prod((int)x, (int) y);
    int x_msb = x >> 31;
    int y_msb = y >> 31;
    return high_prod + y * x_msb + x * y_msb;
}

void* calloc(size_t nmemb, size_t size) {
    if (nmemb == 0 || size == 0) return NULL;
    if (size > SIZE_MAX / nmemb) return NULL;
    size_t total = nmemb * size;
    void* memory = malloc(total);
    if (memory == NULL) return NULL;
    memset(memory, 0, total);
    return memory;

}

// 128, 64,32,16,8,4,2,1,

// k = 17
//     (x * 16) + x
//     (x << 4) + x

// k = -7
//     x - (x * 8)
//     x - (x << 3)

// k = 60
//     (x * 64) - (x * 4)
//     (x << 6) - (x << 2)

// k = -112
//     (x * 16) - (x * 128)
//     (x << 4) - (x << 7)


//divide by power of 2. assume 0 <= k < w-1
int divide_power2(int x, int k) {
    int mask = x >> 31;
    int bias = mask & ((1 << k) - 1);
    return (x + bias) >> k;
}

// computes (3 * x) / 4
int mul3div4(int x) {
    int x3 = (x << 1) + x;

    int mask = x3 >> 31;
    int bias = mask & 3;
    return (x3 + bias) >> 2;
}

// computes 3/4 x, rounded towards zero
int threefourths(int x) {
    int q = x >> 2;
    int r = x & 3;
    int q3 = q + q + q;
    int r3 = r + r + r;

    int bias = (x >> 31) & 3;
    return q3 + ((r3 + bias) >> 2);
}

q: 1 ^ (w - k) 0 ^ k
a : ~0 - ((1 << k) - 1)

q : 0 ^ (w - k - j) 1 ^ k 0 ^ j
a : (((1 << (k + j)) - 1) >> j) << j

//create some arbitrary values
int x = random();
int y = random();

//convert to unsigned
unsigned ux = (unsigned) x;
unsigned uy = (unsigned) uy;


// returns 32-bit unsigned representation of float
unsigned f2u(float x);

int float_le(float x, float y) {

    // assume neither are NaN, and +0 == -0

    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    //get the sign bits
    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;


    // if both positive, uy >= ux if uy - ux >= 0
    // we check the sign bit of  uy - ux
    unsigned pos_le = !((uy + ~ux + 1) >> 31);

    //if both negative the bigger one is less, so ux - uy >= 0
    unsigned neg_le = !((ux + ~uy + 1) >> 31);

    //give an expression using only ux, uy, sx and sy
    return
    // x <= y if
    // x and y are both 0
    !((ux << 1) | (uy << 1)) ||
    // x is negative and y is non-negative
    (sx & !sy) ||
    // both are negative
    ((sx & sy & neg_le) ||
    // both are positive
    (!sx & !sy & pos_le));
}












int main() {
    // int i = 12345;
    //
    // float f = 12345.0f;
    //
    // int *p = &i;

    // int arr[] = {1, 2, 3, 4, 5};


    // print_array(arr, 5);

    // reverse(arr, 5);

    // print_array(arr, 5);


    // printf("int 12345: "); show_int(i);
    // printf("float 12345 : "); show_float(f);
    // printf("pointer &i: "); show_pointer(p);

    // const char* s = "abcdef";
    // show_bytes((byte_pointer)s, strlen(s));

    // int x = 0x87654321;
    // printf("%.8x \n", x & 0xff);//
    // printf("%.2x \n", ((~(x & ~(0xff))) & ~(0xff)) | (x & 0xff));
    // printf("%.2x \n", (x & ~(0xff)) | 0xff);

    // printf("%d\n", !0);

    // unsigned int x = ~0;
    // printf("%032b\n", x >> 7);
    // printf("%d\n", x);
    //
    // int x = 0xfedcba98 << 32;
    // printf("%.2x\n", x);

    // short x = 12345;
    // short mx = -x;

    // show_bytes((byte_pointer) &x, sizeof(short));
    // show_bytes((byte_pointer) &mx, sizeof(short));

    // short int v = -12345;
    // unsigned short uv = (unsigned short) v;
    // printf("v = %d, uv = %u\n", v, uv);

    // unsigned u = 4294967295u;
    // int tu = (int) u;
    // printf("u = %u, tu = %d\n", u, tu);

    // int x = -1;
    // unsigned u = 2147483648;

    // printf("x = %u = %d\n", x, x);
    // printf("u = %u = %d\n", u, u);

    // short sx = -12345;
    // unsigned short usx = sx;
    // int x = sx;
    // unsigned ux = usx;

    // printf("sx = %d:\t", sx);
    // show_bytes((byte_pointer) &sx, sizeof(short));
    // printf("usx = %u:\t", usx);
    // show_bytes((byte_pointer) &usx, sizeof(unsigned short));
    // printf("x = %d:\t", x);
    // show_bytes((byte_pointer) &x, sizeof(int));
    // printf("ux = %u", ux);
    // show_bytes((byte_pointer) &ux, sizeof(unsigned));

    // float a[] = {1.0f, 2.0f};
    // printf("sum = %f", sum_elements(a, 0));
    //
    // printf("%.23f\n", 0.1f + 0.2f);

    // printf("%d\n", is_little_endian());
    // printf("%.2x\n", lsb_x_rest_y(0x89ABCDEF, 0x76543210));
    // printf("%08x\n", replace_byte(0x12345678, 0, 0xAB));
    // long l = 1L;
    // show_long(l);
    //
    // printf("%lu", sizeof(int) );
    // printf("%s",typeof(0));

    // double d = 1.0000;
    // show_double(d);

    return 0;
}
