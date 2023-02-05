#include <iostream>
#include <map>

int main()
{
    std::map<char, int> mymap;

    // （1）插入单个值
    mymap.insert(std::pair<char, int>('a', 100));
    mymap.insert(std::pair<char, int>('z', 200));
    mymap.insert(std::make_pair('f', 300));	// pair方式和make_pair功能是一样的

    // 返回插入位置以及是否插入成功
    std::pair<std::map<char, int>::iterator, bool> ret;
    ret = mymap.insert(std::pair<char, int>('z', 500));
    if (ret.second == false) {
        std::cout << "element 'z' already existed";
        std::cout << " with a value of " << ret.first->second << ' ';
    }

    // （2）指定位置插入
    std::map<char, int>::iterator it = mymap.begin();
    mymap.insert(it, std::pair<char, int>('b', 300));  //效率更高
    mymap.insert(it, std::pair<char, int>('c', 400));  //效率非最高

    // （3）范围多值插入
    std::map<char, int> anothermap;
    anothermap.insert(mymap.begin(), mymap.find('c'));

    // （4）列表形式插入
    anothermap.insert({ { 'd', 100 }, {'e', 200} });

    return 0;
}