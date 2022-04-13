#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

int main() {
    vector<int> a = {5,7,4};
    for(int i=0; i<a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    auto it = find(a.begin(),a.end(),5);
    a.erase(it);
    for(int i=0; i<a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}