#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> vec;
    for(int i = 0; i < n; i ++) {
        int x;
        cin >> x;
        vec.push_back(x);
    }
    int ans = 0;
    for(auto it = vec.begin(); it != vec.end(); it++) if(!*it) ans++;
    cout << ans;
    return 0;
}
