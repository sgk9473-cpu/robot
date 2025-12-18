#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
string print_robot(int offset)
{
    string robot;
    // 所有行拼接成一个字符串（用\n换行，而非多次cout）
    robot += string(offset, ' ') + "   \\   /  \n";
    robot += string(offset, ' ') + "  [=====] \n";
    robot += string(offset, ' ') + "  |  o  | \n";
    robot += string(offset, ' ') + "  [=====] \n";
    robot += string(offset, ' ') + " =========\n";
    robot += string(offset, ' ') + "\\|  ---  |/\n";
    robot += string(offset, ' ') + " =========\n";
    robot += string(offset, ' ') + "  ^^^^^^^ \n";
    robot += string(offset, ' ') + "   |   |  \n";
    return robot;
}
int main() 
{
    
    // 控制移动范围：0~20个空格（从左到右再到左）
    for (int offset = 0; offset <= 20; offset++) {
        system("cls"); // 清屏（Windows）
        cout<<print_robot(offset); // 打印当前位置的机器人
        Sleep(50); // 延时50ms（控制移动速度）
    }
    for (int offset = 20; offset >= 0; offset--) {
        system("cls");
        cout<<print_robot(offset);
        Sleep(50);
    }
    return 0;
}