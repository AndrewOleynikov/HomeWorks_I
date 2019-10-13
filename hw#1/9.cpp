#include <iostream>

using namespace std;

bool isPrime(int a){
    for(int i = 2; i < a; i++) if(!(a % i)) return false;
    return (true);
}

int main()
{
    int a;
    cin >> a;
    for(int i = 1; i <= a; i++) if(isPrime(i)) cout << i << ' ';
    return 0;
}
