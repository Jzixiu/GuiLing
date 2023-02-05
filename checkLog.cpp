#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    while(1)
    {
        _sleep(100);
        system("copy >nul");
        cout<<system("fc \"C:\\Program Files (x86)\\Hearthstone\\Logs\\Power.log\" \"C:\\Program Files (x86)\\Hearthstone\\Logs\\temp.log\"");
        cout<<system("copy /y \"C:\\Program Files (x86)\\Hearthstone\\Logs\\Power.log\" \"C:\\Program Files (x86)\\Hearthstone\\Logs\\temp.log\"");
    }
    return 0;
}