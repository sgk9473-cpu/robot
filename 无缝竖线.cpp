#include <iostream>
#include <locale>
#include <windows.h> // Windows系统API
using namespace std;

int main() {
    setlocale(LC_ALL, "");
    

    
    // 输出全屏无缝竖线
    for (int i = 0; i < 7; ++i) {
        wcout << L'│' << '\n'; // 用\n替代endl，效率更高
    }
    
    return 0;
}