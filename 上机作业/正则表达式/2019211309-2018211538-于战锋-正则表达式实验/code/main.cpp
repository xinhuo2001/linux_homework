#include<iostream>
using namespace std;
#include<vector>
#include<math.h>
#include<algorithm>
#include<fstream>

class Solution
{
public:
    int getMinDistance(const vector<int>& arr) {
        if(arr.size() <= 0) {
            return 0;
        }
        int len = arr.size();
        cout << "len:" << len << endl;
        for(int i=0; i<len; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        int ret = 0;
        for(int i = 1; i <= len; i = i+2) {
            cout << "区间:" << i << endl;
            //区间长度 i
            vector<int> v;
            //填充第一个v
            for(int k = 0; k < i; k++) {
                v.push_back(arr[k]);
            }
            //排序v
            sort(v.begin(),v.end());
            int mid = v.size()/2;
            ret += v[mid];
            int reNum = arr[0];
            cout << "reNum" << reNum << endl;
            cout << "进入遍历 size:" << v.size() << endl;
            cout << "v[0]" << v[0] << endl;
            for(int k = 1; k+i-1 < len; k++) {
                //k ~ k+i 为求中位数区间
                cout << "reNum:" << reNum << endl;
                auto it = find(v.begin(),v.end(),reNum);
                if(it == v.end()) {
                    cout << "找不到" << endl;
                    exit(-1);
                }
                cout << "擦除" << (*it) << " 加入" << arr[k+i-1] << endl;
                v.erase(it);
                reNum = arr[k+i-1];
                //插入新数据
                v.push_back(arr[k+i-1]);
                sort(v.begin(),v.end());
                mid = v.size()/2;
                ret += v[mid];
            }
            cout << "-----------ret:" << ret << endl;
        }
        return ret;
    }
    int getMinDistance2(const vector<int>& arr) {
        if(arr.size() <= 0) {
            return 0;
        }
        int len = arr.size();
        int ret = 0;
        for(int i = 1; i <= len; i = i+2) {
            //区间长度 i
            vector<int> v;
            //填充第一个v
            for(int k = 0; k < i; k++) {
                v.push_back(arr[k]);
            }
            //排序v
            sort(v.begin(),v.end());
            int mid = v.size()/2;
            ret += v[mid];
            int reNum = arr[0];
            for(int k = 1; k+i-1 < len; k++) {
                //k ~ k+i 为求中位数区间
                auto it = find(v.begin(),v.end(),reNum);
                v.erase(it);
                reNum = arr[k+i-1];
                //插入新数据
                v.push_back(arr[k+i-1]);
                sort(v.begin(),v.end());
                mid = v.size()/2;
                ret += v[mid];
            }
        }
        return ret;
    }
};

// ifstream in("in.txt");
int main() {
    // int num;
    // vector<int> arr;
    // in >> num;
    // for(int i = 0; i < num; i++) {
    //     int aix;
    //     in >> aix;
    //     arr.push_back(aix);
    // }
    // int ret = Solution().getMinDistance2(arr);
    // cout << ret << endl;
    // return 0;

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