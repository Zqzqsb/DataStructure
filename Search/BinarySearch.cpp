#include <iostream>
#include <vector>
using namespace std;

int binSearch(vector<int>& v, int element)
{
    int low = 0 , high = v.size() , mid;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if(v[mid] == element)
            return mid;
        if(v[mid] > element) // element 在下半区
            high = mid;
        else
            low = mid;
    }

    return -1;
}

int binSearchRecursive(vector<int>& v , int& element, int low , int high)
{
    if(high < low)
        return -1;
    int mid = (high + low) / 2;
    if(v[mid] == element)
        return mid;
    
    return v[mid] > element ? binSearchRecursive(v , element , low , mid) : binSearchRecursive(v , element , mid , high);
        
}

int binSearchRecursive(vector<int>& v , int element)
{
    return binSearchRecursive(v , element , 0 , v.size());
}

int main()
{
    int array[] = {0,1,2,3,4,5,6,};
    vector<int> v(array , array+7);
    cout << binSearch(v , 3) << endl;

    cout << binSearchRecursive(v , 3) << endl;
    
}