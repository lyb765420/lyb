#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
using namespace std;
/*
*  BF �ַ���ƥ���㷨
*  ����˵��
*  srcStr  ԭʼ�ַ���
*  subStr  �ӣ�ģʽ���ַ���
*  ����ֵ˵�� -1 ��ʾ����ʧ��
*/
//�޸Ĵ���֧��ͨ���*Ϊƥ����������ַ�

int  bruteForceMatch(string srcStr,string subStr,int *len,int *t) {
    // ��ָ��,��ԭʼ�ַ������ƶ�
    int long_index = 0;
    // ��ָ��,��ģʽ�ַ������ƶ�
    int short_index = 0;
    // ����ָ��,��ʼ�ͳ�ָ��λ����ͬ
    int fu_index = long_index;
    // ԭʼ�ַ�������
    int str_len = srcStr.size();
    // ģʽ�ַ����ĳ���
    int sub_len = subStr.size();
    int sub_len_=0;
    while (long_index < str_len-sub_len+1) {
        // �ѳ�ָ���λֵ��������ָ��
        fu_index = long_index;
        //��ʼ��ָ��λ��
        short_index = 0;
        while (short_index < sub_len ) {
            if (subStr[short_index]=='?')
            {
                //����ָ������
                fu_index ++;
                //��ָ������
                short_index ++;
                sub_len_++;
            }
            else if (subStr[short_index]=='*')
            {
                //����ָ������
                // fu_index ++;
                *t=1;
                if (srcStr[fu_index]==subStr[short_index+1])
                {
                    // short_index++;   
                    // fu_index ++;
                    // sub_len_++;                     //?���� sssiii *si -> si ������ sssi
                    short_index++;                        //?���� sssiii *si -> si ������ sssi
                }
                else {
                    fu_index ++;
                    sub_len_++;
                    // short_index++;   
                }
                
                //��ָ������
                // continue;
                // short_index ++;
            }
            else if (srcStr[fu_index] == subStr[short_index])
            {
                //����ָ������
                fu_index ++;
                //��ָ������
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
                    //ƥ��ɹ�
            *len=sub_len_;
            return  long_index;
        }
        //ƥ�䲻�ɹ�����ָ�������ƶ�
        long_index ++;
    }
    return -1;
}
/*
*  KMP �ַ���ƥ���㷨
*  ����˵��
*  srcStr  ԭʼ�ַ���
*  subStr  �ӣ�ģʽ���ַ���
*  ����ֵ˵�� -1 ��ʾ����ʧ��
*/
vector<int> Next(string pattern)
{
    vector<int> next;
    next.push_back(0);//next��������λ��Ϊ0
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
    cout<<"���룺\n1.BF\n2.KMP"<<endl;
    cin>>x;
    if (x==1)
    {
        string srcStr,subStr;
        // string subStr="*i*g";
        while (1)
        {
            cout<<"******************* ���� Exit �˳� *********************"<<endl;
            cout<<"���룺str="<<" ";
            getline(cin,srcStr);
            if (srcStr=="Exit")
            {
                break;
            }
            cout<<"���룺pattern="<<" ";
            getline(cin,subStr);
            
            
            int len=subStr.length(),t=0;
            int res= bruteForceMatch(srcStr,subStr,&len,&t);
            cout<<"ƥ��index��"<<res<<endl;
            if (res!=-1)
            {
                if (t==1)
                {
                    cout<<"ƥ��ɹ�����һ��ƥ����̵��Ӵ�Ϊ��"<<srcStr.substr(res,len)<<"��"<<endl;
                }
                else
                    cout<<"ƥ��ɹ�����һ��ƥ����Ӵ�Ϊ��"<<srcStr.substr(res,len)<<"��"<<endl;
            }
            else cout<<"ƥ��ʧ��"<<endl;
            
            cout<<"------------------- ���� Exit �˳� ---------------------"<<endl;
        }
    }
    else if (x==2)
    {
        string subStr,srcStr;
        while (1)
        {
            cout<<"******************* ���� Exit �˳� *********************"<<endl;
            cout<<"���룺str="<<" ";
            getline(cin,srcStr);
            if (srcStr=="Exit")
            {
                break;
            }
            cout<<"���룺pattern="<<" ";
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
                    cout<<"ƥ��ɹ����ҵ��Ӵ�λ��:"<<i-j+1<<endl;
                    cout<<"ƥ��ɹ����Ӵ�Ϊ��"<<srcStr.substr(i-j+1,subStr.length())<<"��"<<endl;

                    j=next[j-1];
                }
                
                
            }
            
            
            cout<<"------------------- ���� Exit �˳� ---------------------"<<endl;
        }
    }
    
    
    
    system("PAUSE");
    return 0;
}
