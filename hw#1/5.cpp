#include <iostream>
#include <vector>

using namespace std;

vector<int> x;

void reverseVec(int a, int b){
    while(a < b){
        swap(x[a], x[b]);
        a++;
        b--;
    }
}

int main()
{
    int n, m;
    cin >> m >> n;
    for(int i = 0; i < n + m; i++){
        int push;
        cin >> push;
        x.push_back(push);
    }
    if(m > n) swap(m, n);
    for(int i = 0; i < m; i++) swap(x[i], x[x.size()-1 - i]);
    // reverseVec(1, 3);
    //for(int i = 0; i < n + m; i++) cout <<  endl << x[i];
    //for(int i = 0; i < n + m; i++) cout <<  endl << x[i]; cout << endl;
    reverseVec(0, m - 1); cout << endl;
    reverseVec(m , x.size() - m -1);
    reverseVec(x.size() - m, x.size() - 1);
    for(int i = 0; i < n + m; i++) cout <<  endl << x[i];
    return 0;
}
