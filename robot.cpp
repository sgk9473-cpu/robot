#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;

// 初始通关状态
bool levelpassed[4] = {false, false, false, false};

// 建立保存进度的文件
const string progressfile = "robot_progress.txt";

// 从文件加载通关进度
void loadprogress()
{
    ifstream fin(progressfile);
    if (!fin.is_open())
    {
        cerr << "First-time game play, initializing progress file..." << endl;
        return;
    }
    int status;
    for (int i = 0; i < 4; i++)
    {
        fin >> status;
        if (status == 1)
        {
            levelpassed[i] = true;
        }
        else
        {
            levelpassed[i] = false;
        }
    }
    fin.close();
    cout << "Progress loaded successfully!" << endl;
}

// 保存通关进度到文件
void saveprogress()
{
    ofstream fout(progressfile);
    if (!fout.is_open())
    {
        cerr << "Error: Failed to save progress!" << endl;
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        if (levelpassed[i])
        {
            fout << 1 << " ";
        }
        else
        {
            fout << 0 << " ";
        }
    }
    fout.close();
    cout << "Progress saved successfully!" << endl;
}
// 光标定位
void setCursorPos(int x, int y)
{
    // 获取控制台输出句柄
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // COORD结构体存储坐标
    COORD pos;
    pos.X = x; // 列坐标（横向位置）
    pos.Y = y; // 行坐标（纵向位置）
    // 设置光标位置
    SetConsoleCursorPosition(hConsole, pos);
}
// 显示关卡选择界面
void showlevelselect()
{
    // 清屏
    system("cls");
    cout << "===========" << " Level Select " << "===========" << endl;
    cout << endl;
    cout << "1. Level 1:  " << (levelpassed[0] ? "(Passed)" : "(Not Passed)") << endl;
    cout << "2. Level 2:  " << (levelpassed[1] ? "(Passed)" : "(Not Passed)") << endl;
    cout << "3. Level 3:  " << (levelpassed[2] ? "(Passed)" : "(Not Passed)") << endl;
    cout << "4. Level 4:  " << (levelpassed[3] ? "(Passed)" : "(Not Passed)") << endl;
    cout << endl;
    cout << "====================================" << endl;
    cout << endl;
    cout << "Enter your challenge choice (1-4) (0 to exit): ";
}

// 模拟玩关卡过程
void mimicplay(int level_num)
{
    // 清屏
    system("cls");
    cout << "===========" << " Start to challenge Level " << level_num << " ===========" << endl;
    cout << "Level " << level_num << " is playing..." << endl;
    cout << "press any key to continue...(just mimic the progress)" << endl;
    // 随便输模拟玩游戏
    string input;
    cin >> input;
    // 通关
    levelpassed[level_num - 1] = true;
    cout << "Congratualations! You have passed Level " << level_num << " !" << endl;
    cout << "Press return key to return to Level Select..." << endl;
    // 等待回车
    cin.ignore(); // 清除输入缓冲区中的换行符
    cin.get();    // 等待用户按下回车
}

// outbox的合法性
bool is_outbox(bool is_hold_block)
{
    if (!is_hold_block)
        return false;
    return true;
}
// add的合法性
bool is_add(bool is_hold_block, int X, vector<bool> is_valid)
{
    if (!is_hold_block)
        return false;
    if (X > is_valid.size() - 1 || X < 0)
        return false;
    if (!is_valid[X])
        return false;
    return true;
}
// sub的合法性
bool is_sub(bool is_hold_block, int X, vector<bool> is_valid)
{
    if (!is_hold_block)
        return false;
    if (X > is_valid.size() - 1 || X < 0)
        return false;
    if (!is_valid[X])
        return false;
    return true;
}
// copyto的合法性
bool is_copyto(bool is_hold_block, int X, vector<bool> is_valid)
{
    if (!is_hold_block)
        return false;
    if (X > is_valid.size() - 1 || X < 0)
        return false;
    return true;
}
// copyfrom的合法性
bool is_copyfrom(int X, vector<bool> is_valid)
{
    if (X > is_valid.size() - 1 || X < 0)
        return false;
    if (!is_valid[X])
        return false;
    return true;
}
// jump的合法性
bool is_jump(int X, int i, int instruction_num)
{
    if (X <= 0 || X > instruction_num)
        return false;
    return true;
}
// jumpifzero的合法性
bool is_jumpifzero(int X, int i, int instruction_num, bool is_hold_block)
{
    if (!is_hold_block)
        return false;
    if (X <= 0 || X > instruction_num)
        return false;
    return true;
}
// inbox操作
void inbox(bool &is_hold_block, vector<int> &entry_list, int &current_hold_num)
{
    if (entry_list.size() >= 1)
    {
        is_hold_block = true;
        current_hold_num = entry_list[0];
        entry_list.erase(entry_list.begin());
    }
}
// outbox操作
void outbox(bool &is_hold_block, vector<int> &out_list, int &current_hold_num)
{
    out_list.push_back(current_hold_num);
    is_hold_block = false;
}
// add操作
void add(int X, vector<int> &valid_area, int &current_hold_num)
{
    current_hold_num += valid_area[X];
}
// sub操作
void sub(int X, vector<int> &valid_area, int &current_hold_num)
{
    current_hold_num -= valid_area[X];
}
// copyto操作
void copyto(int X, vector<int> &valid_area, int &current_hold_num, vector<bool> &is_valid)
{
    valid_area[X] = current_hold_num;
    is_valid[X] = true;
}
// copyfrom操作
void copyfrom(int X, vector<int> &valid_area, int &current_hold_num, bool &is_hold_block)
{
    current_hold_num = valid_area[X];
    is_hold_block = true;
}
// jump操作
void jump(int X, int &i)
{
    i = X - 2;
}
// jumpifzero操作
void jumpifzero(int X, int &i, int &current_hold_num)
{
    if (current_hold_num == 0)
    {
        i = X - 2;
    }
}
// 打印积木
void print_block(int x, int y, int num)
{
    if (num >= 0 && num < 10)
    {
        setCursorPos(x, y);
        cout << "+---+";
        setCursorPos(x, y + 1);

        cout << "| " << num << " |";
        setCursorPos(x, y + 2);
        cout << "+---+";
    }
    else if ((num >= 10 && num < 100) || (num < 0 && num > -10))
    {
        setCursorPos(x, y);
        cout << "+---+";
        setCursorPos(x, y + 1);
        cout << "| " << num << "|";
        setCursorPos(x, y + 2);
        cout << "+---+";
    }
    else if ((num >= 100 && num < 1000) || (num <= -10 && num > -100))
    {
        setCursorPos(x, y);
        cout << "+---+";
        setCursorPos(x, y + 1);
        cout << "|" << num << "|";
        setCursorPos(x, y + 2);
        cout << "+---+";
    }
}
// 打印空白积木
void print_blank_block(int x, int y)
{
    setCursorPos(x, y);
    cout << "+---+";
    setCursorPos(x, y + 1);
    cout << "| X |";
    setCursorPos(x, y + 2);
    cout << "+---+";
}
// 打印机器人
void print_robot(int offset)
{

    setCursorPos(11, 13);
    cout << string(offset, ' ') + "   \\   /  \n";
    setCursorPos(11, 14);
    cout << string(offset, ' ') + "  [=====] \n";
    setCursorPos(11, 15);
    cout << string(offset, ' ') + "  |  o  | \n";
    setCursorPos(11, 16);
    cout << string(offset, ' ') + "  [=====] \n";
    setCursorPos(11, 17);
    cout << string(offset, ' ') + " =========\n";
    setCursorPos(11, 18);
    cout << string(offset, ' ') + "\\|  ---  |/\n";
    setCursorPos(11, 19);
    cout << string(offset, ' ') + " =========\n";
    setCursorPos(11, 20);
    cout << string(offset, ' ') + "  ^^^^^^^ \n";
    setCursorPos(11, 21);
    cout << string(offset, ' ') + "   |   |  \n";
}

// 打印拿着的积木
void print_hold_block(int offset, int num)
{
    if(num>=0&&num<10)
    {
    setCursorPos(14, 10);
    cout << string(offset, ' ') + "+---+\n";
    setCursorPos(14, 11);
    cout << string(offset, ' ') + "| " << num << " |\n";
    setCursorPos(14, 12);
    cout << string(offset, ' ') + "+---+\n";}
    else if((num>=10&&num<100)||(num<0&&num>-10))
    {
        setCursorPos(14, 10);
        cout << string(offset, ' ') + "+---+\n";
        setCursorPos(14, 11);
        cout << string(offset, ' ') + "| " << num << "|";
        setCursorPos(14, 12);
        cout << string(offset, ' ') + "+---+\n";
    }
    else if((num>=100&&num<1000)||(num<= -10&&num>-100))
    {
        setCursorPos(14, 10);
        cout << string(offset, ' ') + "+---+\n";
        setCursorPos(14, 11);
        cout << string(offset, ' ') + "|" << num << "|";
        setCursorPos(14, 12);
        cout << string(offset, ' ') + "+---+\n";
    }
}

// 打印关卡1初始信息
void print_level_1()
{
    system("cls"); // 清屏
    cout << "===========" << " Start to challenge Level 1 " << "===========" << endl;
    cout << "Level 1 is playing..." << endl;
    cout << "Level information:" << endl;
    cout << "Let the robot take each block from the input sequence and place it in the output sequence." << endl;
    cout << "a.Input and output of the level:" << endl;
    cout << "  i.Input: 1 2" << endl;
    cout << "  ii.Output: 1 2" << endl;
    cout << "b.Number of available open spaces: 0" << endl;
    cout << "c.Available instruction set: inbox outbox" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    setCursorPos(0, 11);
    cout << "IN";
    for (int i = 0; i <= 3; i += 3)
    {
        print_block(4, i + 10, i / 3 + 1);
    }
    for (int i = 0; i <= 3; i += 3)
    {
        print_blank_block(50, i + 10);
    }
    setCursorPos(57, 11);
    cout << "OUT";
    for (int i = 0; i < 18; ++i)
    {
        setlocale(LC_ALL, "");
        setCursorPos(62, i + 10);
        wcout << L'│' << '\n';
    }
    setCursorPos(63, 10);
    cout << " ======= CODE =======";
    print_robot(0);
}
// 关卡1
void level_1(int m, vector<string> instructions, vector<int> instruction_X)
{
    print_level_1();
    bool is_hold_block = false;      // 机器人手上是否有积木
    bool is_pass = false;            // 是否通关
    bool is_error = false;           // 是否发生错误
    vector<int> entry_list = {1, 2}; // 输入序列
    vector<int> out_list = {1, 2};   // 目标输出序列
    vector<int> user_out;            // 经过输入指令输出的序列
    user_out.clear();
    int current_hold_num = 0;   // 机器人手上的积木
    for (int i = 0; i < m; i++) // 打印code
    {
        setCursorPos(67, 11 + i);
        cout << i + 1 << " " << instructions[i];
    }
    for (int i = 0; i < m; i++)
    {
        for (int i = 0; i < m; i++)
        {
            setCursorPos(65, 11 + i);
            cout << " ";
        }
        setCursorPos(65, 11 + i);
        cout << "> "; // 更新>的位置
        Sleep(1000);  // 可视化
        if (instructions[i] == "inbox")
        {
            if(entry_list.empty())
            {
                break;
            }
            inbox(is_hold_block, entry_list, current_hold_num);
            for (int j = 0; j < entry_list.size(); j++)
            {
                print_block(4, j * 3 + 10, entry_list[j]);
            }
            for (int j = entry_list.size(); j < 2; j++)
            {
                print_blank_block(4, j * 3 + 10);
            }
            print_hold_block(0, current_hold_num); // 更新输入序列
            Sleep(1000);                           // 可视化
        }
        else if (instructions[i] == "outbox")
        {
            if (!is_outbox(is_hold_block))
            {
                is_error = true;
                setCursorPos(0, 23);
                cout << "                                            "; // 清除
                setCursorPos(0, 23);
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            outbox(is_hold_block, user_out, current_hold_num);
            for (int j = 0; j <= 25; j++) // 向右移动
            {
                for (int m = 10; m <= 21; m++)
                {
                    for (int n = 14; n <= 49; n++)
                    {
                        setCursorPos(n, m);
                        cout << " ";
                    }
                }
                print_robot(j);
                print_hold_block(j, current_hold_num);
                Sleep(10);
            }
            for (int j = 0; j < user_out.size(); j++)
            {
                print_block(50, j * 3 + 10, user_out[user_out.size() - 1 - j]);
            }
            for (int j = user_out.size(); j < 2; j++)
            {
                print_blank_block(50, j * 3 + 10);
            } // 更新输出序列
            for (int j = 25; j >= 0; j--)
            {
                for (int m = 10; m <= 21; m++)
                {
                    for (int n = 14; n <= 49; n++)
                    {
                        setCursorPos(n, m);
                        cout << " ";
                    }
                }
                print_robot(j);
                Sleep(10);
            } // 向左移动
        }
        else // 指令不是inbox或outbox，发生错误
        {
            setCursorPos(0, 23);
            cout << "                                            "; // 清除
            setCursorPos(0, 23);
            cout << "Error on instruction " << i + 1 << endl;
            is_error = true;
            break;
        }
    }
    setCursorPos(0, 24); // 调整光标
    // 检查是否通关
    if (user_out == out_list)
    {
        is_pass = true;
    }
    if (!is_pass && !is_error)
    {
        cout << "You have failed to pass Level 1 !" << endl;
    }
    if (is_pass && !is_error)
    {
        cout << "Congratualations! You have passed Level 1 !" << endl;
        levelpassed[0] = true;
    }
    cout << "Press return key to return to Level Select..." << endl; // 等待回车
    cin.ignore();                                                    // 清除输入缓冲区中的换行符
    cin.get();                                                       // 等待用户按下回车
}

// 检查选关卡的合法性
bool checklevel(int level_choice)
{
    // 0退出
    if (level_choice == 0)
    {
        return true;
    }
    // 1-4选关卡
    if (level_choice < 1 || level_choice > 4)
    {
        cout << "Invalid level choice! Please enter a number between 1 and 4." << endl;
        return false;
    }
    // 第1关随便玩
    if (level_choice == 1)
    {
        return true;
    }
    // 检查前面关卡的通过情况
    if (!levelpassed[level_choice - 2])
    {
        cout << "You must pass Level " << level_choice - 1 << " before you can play Level " << level_choice << " !" << endl;
        return false;
    }
    // 所有都满足
    return true;
}
// 打印第2关的界面
void print_level_2(vector<int> entry_list)
{
    system("cls"); // 清屏
    cout << "===========" << " Start to challenge Level 2 " << "===========" << endl;
    cout << "Level 2 is playing..." << endl;
    cout << "Level information:" << endl;
    cout << "For each pair in the input sequence, subtract the second from the first, then the first from the second, and append both results to the output sequence." << endl;
    cout << "a.Input and output of the level:" << endl;
    cout << "  i.Input: 3 9 5 1 -2 -2 9 -9" << endl;
    cout << "  ii.Output: -6 6 4 -4 0 0 18 -18" << endl;
    cout << "b.Number of available open spaces: 3" << endl;
    cout << "c.Available instruction set: inbox outbox copyfrom copyto add sub jump jumpifzero" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    setCursorPos(0, 11);
    cout << "IN";
    for (int i = 0; i <= entry_list.size() - 1; i++)
    {
        print_block(4, i * 3 + 10, entry_list[i]);
    }
    for (int i = 0; i <= entry_list.size() - 1; i++)
    {
        print_blank_block(50, i * 3 + 10);
    }
    setCursorPos(57, 11);
    cout << "OUT";
    for (int i = 0; i < 24; ++i)
    {
        setlocale(LC_ALL, "");
        setCursorPos(62, i + 10);
        wcout << L'│' << '\n';
    }
    setCursorPos(63, 10);
    cout << " ======= CODE =======";
    print_robot(0);
    for (int j = 17; j <= 37; j += 10)
    {
        print_blank_block(j, 23);
    }
    for (int j = 19; j <= 39; j += 10)
    {
        setCursorPos(j, 26);
        cout << j / 10 - 1;
    }
}
void level_2(int m, vector<string> instructions, vector<int> instruction_X, vector<int> entry_list, vector<int> out_list)
{
    vector<int> valid_area(3);       // 空地
    vector<bool> is_valid(3, false); // 空地是否被占用
    vector<int> user_out;            // 经过输入指令输出的序列
    bool is_hold_block = false;      // 机器人手上是否有积木
    int current_hold_num = 0;        // 机器人手上的积木号
    bool is_pass = false;            // 是否通关
    bool is_error = false;           // 是否发生错误
    for (int i = 0; i < m; i++)      // 打印code
    {
        setCursorPos(67, 11 + i);
        cout << i + 1 << " " << instructions[i];
        if(instructions[i]=="jump"||instructions[i]=="jumpifzero"||instructions[i]=="add"||instructions[i]=="sub"||instructions[i]=="copyfrom"||instructions[i]=="copyto")
        {
            cout << " " << instruction_X[i];
        }
    }
    // 遍历
    for (int i = 0; i < m; i++)
    {
        for (int i = 0; i < m; i++)
        {
            setCursorPos(65, 11 + i);
            cout << " ";
        }
        setCursorPos(65, 11 + i);
        cout << "> "; // 更新>的位置
        Sleep(1000);  // 可视化
        if (instructions[i] == "inbox")
        {
            if(entry_list.empty())
            {
                break;
            }
            inbox(is_hold_block, entry_list, current_hold_num);
            for (int j = 0; j < entry_list.size(); j++)
            {
                print_block(4, j * 3 + 10, entry_list[j]);
            }
            for (int j = entry_list.size(); j < 8; j++)
            {
                print_blank_block(4, j * 3 + 10);
            }
            print_hold_block(0, current_hold_num); // 更新输入序列
            Sleep(1000);                           // 可视化
        }
        else if (instructions[i] == "outbox")
        {
            if (!is_outbox(is_hold_block))
            {
                is_error = true;
                setCursorPos(0, 34);
                cout << "                                            "; // 清除
                setCursorPos(0, 34);
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            outbox(is_hold_block, user_out, current_hold_num);
            for (int j = 0; j <= 25; j++) // 向右移动
            {
                for (int m = 10; m <= 21; m++)
                {
                    for (int n = 14; n <= 49; n++)
                    {
                        setCursorPos(n, m);
                        cout << " ";
                    }
                }
                print_robot(j);
                print_hold_block(j, current_hold_num);
                Sleep(10);
            }
            for (int j = 0; j < user_out.size(); j++)
            {
                print_block(50, j * 3 + 10, user_out[user_out.size() - 1 - j]);
            }
            for (int j = user_out.size(); j < 8; j++)
            {
                print_blank_block(50, j * 3 + 10);
            } // 更新输出序列
            for (int j = 25; j >= 0; j--)
            {
                for (int m = 10; m <= 21; m++)
                {
                    for (int n = 14; n <= 49; n++)
                    {
                        setCursorPos(n, m);
                        cout << " ";
                    }
                }
                print_robot(j);
                Sleep(10);
            } // 向左移动
        }
        else if (instructions[i] == "add") // add操作
        {
            if (!is_add(is_hold_block, instruction_X[i], is_valid))
            {
                is_error = true;
                setCursorPos(0, 34);
                cout << "                                            "; // 清除
                setCursorPos(0, 34);
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            add(instruction_X[i], valid_area, current_hold_num);
            print_hold_block(0, current_hold_num + valid_area[instruction_X[i]]);
            Sleep(1000); // 可视化
        }
        else if (instructions[i] == "sub") // sub操作
        {
            if (!is_sub(is_hold_block, instruction_X[i], is_valid))
            {
                is_error = true;
                setCursorPos(0, 34);
                cout << "                                            "; // 清除
                setCursorPos(0, 34);
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            sub(instruction_X[i], valid_area, current_hold_num);
            print_hold_block(0, current_hold_num - valid_area[instruction_X[i]]);
            Sleep(1000); // 可视化
        }
        else if (instructions[i] == "copyto") // copyto操作
        {
            if (!is_copyto(is_hold_block, instruction_X[i], is_valid))
            {
                is_error = true;
                setCursorPos(0, 34);
                cout << "                                            "; // 清除
                setCursorPos(0, 34);
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            copyto(instruction_X[i], valid_area, current_hold_num, is_valid);
            print_block(instruction_X[i] * 10 + 17, 23, current_hold_num);
            Sleep(1000); // 可视化
        }
        else if (instructions[i] == "copyfrom") // copyfrom操作
        {
            if (!is_copyfrom(instruction_X[i], is_valid))
            {
                is_error = true;
                setCursorPos(0, 34);
                cout << "                                            "; // 清除
                setCursorPos(0, 34);
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            copyfrom(instruction_X[i], valid_area, current_hold_num, is_hold_block);
            print_hold_block(0, valid_area[instruction_X[i]]);
            Sleep(1000); // 可视化
        }
        else if (instructions[i] == "jump") // jump操作
        {
            if (!is_jump(instruction_X[i], i, m))
            {
                is_error = true;
                setCursorPos(0, 34);
                cout << "                                            "; // 清除
                setCursorPos(0, 34);
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            jump(instruction_X[i], i);
        }
        else if (instructions[i] == "jumpifzero") // jumpifzero操作
        {
            if (!is_jumpifzero(instruction_X[i], i, m, is_hold_block))
            {
                is_error = true;
                setCursorPos(0, 34);
                cout << "                                            "; // 清除
                setCursorPos(0, 34);
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            jumpifzero(instruction_X[i], i, current_hold_num);
        }
        else // 指令不是以上操作，发生错误
        {
            is_error = true;
            setCursorPos(0, 34);
            cout << "                                            "; // 清除
            setCursorPos(0, 34);
            cout << "Error on instruction " << i + 1 << endl;
            break;
        }
    }
    if(is_error==true)
    setCursorPos(0, 35); // 调整光标
    else setCursorPos(0, 34);
    // 检查是否通关
    if (user_out == out_list)
    {
        is_pass = true;
    }
    if (!is_pass && !is_error)
    {
        cout << "You have failed to pass Level 2 !" << endl;
    }
    if (is_pass && !is_error)
    {
        cout << "Congratualations! You have passed Level 2 !" << endl;
        levelpassed[1] = true;
    }
    cout << "Press return key to return to Level Select..." << endl; // 等待回车
    cin.ignore();                                                    // 清除输入缓冲区中的换行符
    cin.get();                                                       // 等待用户按下回车
}
void print_level_3(vector<int> entry_list)
{
    system("cls"); // 清屏
    cout << "===========" << " Start to challenge Level 3 " << "===========" << endl;
    cout << "Level 3 is playing..." << endl;
    cout << "Level information:" << endl;
    cout << "Repeatedly take two numbers from the input; output one if they are equal, otherwise discard them, until the input is empty." << endl;
    cout << "a.Input and output of the level:" << endl;
    cout << "  i.Input: 6 2 7 7 -9 3 -3 -3" << endl;
    cout << "  ii.Output: 7 -3" << endl;
    cout << "b.Number of available open spaces: 3" << endl;
    cout << "c.Available instruction set: inbox outbox copyfrom copyto add sub jump jumpifzero" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    setCursorPos(0, 11);
    cout << "IN";
    for (int i = 0; i <= entry_list.size() - 1; i++)
    {
        print_block(4, i * 3 + 10, entry_list[i]);
    }
    for (int i = 0; i <= entry_list.size() - 1; i++)
    {
        print_blank_block(50, i * 3 + 10);
    }
    setCursorPos(57, 11);
    cout << "OUT";
    for (int i = 0; i < 24; ++i)
    {
        setlocale(LC_ALL, "");
        setCursorPos(62, i + 10);
        wcout << L'│' << '\n';
    }
    setCursorPos(63, 10);
    cout << " ======= CODE =======";
    print_robot(0);
    for (int j = 17; j <= 37; j += 10)
    {
        print_blank_block(j, 23);
    }
    for (int j = 19; j <= 39; j += 10)
    {
        setCursorPos(j, 26);
        cout << j / 10 - 1;
    }
}

void level_3(int m, vector<string> instructions, vector<int> instruction_X, vector<int> entry_list, vector<int> out_list)
{
    vector<int> valid_area(3);       // 空地
    vector<bool> is_valid(3, false); // 空地是否被占用
    vector<int> user_out;            // 经过输入指令输出的序列
    bool is_hold_block = false;      // 机器人手上是否有积木
    int current_hold_num = 0;        // 机器人手上的积木号
    bool is_pass = false;            // 是否通关
    bool is_error = false;           // 是否发生错误
    for (int i = 0; i < m; i++)      // 打印code
    {
        setCursorPos(67, 11 + i);
        cout << i + 1 << " " << instructions[i];
        if(instructions[i]=="jump"||instructions[i]=="jumpifzero"||instructions[i]=="add"||instructions[i]=="sub"||instructions[i]=="copyfrom"||instructions[i]=="copyto")
        {
            cout << " " << instruction_X[i];
        }
    }
    // 遍历
    for (int i = 0; i < m; i++)
    {
        for (int i = 0; i < m; i++)
        {
            setCursorPos(65, 11 + i);
            cout << " ";
        }
        setCursorPos(65, 11 + i);
        cout << "> "; // 更新>的位置
        Sleep(1000);  // 可视化
        if (instructions[i] == "inbox")
        {
            if(entry_list.empty())
            {
                break;
            }
            inbox(is_hold_block, entry_list, current_hold_num);
            for (int j = 0; j < entry_list.size(); j++)
            {
                print_block(4, j * 3 + 10, entry_list[j]);
            }
            for (int j = entry_list.size(); j < 8; j++)
            {
                print_blank_block(4, j * 3 + 10);
            }
            print_hold_block(0, current_hold_num); // 更新输入序列
            Sleep(1000);                           // 可视化
        }
        else if (instructions[i] == "outbox")
        {
            if (!is_outbox(is_hold_block))
            {
                is_error = true;
                setCursorPos(0, 34);
                cout << "                                            "; // 清除
                setCursorPos(0, 34);
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            outbox(is_hold_block, user_out, current_hold_num);
            for (int j = 0; j <= 25; j++) // 向右移动
            {
                for (int m = 10; m <= 21; m++)
                {
                    for (int n = 14; n <= 49; n++)
                    {
                        setCursorPos(n, m);
                        cout << " ";
                    }
                }
                print_robot(j);
                print_hold_block(j, current_hold_num);
                Sleep(10);
            }
            for (int j = 0; j < user_out.size(); j++)
            {
                print_block(50, j * 3 + 10, user_out[user_out.size() - 1 - j]);
            }
            for (int j = user_out.size(); j < 8; j++)
            {
                print_blank_block(50, j * 3 + 10);
            } // 更新输出序列
            for (int j = 25; j >= 0; j--)
            {
                for (int m = 10; m <= 21; m++)
                {
                    for (int n = 14; n <= 49; n++)
                    {
                        setCursorPos(n, m);
                        cout << " ";
                    }
                }
                print_robot(j);
                Sleep(10);
            } // 向左移动
        }
        else if (instructions[i] == "add") // add操作
        {
            if (!is_add(is_hold_block, instruction_X[i], is_valid))
            {
                is_error = true;
                setCursorPos(0, 34);
                cout << "                                            "; // 清除
                setCursorPos(0, 34);
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            add(instruction_X[i], valid_area, current_hold_num);
            print_hold_block(0, current_hold_num + valid_area[instruction_X[i]]);
            Sleep(1000); // 可视化
        }
        else if (instructions[i] == "sub") // sub操作
        {
            if (!is_sub(is_hold_block, instruction_X[i], is_valid))
            {
                is_error = true;
                setCursorPos(0, 34);
                cout << "                                            "; // 清除
                setCursorPos(0, 34);
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            sub(instruction_X[i], valid_area, current_hold_num);
            print_hold_block(0, current_hold_num - valid_area[instruction_X[i]]);
            Sleep(1000); // 可视化
        }
        else if (instructions[i] == "copyto") // copyto操作
        {
            if (!is_copyto(is_hold_block, instruction_X[i], is_valid))
            {
                is_error = true;
                setCursorPos(0, 34);
                cout << "                                            "; // 清除
                setCursorPos(0, 34);
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            copyto(instruction_X[i], valid_area, current_hold_num, is_valid);
            print_block(instruction_X[i] * 10 + 17, 23, current_hold_num);
            Sleep(1000); // 可视化
        }
        else if (instructions[i] == "copyfrom") // copyfrom操作
        {
            if (!is_copyfrom(instruction_X[i], is_valid))
            {
                is_error = true;
                setCursorPos(0, 34);
                cout << "                                            "; // 清除
                setCursorPos(0, 34);
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            copyfrom(instruction_X[i], valid_area, current_hold_num, is_hold_block);
            print_hold_block(0, valid_area[instruction_X[i]]);
            Sleep(1000); // 可视化
        }
        else if (instructions[i] == "jump") // jump操作
        {
            if (!is_jump(instruction_X[i], i, m))
            {
                is_error = true;
                setCursorPos(0, 34);
                cout << "                                            "; // 清除
                setCursorPos(0, 34);
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            jump(instruction_X[i], i);
        }
        else if (instructions[i] == "jumpifzero") // jumpifzero操作
        {
            if (!is_jumpifzero(instruction_X[i], i, m, is_hold_block))
            {
                is_error = true;
                setCursorPos(0, 34);
                cout << "                                            "; // 清除
                setCursorPos(0, 34);
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            jumpifzero(instruction_X[i], i, current_hold_num);
        }
        else // 指令不是以上操作，发生错误
        {
            is_error = true;
            setCursorPos(0, 34);
            cout << "                                            "; // 清除
            setCursorPos(0, 34);
            cout << "Error on instruction " << i + 1 << endl;
            break;
        }
    }
    if(is_error==true)
    setCursorPos(0, 35); // 调整光标
    else setCursorPos(0, 34);
    // 检查是否通关
    if (user_out == out_list)
    {
        is_pass = true;
    }
    if (!is_pass && !is_error)
    {
        cout << "You have failed to pass Level 3 !" << endl;
    }
    if (is_pass && !is_error)
    {
        cout << "Congratualations! You have passed Level 3 !" << endl;
        levelpassed[2] = true;
    }
    cout << "Press return key to return to Level Select..." << endl; // 等待回车
    cin.ignore();                                                    // 清除输入缓冲区中的换行符
    cin.get();                                                       // 等待用户按下回车
}
// 主函数
int main()
{
    // 加载通关进度
    loadprogress();
    // 循环显示关卡界面
    while (true)
    {
        // 显示关卡选择界面
        showlevelselect();
        // 获取用户输入
        int level_choice;
        // 处理非数字输入
        while (!(cin >> level_choice))
        {
            // 清除
            cin.clear();
            cin.ignore();
            cout << "Invalid input! Please enter a number between 0 and 4 : ";
            continue;
        }
        // 检查选择关卡的合法性
        if (!checklevel(level_choice))
        {
            cout << "Press return key to choose again...";
            cin.ignore();
            cin.get();
            continue;
        }
        // 0保存进度后退出
        if (level_choice == 0)
        {
            saveprogress();
            cout << "Game Over! Thanks for playing!" << endl;
            break;
        }

        if (level_choice == 1)
        {
            print_level_1();
            setCursorPos(0, 22);
            cout << "Please enter how many steps you want to take: ";
            int m;
            cin >> m;                        // m为指令数
            vector<string> instructions(m);  // 指令序列
            vector<int> instruction_X(m, 0); // 指令X序列
            cout << "Please enter your operations: " << endl;
            for (int i = 0; i < m; i++)
            {
                cin >> instructions[i];
                if (instructions[i] == "add" || instructions[i] == "sub" || instructions[i] == "copyto" || instructions[i] == "copyfrom" || instructions[i] == "jump" || instructions[i] == "jumpifzero")
                {
                    int x;
                    cin >> x;
                    instruction_X[i] = x;
                }
            }
            level_1(m, instructions, instruction_X);
        }

        else if (level_choice == 2)
        {
            vector<int> entry_list = {3, 9, 5, 1, -2, -2, 9, -9}; // 输入序列
            vector<int> out_list = {-6, 6, 4, -4, 0, 0, 18, -18}; // 目标输出序列
            print_level_2(entry_list);
            // 输入
            setCursorPos(0, 34);
            cout << "Please enter how many steps you want to take: ";
            int m;
            cin >> m;                        // m为指令数
            vector<string> instructions(m);  // 指令序列
            vector<int> instruction_X(m, 0); // 指令X序列
            cout << "Please enter your operations: " << endl;
            for (int i = 0; i < m; i++)
            {
                cin >> instructions[i];
                if (instructions[i] == "add" || instructions[i] == "sub" || instructions[i] == "copyto" || instructions[i] == "copyfrom" || instructions[i] == "jump" || instructions[i] == "jumpifzero")
                {
                    int x;
                    cin >> x;
                    instruction_X[i] = x;
                }
            }
            print_level_2(entry_list);
            level_2(m, instructions, instruction_X, entry_list, out_list);
        }
        else if (level_choice == 3)
        {
            vector<int> entry_list = {6, 2, 7, 7, -9, 3, -3, -3}; // 输入序列
            vector<int> out_list = {7, -3}; // 目标输出序列
            print_level_3(entry_list);
            // 输入
            setCursorPos(0, 34);
            cout << "Please enter how many steps you want to take: ";
            int m;
            cin >> m;                        // m为指令数
            vector<string> instructions(m);  // 指令序列
            vector<int> instruction_X(m, 0); // 指令X序列
            cout << "Please enter your operations: " << endl;
            for (int i = 0; i < m; i++)
            {
                cin >> instructions[i];
                if (instructions[i] == "add" || instructions[i] == "sub" || instructions[i] == "copyto" || instructions[i] == "copyfrom" || instructions[i] == "jump" || instructions[i] == "jumpifzero")
                {
                    int x;
                    cin >> x;
                    instruction_X[i] = x;
                }
            }
            print_level_3(entry_list);
            level_3(m, instructions, instruction_X, entry_list, out_list);       //2、3一样的操作
        }
        // 玩完保存
        saveprogress();
    }

    return 0;
}
