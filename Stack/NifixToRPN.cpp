#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
string NifixToRpn(string Nifix)
{
    string res;
    stack<char> work;
    for(char i : Nifix)
    {
        if(i >= '0' && i <= '9')
            res += (string)i;
        else
        {
            if(i == '(')
                work.push(i);
            else if(i == ')')
            {
                while(work.top() != '(')
                {
                    res += (string)work.top();
                    work.pop();
                }
                work.pop();
            }
            else
            {
                while(compare(i , work.top()) >= 0)
                {
                    res += (string)work.top();
                    work.pop();
                }
                work.push(i);
            }
        }
    }
    while(!work.empty())
    {
        res += (string)work.top();
        work.pop();
    }
        
        
    return res;
}

int compare(char op1 , char op2)
{
    vector<vector<char>> sq;
    int flag1=0 , flag2=0;
    for(auto &group : sq)
    {
        for(char op : group)
        {
            if(op == op1)
                flag1 = 1;
            if(op == op2)
                flag2 = 1;
        }
        if(flag1 || flag2)
            return flag2 - flag1;
    }
}

int main()
{
    cout << NifixToRpn("1+2-3") << endl;
}