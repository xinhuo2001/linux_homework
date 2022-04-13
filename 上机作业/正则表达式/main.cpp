#include<iostream>
using namespace std;
#include<vector>
#include<math.h>
#include<algorithm>
#include<fstream>
#include<map>

ifstream in("in.txt");

class Solution
{
public:
    map<int,int> tmap; //时间
    map<int,vector<int> > relay_map; //依赖
public:
    Solution() {
        int vedio_num;
        int vedio_time;
        int relay_num;
        int relay_index;
        in >> vedio_num;
        for(int i = 0; i < vedio_num; i++) {
            in >> vedio_time >> relay_num;
            auto mi = make_pair(i,vedio_time);
            tmap.insert(mi);
            for(int k = 0; k < relay_num; k++) {
                in >> relay_index;
            }
        }
    }
    int getMinDistance(const vector<int>& arr) {
        
    }
};


int main() {
    int num;
    vector<int> arr;
    in >> num;
    for(int i = 0; i < num; i++) {
        int aix;
        in >> aix;
        arr.push_back(aix);
    }
    int ret = Solution().getMinDistance(arr);
    cout << ret << endl;
    return 0;

    // int num;
    // vector<int> arr;
    // cin >> num;
    // for(int i = 0; i < num; i++) {
    //     int aix;
    //     cin >> aix;
    //     arr.push_back(aix);
    // }
    // int ret = Solution().getMinDistance2(arr);
    // cout << ret << endl;
    // return 0;
}