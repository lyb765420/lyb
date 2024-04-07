#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
using namespace std;
/*
*  BF 字符串匹配算法
*  参数说明
*  srcStr  原始字符串
*  subStr  子（模式）字符串
*  返回值说明 -1 表示查找失败
*/
//修改代码支持通配符*为匹配零个或多个字符

int  bruteForceMatch(string srcStr,string subStr,int *len,int *t) {
    // 长指针,在原始字符串上移动
    int long_index = 0;
    // 短指针,在模式字符串上移动
    int short_index = 0;
    // 辅助指针,初始和长指针位置相同
    int fu_index = long_index;
    // 原始字符串长度
    int str_len = srcStr.size();
    // 模式字符串的长度
    int sub_len = subStr.size();
    int sub_len_=0;
    while (long_index < str_len-sub_len+1) {
        // 把长指针的位值赋给辅助指针
        fu_index = long_index;
        //初始短指针位置
        short_index = 0;
        while (short_index < sub_len ) {
            if (subStr[short_index]=='?')
            {
                //辅助指针向右
                fu_index ++;
                //短指针向右
                short_index ++;
                sub_len_++;
            }
            else if (subStr[short_index]=='*')
            {
                //辅助指针向右
                // fu_index ++;
                *t=1;
                if (srcStr[fu_index]==subStr[short_index+1])
                {
                    // short_index++;   
                    // fu_index ++;
                    // sub_len_++;                     //?输入 sssiii *si -> si 而不是 sssi
                    short_index++;                        //?输入 sssiii *si -> si 而不是 sssi
                }
                else {
                    fu_index ++;
                    sub_len_++;
                    // short_index++;   
                }
                
                //短指针向右
                // continue;
                // short_index ++;
            }
            else if (srcStr[fu_index] == subStr[short_index])
            {
                //辅助指针向右
                fu_index ++;
                //短指针向右
                short_index ++;
                sub_len_++;
            }
            else{
                // short_index=0;
                sub_len_=0,*t=0;
                break;
            }
        }
        if (short_index == sub_len) {
                    //匹配成功
            *len=sub_len_;
            return  long_index;
        }
        //匹配不成功，则长指针向右移动
        long_index ++;
    }
    return -1;
}
/*
*  KMP 字符串匹配算法
*  参数说明
*  srcStr  原始字符串
*  subStr  子（模式）字符串
*  返回值说明 -1 表示查找失败
*/
vector<int> Next(string pattern)
{
    vector<int> next;
    next.push_back(0);//next容器的首位必为0
    for (int i = 1,j=0; i < pattern.length(); i++)
    {
        while (j>0 && pattern[j]!=pattern[i])
        {
            j=next[j-1];
        }
        if (pattern[i]==pattern[j])
        {
            j++;
        }
        next.push_back(j);
    }
    return next;
}
int main(int argc, char *argv[])
{
    // string srcStr="string matching";
    int x;
    cout<<"输入：\n1.BF\n2.KMP"<<endl;
    cin>>x;
    if (x==1)
    {
        string srcStr,subStr;
        // string subStr="*i*g";
        while (1)
        {
            cout<<"******************* 输入 Exit 退出 *********************"<<endl;
            cout<<"输入：str="<<" ";
            getline(cin,srcStr);
            if (srcStr=="Exit")
            {
                break;
            }
            cout<<"输入：pattern="<<" ";
            getline(cin,subStr);
            
            
            int len=subStr.length(),t=0;
            int res= bruteForceMatch(srcStr,subStr,&len,&t);
            cout<<"匹配index："<<res<<endl;
            if (res!=-1)
            {
                if (t==1)
                {
                    cout<<"匹配成功，第一个匹配最短的子串为“"<<srcStr.substr(res,len)<<"”"<<endl;
                }
                else
                    cout<<"匹配成功，第一个匹配的子串为“"<<srcStr.substr(res,len)<<"”"<<endl;
            }
            else cout<<"匹配失败"<<endl;
            
            cout<<"------------------- 输入 Exit 退出 ---------------------"<<endl;
        }
    }
    else if (x==2)
    {
        string subStr,srcStr;
        while (1)
        {
            cout<<"******************* 输入 Exit 退出 *********************"<<endl;
            cout<<"输入：str="<<" ";
            getline(cin,srcStr);
            if (srcStr=="Exit")
            {
                break;
            }
            cout<<"输入：pattern="<<" ";
            getline(cin,subStr);
            
            vector<int> next = Next(subStr);
            for (int i = 0,j=0; i < srcStr.length(); i++)
            {
                while (j>0 && srcStr[i]!=subStr[j])
                {
                    j=next[j-1];
                }
                if (srcStr[i]==subStr[j])
                {
                    j++;
                }
                if (j==subStr.length())
                {
                    cout<<"匹配成功，找到子串位置:"<<i-j+1<<endl;
                    cout<<"匹配成功，子串为“"<<srcStr.substr(i-j+1,subStr.length())<<"”"<<endl;

                    j=next[j-1];
                }
                
                
            }
            
            
            cout<<"------------------- 输入 Exit 退出 ---------------------"<<endl;
        }
    }
    
    
    
    system("PAUSE");
    return 0;
}
