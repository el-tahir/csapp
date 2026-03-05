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

    return (x & 0x000000FF) | (y & 0xFFFFFF00);
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
    printf("%.2x\n", lsb_x_rest_y(0x89ABCDEF, 0x76543210));

    // long l = 1L;
    // show_long(l);

    // double d = 1.0000;
    // show_double(d);

    return 0;
}
