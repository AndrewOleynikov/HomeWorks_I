#include <stdio.h>
#include <limits.h>

int bitAnd(int x, int y){
  return ~(~x | ~y);
}

int bitXor(int x, int y){
  return ~(~(x & ~y) & ~(~x & y));
}

int thirdBits(){
  int a = 0b100100;
  return a << 24 | a << 18 | a << 12 | a << 6 | a;
}

int sign(int x){
  return x >> 31 | !!x;
}

int fitsBits(int x, int n){
  return !(x^((x << (32 + ~n + 1)) >> (32 + ~n + 1)));
}

int getByte(int x, int n){
  int mask = 0x000000ff;
  return mask & (x >> (n << 3));
}

int logicalShift(int x, int n){
  return (x >> n) & (~(((1 << 31) >> n) << 1));
}

int addOK(int x, int y){
  int sum = x + y;
  return !((((x ^ sum) & (1 << 31)) & (y ^ sum & (1 << 31))) >> 31);
}

int bang(int x){
  return ((x | (~x + 1)) >> 31) + 1;
}

int isPower2(int x){
  return !!x & !(1 & (x >> 31)) & !(x & (x + (~1 + 1)));
}

int conditional(int x, int y, int z){
  return z ^ ((y ^ z) & ((!x) + ~0));
}

/* int main(int argc, char const *argv[]) {
   printf("%d\n", isPower2( 0));

   return 0;
 }*/
