#include <iostream>

using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    int k = 0;
    if(b){
        while(a - b > 0) {
            a -= b;
            k++;
        }
        cout << k;
    } else cout << "divided by 0";

    return 0;
}
