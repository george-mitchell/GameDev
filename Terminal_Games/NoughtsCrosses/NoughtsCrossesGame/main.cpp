
#include <iostream> 
#include <vector>

using namespace std;

int main()
{
    
    vector <int> numbers {1,1,1,2,2,3}; 
    
    for (int i {1}; i <= 3; ++i)
    {
        int count {0}; 
        for ( auto num: numbers)
        {
            if (num == i)
            {
                count = count + 1;
            }
        }
        cout << count << endl; 
    }
    
    return 0;
}