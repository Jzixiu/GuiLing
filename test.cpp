#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int a[4]={1,2,2,2};
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<i;j++)
        {
            cout<<a[i]<<" "<<a[j]<<endl;
        }
    }
    
    return 0;
}