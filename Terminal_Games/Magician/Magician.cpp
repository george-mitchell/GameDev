// Magician Game
// User picks a number, Magician guesses it after asking three questions. 

#include <iostream> 

using namespace std;

int main()
{
    int Remainder2;
    int Remainder3;
    int Remainder5;
    int Answer; 
    int Answer2;
    cout << "Pick an integer between 1 and 30. \nI will ask thee three questions:" << endl; 
    cout << "The remainder when dividing your number by 2 is: "; 
    cin >> Remainder2; 
    cout << "Of course...\n The remainder when dividing your number by 3 is: "; 
    cin >> Remainder3; 
    cout << "Yes, just as I thought...\nFinally, the remainder when dividing your number by 5 is: ";
    cin >> Remainder5; 
    Answer = (Remainder2 * 15) + (Remainder3 * 10) + (Remainder5 * 6); 
    Answer2 = Answer % 30;
    cout << "How predictable. From the moment I saw you, I knew you'd pick " << Answer2 << "." << endl;

    return 0;

}