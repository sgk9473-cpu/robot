#include <bits/stdc++.h>
using namespace std;

//初始通关状态
bool levelpassed[4]={false,false,false,false};

//建立保存进度的文件
const string progressfile="robot_progress.txt";

//从文件加载通关进度
void loadprogress()
{
    ifstream fin(progressfile);
    if(!fin.is_open())
    {
        cerr<<"First-time game play, initializing progress file..."<<endl;
        return;
    }
    int status;
    for(int i=0;i<4;i++)
    {
        fin>>status;
        if(status==1)
        {
            levelpassed[i]=true;
        }
        else
        {
            levelpassed[i]=false;
        }
    }
    fin.close();
    cout<<"Progress loaded successfully!"<<endl;
}

//保存通关进度到文件
void saveprogress()
{
    ofstream fout(progressfile);
    if(!fout.is_open())
    {
        cerr<<"Error: Failed to save progress!"<<endl;
        return;
    }
    for(int i=0;i<4;i++)
    {
        if(levelpassed[i])
        {
            fout<<1<<" ";
        }
        else
        {
            fout<<0<<" ";
        }
    }
    fout.close();
    cout<<"Progress saved successfully!"<<endl;
}

//显示关卡选择界面
void showlevelselect()
{
    //清屏
    system("cls");
    cout<<"==========="<<" Level Select "<<"==========="<<endl;
    cout<<endl;
    cout<<"1. Level 1:  "<<(levelpassed[0]?"(Passed)":"(Not Passed)")<<endl;
    cout<<"2. Level 2:  "<<(levelpassed[1]?"(Passed)":"(Not Passed)")<<endl;
    cout<<"3. Level 3:  "<<(levelpassed[2]?"(Passed)":"(Not Passed)")<<endl;
    cout<<"4. Level 4:  "<<(levelpassed[3]?"(Passed)":"(Not Passed)")<<endl;
    cout<<endl;
    cout<<"===================================="<<endl;
    cout<<endl;
    cout<<"Enter your challenge choice (1-4) (0 to exit): ";
}

//模拟玩关卡过程
void mimicplay(int level_num)
{
    //清屏
    system("cls");
    cout<<"==========="<<" Start to challenge Level "<<level_num<<" ==========="<<endl;
    cout<<"Level "<<level_num<<" is playing..."<<endl;
    cout<<"press any key to continue...(just mimic the progress)"<<endl;
    //随便输模拟玩游戏
    string input;
    cin>>input;
    //通关
    levelpassed[level_num-1]=true;
    cout<<"Congratualations! You have passed Level "<<level_num<<" !"<<endl;
    cout<<"Press return key to return to Level Select..."<<endl;
    //等待回车
    cin.ignore();//清除输入缓冲区中的换行符
    cin.get();//等待用户按下回车
}

//检查选关卡的合法性
bool checklevel(int level_choice)
{
    //0退出
    if(level_choice==0)
    {
        return true;
    }
    //1-4选关卡
    if(level_choice<1||level_choice>4)
    {
        cout<<"Invalid level choice! Please enter a number between 1 and 4."<<endl;
        return false;
    }
    //第1关随便玩
    if(level_choice==1)
    {
        return true;
    }
    //检查前面关卡的通过情况
    if(!levelpassed[level_choice-2])
    {
        cout<<"You must pass Level "<<level_choice-1<<" before you can play Level "<<level_choice<<" !"<<endl;
        return false;
    }
    //所有都满足
    return true;
}

//主函数
int main()
{
    //加载通关进度
    loadprogress();
    //循环显示关卡界面
    while(true)
    {
        //显示关卡选择界面
        showlevelselect();
        //获取用户输入
        int level_choice;
        //处理非数字输入
        while(!(cin>>level_choice))
        {
            //清除
            cin.clear();
            cin.ignore();
            cout<<"Invalid input! Please enter a number between 0 and 4 : ";
        }
        //检查选择关卡的合法性
        if(!checklevel(level_choice))
        {
            cout<<"Press return key to choose again...";
            cin.ignore();
            cin.get();
            continue;
        }
        //0保存进度后退出
        if(level_choice==0)
        {
            saveprogress();
            cout<<"Game Over! Thanks for playing!"<<endl;
            break;
        }
        //合法后模拟开玩
        mimicplay(level_choice);
        //玩完保存
        saveprogress();
    }
    
    return 0;
}