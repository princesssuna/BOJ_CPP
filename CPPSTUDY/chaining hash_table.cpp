#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

using uint=unsigned int; //unsigned int 타입 이름 대신 uint로 짧게 사용.

//hash_map class add.
class hash_map {
    vector<list<int>> data;
    
    //hash_map class의 생성자 추가. 생성자는 해시 맵 또는 데이터 크기를 인자로 받는다.
public:
    hash_map(size_t n) {
        data.resize(n);
    }
    
    //삽입 함수. value 값을 항상 해시 맵에 추가한다.
    void insert(uint value) {
        int n=data.size();
        data[value%n].push_back(value);
        cout<<value<<"을(를) 삽입했습니다."<<endl;
    }
    
    //특정 원소가 해시 맵에 있는지 확인하는 룩업 함수.
    bool find(uint value) {
        int n=data.size();
        auto& entries=data[value%n];
        return find(entries.begin(), entries.end(), value)!=entries.end();
    }
    
}
