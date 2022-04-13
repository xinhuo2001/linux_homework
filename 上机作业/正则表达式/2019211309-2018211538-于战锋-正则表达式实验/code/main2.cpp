#include<iostream>
using namespace std;
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>

class Solution
{
public:
    int f(const vector<char>& arr) {
        // a cbcca
        int len = arr.size();
        int count[5];
        for(int i = 0; i < 5; i++) {
            count[i] = 0;
        }
        for(int i = 0; i < len; i++) {
            if(arr[i] >= 'a' && arr[i] <= 'c') {
                count[arr[i]-'a']++;
            }
        }
        // for(int i = 0; i < 3; i++) {
        //     printf("%c:%d\n",i+'a',count[i]);
        // }
        int ret = min(count[0]-1,count[1]);
        ret = min(ret,count[2]/3);
        return ret;
    }
};


int main() {
    string s;
    cin >> s;
    vector<char> arr;
    for(int i = 0; i < s.length(); i++) {
        arr.push_back(s[i]);
    }
    int ret = Solution().f(arr);
    cout << ret << endl;
    return 0;
}