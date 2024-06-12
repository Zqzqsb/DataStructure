#include <iostream>
#include <string>
using namespace std;

class KmpMatcher
{
    string s , p;
    int* Partial_Match;
    int* Next;
public:
    KmpMatcher(const string& s , const string& p)
    {
        this -> s = s;
        this -> p = p;
        Partial_Match = new int[p.length()];
        Next = new int[p.length()];
        buildPartial_Match();
        buildNext();
    }

    int match_withPM()
    {
        int tar = 0 , pos = 0;
        while(tar < (this->s).length() && pos < (this->p).length())
        {
            if(s[tar] == p[pos])
            {
                tar++;
                pos++;
            }
            else if(pos) // miss match case1(matched some part)
            {
                pos = Partial_Match[pos-1];
            }
            else // miss match case2(matched none)
                tar++;
        }
        if(pos == p.length())
            return pos-1; // return real index
        else
            return -1;
    }
    void showNext()
    {
        for(int i = 0 ; i < p.length() ; i++)
            cout << *(Next+i) << " ";
        cout << endl;
    }
    void showPartial_MatchTable()
    {
        for(int i = 0 ; i < p.length() ; i++)
            cout << *(Partial_Match+i) << " ";
        cout << endl;
    }
private:
    void buildPartial_Match()
    {
        *Partial_Match = 0; 
        int now = 0 , x = 1;
        // build Partial_Match from pos1
        while(x < p.length())
        {
            // p[now] = p[x] find a match prefix and suffix , matched length is now
            if(p[now] == p[x])
            {
                now += 1;                
                *(Partial_Match+x) = now; // Partial_Match[x] = now 
                x += 1;
            }
            else if(now)
                now = *(Partial_Match+now-1); // Partial_Match[now-1]
            else
                *(Partial_Match+(x++)) = 0; // Partial_Match[x] = 0 
            // now == 0 can't find a match prefix and suffix
        }
    }

    void buildNext()
    {
        int now = -1 , x = 0;
        *Next = -1;
        while(x < p.length() -1)
        {
            if(now == -1 || p[now] == p[x])
            {
                now++;
                x++;
                if(p[now] == p[x])
                    *(Next+x) = *(Next+now);
                else
                    *(Next+x) = now; 
            }
            else
                now = *(Next+now); // callback

        }
        
    }

    
};

int main()
{
    string p = "aaaab" , s = "ahjdfabcabciopahg";
    KmpMatcher m(s , p);
    m.showPartial_MatchTable();
    m.showNext();
    cout << m.match_withPM() << endl;
}