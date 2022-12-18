#include "Header.h"

// d is the number of characters
#define d 256
// q = INT_MAX  to avoid integer overflow
#define q INT_MAX

using namespace std;

vector<pair<int, int>> RabinKarpAlgo(string pattern, string text, long long &c)
{
    vector<pair<int, int>> pos;
    int n = text.length();
    int m = pattern.length();
    int h = 1;
    int p = 0; // Hash value for pattern
    int t = 0; // Hash value for text
    int i, j;
    bool flag =true;
    static long long temp;
    // Calculate  h = d^(m-1) mod q
    for (int i = 0; ++c && i < m - 1; i++)
    {
        h = (h * d) % q;
    }

    // Preprocessing hash value of pattern and text
    for (i = 0; ++c && i < m; i++)
    {
        p = (d * p + int(pattern[i])) % q;
        t = (d * t + int(text[i])) % q;
    }
    // Slide the pattern over text one by one character
    for (i = 0; ++c && i <= n - m; i++)
    {

        // Check matching the same hash code
        if (++c && p == t)
        {
            // Check each characters
            for (j = 0; ++c && j < m; j++)
            {
                if (++c && text[i + j] != pattern[j])
                    break;
            }
            if (++c && j == m)
            {
                // cout << i << " " << i + m - 1 << endl;
                if(flag==true){
                    temp = c;
                    flag = false;
                }
                pos.push_back(make_pair(i, i + m - 1));
            }
        }
        // Calculate the hash value of the next part of text
        if (++c && i < n - m)
        {
            t = (d * (t - int(text[i] * h)) + int(text[i + m])) % q;
            // Converting t to sure t is positive
            if (t < 0)
                t = t + q;
        }
    }
    c = temp;
    return pos;
}
void computePrefix(string pattern, int m, int* lps, long long &c)
{
    int len = 0;
    // First element always 0
    lps[0] = 0;
    int i = 1;
 
    while (++c && i < m)
    {
        if (++c && pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            lps[i] = 0;
            i++;
        }
    }
}
 
vector<pair<int, int>> KMPAlgo(string pattern, string text, long long &c)
{
    vector<pair<int, int>> pos;
    bool flag = true;
    int m = pattern.length();
    int n = text.length();
    // lps[] will hold the longest prefix suffix
    int* lps = new int [m];
    // calculate lps[]
    computePrefix(pattern, m, lps, c);
    int i = 0, j = 0;
    static long long temp;
    while (++c && (n - i) >= (m - j))
    {
        if (++c && pattern[j] == text[i])
        {
            j++;
            i++;
        }
        if (++c && j == m)
        {
            pos.push_back(make_pair(i - j, i - j + m - 1));
            if(flag==true){
				temp = c;
				flag = false;
			}
            // back track
            j = lps[j - 1];
        }
        else if (++c && i < n && ++c && pattern[j] != text[i])
        {
            if (++c && j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    delete lps;
    c = temp;
    return pos;
 
}
 
/*
int main()
{

    string text = "abd caafg haretwq treqtrq qed abd atojv abd";
    string pattern = "abd";
    int c1 = 0;
    int c2 = 0;
    vector<pair<int, int>> posRK;
    vector<pair<int, int>> posKMP;
    cout << "Do dai chuoi text: " << text.length() << endl;
    cout << "Do dai chuoi pattern: " << pattern.length() << endl;

    // Test Rabin Karp
    posRK = RabinKarpAlgo(pattern, text, c1);
    cout << "Vi tri : " << endl;
    for (int i = 0; i < posRK.size(); i++)
    {
        cout << posRK[i].first << " " << posRK[i].second << endl;
    }
    cout << endl;
    cout << "So phep so sanh cua Rabin Karp : " << c1 << endl;
    cout << "======================" << endl;
    // Test KMP
    posKMP = KMPAlgo(pattern, text, c2);
    cout << "Vi tri : " << endl;
    for (int i = 0; i < posKMP.size(); i++)
    {
        cout << posRK[i].first << " " << posRK[i].second << endl;
    }
    cout << "So phep so sanh cua KMP : " << c2 << endl;

    return 0;
}
*/
