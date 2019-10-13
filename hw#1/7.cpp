#include <iostream>
#include <vector>

using namespace std;

bool ans(vector<char> str){
    int check = 0;
    for(int i = 0; i < str.size(); i++){
        if(str[i] == ')') check--;
        if(str[i] == '(') check++;
    }
    return check == 0;
}

int main()
{
    vector<char> vec;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        char push;
        cin >> push;
        vec.push_back(push);
    }
    cout << ans(vec);
    return 0;
}
