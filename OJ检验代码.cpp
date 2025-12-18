#include <bits/stdc++.h>
using namespace std;

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
void inbox(bool& is_hold_block, vector<int>& entry_list, int& current_hold_num)
{
    if(entry_list.size()>=1)
    {
    is_hold_block = true;
    current_hold_num = entry_list[0];
    entry_list.erase(entry_list.begin());
    }
}
// outbox操作
void outbox(bool& is_hold_block, vector<int>& out_list, int& current_hold_num)
{
    out_list.push_back(current_hold_num);
    is_hold_block = false;
}
// add操作
void add(int X, vector<int>& valid_area, int& current_hold_num)
{
    current_hold_num += valid_area[X];
}
// sub操作
void sub(int X, vector<int>& valid_area, int& current_hold_num)
{
    current_hold_num -= valid_area[X];
}
// copyto操作
void copyto(int X, vector<int>& valid_area, int& current_hold_num, vector<bool>& is_valid)
{
    valid_area[X] = current_hold_num;
    is_valid[X] = true;
}
// copyfrom操作
void copyfrom(int X, vector<int>& valid_area, int& current_hold_num, bool& is_hold_block)
{
    current_hold_num = valid_area[X];
    is_hold_block = true;
}
// jump操作
void jump(int X, int& i)
{
    i=X-2;
}
// jumpifzero操作
void jumpifzero(int X, int& i, int& current_hold_num)
{
    if (current_hold_num == 0)
    {
        i=X-2;
    }
}
void play_level_1(int instruction_num, vector<string> instructions)
{
    bool is_hold_block = false;  // 机器人手上是否有积木
    int transport_block_num = 0; // 机器人运输的积木数量
    bool is_pass = false;        // 是否通关
    bool is_error = false;       // 是否发生错误
    vector<int> entry_list = {1,2}; // 输入序列
    vector<int> out_list = {1,2}; // 目标输出序列
    vector<int> user_out;                                 // 经过输入指令输出的序列
    int current_hold_num = 0; // 机器人手上的积木
    for (int i = 0; i < instruction_num; i++)
    {
        if (instructions[i] == "inbox")
        {
            inbox(is_hold_block, entry_list, current_hold_num);
        }
        else if (instructions[i] == "outbox")
        {
            if (!is_outbox(is_hold_block))
            {
                is_error = true;
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            outbox(is_hold_block, user_out, current_hold_num);
        }
        else // 指令不是inbox或outbox，发生错误
        {
            cout << "Error on instruction " << i + 1 << endl;
            is_error = true;
            break;
        }
    }
    // 检查是否通关
    if(user_out==out_list)
    {
        is_pass = true;
    }
    if(!is_pass&&!is_error)
    {
        cout<<"Fail"<<endl;
    }
    if(is_pass&&!is_error)
    {
        cout<<"Success"<<endl;
    }
}

void play_level_2(int instruction_num, vector<string> instructions, vector<int> instruction_X)
{
    vector<int> valid_area(3);                            // 空地
    vector<bool> is_valid(3, false);                          // 空地是否被占用
    vector<int> entry_list = {3, 9, 5, 1, -2, -2, 9, -9}; // 输入序列
    vector<int> out_list = {-6, 6, 4, -4, 0, 0, 18, -18}; // 目标输出序列
    vector<int> user_out;                                 // 经过输入指令输出的序列
    bool is_hold_block = false;                           // 机器人手上是否有积木
    int current_hold_num = 0;                             // 机器人手上的积木号
    bool is_pass = false;                                 // 是否通关
    bool is_error = false;                                // 是否发生错误
    // 遍历
    for (int i = 0; i < instruction_num; i++)
    {
        if (instructions[i] == "inbox") // inbox操作
        {
            if(entry_list.size()==0)break;
            inbox(is_hold_block, entry_list, current_hold_num);
        }
        else if (instructions[i] == "outbox") // outbox操作
        {
            if (!is_outbox(is_hold_block))
            {
                is_error = true;
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            outbox(is_hold_block, user_out, current_hold_num);
        }
        else if (instructions[i] == "add") // add操作
        {
            if (!is_add(is_hold_block, instruction_X[i], is_valid))
            {
                is_error = true;
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            add(instruction_X[i], valid_area, current_hold_num);
        }
        else if (instructions[i] == "sub") // sub操作
        {
            if (!is_sub(is_hold_block, instruction_X[i], is_valid))
            {
                is_error = true;
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            sub(instruction_X[i], valid_area, current_hold_num);
        }
        else if (instructions[i] == "copyto") // copyto操作
        {
            if (!is_copyto(is_hold_block, instruction_X[i], is_valid))
            {
                is_error = true;
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            copyto(instruction_X[i], valid_area, current_hold_num, is_valid);
        }
        else if (instructions[i] == "copyfrom") // copyfrom操作
        {
            if (!is_copyfrom(instruction_X[i], is_valid))
            {
                is_error = true;
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            copyfrom(instruction_X[i], valid_area, current_hold_num, is_hold_block);
        }
        else if (instructions[i] == "jump") // jump操作
        {
            if (!is_jump(instruction_X[i], i, instruction_num))
            {
                is_error = true;
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            jump(instruction_X[i], i);
        }
        else if (instructions[i] == "jumpifzero") // jumpifzero操作
        {
            if (!is_jumpifzero(instruction_X[i], i, instruction_num, is_hold_block))
            {
                is_error = true;
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            jumpifzero(instruction_X[i], i, current_hold_num);
        }
        else // 指令不是以上操作，发生错误
        {
            cout << "Error on instruction " << i + 1 << endl;
            is_error = true;
            break;
        }
    }
    if (user_out == out_list)
    {
        is_pass = true;
    }
    if (is_error == false && is_pass == true)
    {
        cout << "Success" << endl;
    }
    if (is_error == false && is_pass == false)
    {
        cout << "Fail" << endl;
    }
}

void play_level_3(int instruction_num, vector<string> instructions, vector<int> instruction_X)
{
    vector<int> valid_area(3);                            // 空地
    vector<bool> is_valid(3, false);                          // 空地是否被占用
    vector<int> entry_list = {6,2,7,7,-9,3,-3,-3}; // 输入序列
    vector<int> out_list = {7,-3}; // 目标输出序列
    vector<int> user_out;                                 // 经过输入指令输出的序列
    bool is_hold_block = false;                           // 机器人手上是否有积木
    int current_hold_num = 0;                             // 机器人手上的积木号
    bool is_pass = false;                                 // 是否通关
    bool is_error = false;                                // 是否发生错误
    // 遍历
    for (int i = 0; i < instruction_num; i++)
    {
        if (instructions[i] == "inbox") // inbox操作
        {
            if(entry_list.size()==0)break;
            inbox(is_hold_block, entry_list, current_hold_num);
        }
        else if (instructions[i] == "outbox") // outbox操作
        {
            if (!is_outbox(is_hold_block))
            {
                is_error = true;
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            outbox(is_hold_block, user_out, current_hold_num);
        }
        else if (instructions[i] == "add") // add操作
        {
            if (!is_add(is_hold_block, instruction_X[i], is_valid))
            {
                is_error = true;
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            add(instruction_X[i], valid_area, current_hold_num);
        }
        else if (instructions[i] == "sub") // sub操作
        {
            if (!is_sub(is_hold_block, instruction_X[i], is_valid))
            {
                is_error = true;
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            sub(instruction_X[i], valid_area, current_hold_num);
        }
        else if (instructions[i] == "copyto") // copyto操作
        {
            if (!is_copyto(is_hold_block, instruction_X[i], is_valid))
            {
                is_error = true;
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            copyto(instruction_X[i], valid_area, current_hold_num, is_valid);
        }
        else if (instructions[i] == "copyfrom") // copyfrom操作
        {
            if (!is_copyfrom(instruction_X[i], is_valid))
            {
                is_error = true;
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            copyfrom(instruction_X[i], valid_area, current_hold_num, is_hold_block);
        }
        else if (instructions[i] == "jump") // jump操作
        {
            if (!is_jump(instruction_X[i], i, instruction_num))
            {
                is_error = true;
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            jump(instruction_X[i], i);
        }
        else if (instructions[i] == "jumpifzero") // jumpifzero操作
        {
            if (!is_jumpifzero(instruction_X[i], i, instruction_num, is_hold_block))
            {
                is_error = true;
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            jumpifzero(instruction_X[i], i, current_hold_num);
        }
        else // 指令不是以上操作，发生错误
        {
            cout << "Error on instruction " << i + 1 << endl;
            is_error = true;
            break;
        }
    }
    if (user_out == out_list)
    {
        is_pass = true;
    }
    if (is_error == false && is_pass == true)
    {
        cout << "Success" << endl;
    }
    if (is_error == false && is_pass == false)
    {
        cout << "Fail" << endl;
    }
}
int main()
{
    int level;           // 第几个关卡
    int instruction_num; // 指令数
    cin >> level >> instruction_num;
    vector<string> instructions(instruction_num); // 指令序列
    vector<int> instruction_X(instruction_num,0);   // 指令X序列
    for (int i = 0; i < instruction_num; i++)
    {
        cin >> instructions[i];
        if (instructions[i] == "add" || instructions[i] == "sub" || instructions[i] == "copyto" || instructions[i] == "copyfrom" || instructions[i] == "jump" || instructions[i] == "jumpifzero")
        {
            int m;
            cin >> m;
            instruction_X[i] = m;
        }
    }
    if (level == 1)
    {
        play_level_1(instruction_num, instructions); // 玩第一关
    }
    else if (level == 2)
    {
        play_level_2(instruction_num, instructions, instruction_X); // 玩第二关
    }
    else if (level == 3)
    {
        play_level_3(instruction_num, instructions, instruction_X); // 玩第三关
    }
    return 0;
}