#include <iostream>
#include <vector>

using namespace std;

class hash_map {
    //두 개의 해시 테이블 사용, 각 테이블 크기를 멤버로 저장한다.
    vector<int> data1;
    vector<int> data2;
    int size;
    
    //두 개의 해시 함수 정의.
    int hash1(int key) const {
        return key%size;
    }
    int hash2(int key) const {
        return (key/size)%size;
    }
    
    //생성자 추가, 해시 테이블을 모두 -1로 초기화한다.(테이블이 비어 있음을 의미)
public:
    hash_map(int n) : size(n) {
        data1=vector<int>(size, -1);
        data2=vector<int>(size, -1);
    }
    
    //룩업 수행 함수.
    vector<int>::iterator lookup(int key) {
        auto hash_value1=hash1(key);
        if(data1[hash_value1]==key) {
            cout<<"1번 테이블에서 "<<key<<"을(를) 찾았습니다."<<endl;
            return data1.begin()+hash_value1;
        }
        
        auto hash_value2=hash2(key);
        if(data2[hash_value2]==key) {
            cout<<"2번 테이블에서 "<<key<<"을(를) 찾았습니다."<<endl;
            return data2.begin()+hash_value2;
        }
        
        return data2.end();
    } //룩업 함수는 양쪽 해시 테이블에서 키를 검색하고, 해당 위치를 나타내는 반복자를 반환한다. 이 반복자는 다음 삭제 함수에서 사용한다.
    //만약 원소를 찾지 못하면 data2의 테이블의 마지막을 가리키는 반복자가 반환된다. 룩업 함수는 O(1)의 시간 복잡도를 가지는 매우 빠른 함수다.
    
    //삭제 함수.
    void erase(int key) {
        //lookup() 함수가 반환한 값을 조사하여 실제 삭제 작업을 수행하거나 단순히 문자열만 출력한다.
        auto position=lookup(key);
        if(position!=data2.end()) {
            *position=-1;
            cout<<key<<"에 해당하는 원소를 삭제했습니다."<<endl;
        }
        else {
            cout<<key<<"키를 찾지 못했습니다."<<endl;
        }
    }
    
    //재귀적 동작 삽입 함수. 최대 재귀 호출 횟수는 해시 테이블의 크기와 같게 설정.
    void insert(int key) {
        insert_impl(key, 0, 1);
    }
    
    //key는 키, cnt는 재귀 호출 횟수, table은 키를 삽입할 테이블 번호.
    void insert_impl(int key, int cnt, int table) {
        if(cnt>=size) {
            cout<<key<<" 삽입 시 순환 발생. 재해싱이 필요합니다."<<endl;
            return;
        }
        
        if(table==1) {
            int hash=hash1(key);
            if(data1[hash]==-1) {
                cout<<table<<"번 테이블에 "<<key<<" 삽입"<<endl;
                data1[hash]=key;
            }
            else {
                int old=data1[hash];
                data1[hash]=key;
            }
            else {
                int old=data1[hash];
                data1[hash]=key;
                cout<<table<<"번 테이블에 "<<key<<" 삽입 : 기존의 "<<old<<" 이동 -> ";
                insert_impl(old, cnt+1, 2);
            }
        }
        else {
            int hash=hash2(key);
            if(data2[hash]==-1) {
                cout<<table<<"번 테이블에 "<<key<<" 삽입"<<endl;
                data2[hash]=key;
            }
            else {
                int old=data2[hash];
                data2[hash]=key;
                cout<<table<<"번 테이블에 "<<key<<" 삽입 : 기존의 "<<old<<" 이동 -> ";
                insert_impl(old, cnt+1, 1);
            }
        }
    }
    
    //모든 데이터를 출력하는 print() 함수.
    void print() {
        cout<<"Index : ";
        for(int i=0; i<size; i++)
            cout<<i<<'\t';
        cout<<endl;
        
        cout<<"Data1 : ";
        for(auto i:data1)
            cout<<i<<'\t';
        cout<<endl;
        
        cout<<"Data2 : ";
        for(auto i:data2)
            cout<<i<<'\t';
        cout<<endl;
    }
};

int main() {
    hash_map map(7);
    map.print();
    cout<<endl;
    
    map.insert(10);
    map.insert(20);
    map.insert(30);
    cout<<endl;
    
    map.insert(104);
    map.insert(2);
    map.insert(70);
    map.insert(9);
    map.insert(90);
    map.insert(2);
    map.insert(7);
    cout<<endl;
    
    map.print();
    cout<<endl;
    
    //순환 발생.
    map.insert(14);
}
