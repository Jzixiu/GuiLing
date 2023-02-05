#include <iostream>
#include <vector>
using namespace std;

class minion
{
    public:
    int hp;
    int id;
};

int main()
{
    vector<minion> vec;
    minion temp;
    temp.hp=0;
    temp.id=0;
    vec.push_back(temp);
    int i=0;
    vec.erase(vec.begin()+i);
    return 0;
}