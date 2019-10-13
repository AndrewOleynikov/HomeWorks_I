#include <iostream>
#include <string>

using namespace std;

int main()
{
    int count = 0;
    string big, small;
    cin >> big >> small;
    for(int i = 0; i < big.size(); i++){
        if(big[i] == small[0] && big.size() - 1 - i >= small.size() - 1){
            int concided = 0;
            int j = 0, ii = i;
            while(j < small.size() && small[j] == big[ii]){
                concided++;
                j++;
                ii++;
            }
            if(concided == small.size()) count++;
        }
    }

    cout << count;

    return 0;
}
