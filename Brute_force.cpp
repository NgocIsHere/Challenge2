#include "Header.h"

vector<pair<int, int>> Brute_force_Cmp(string pat, string txt, long long &cnt_cmp)
{
    int M = pat.length();
    int N = txt.length();
    static long long temp;
    vector<pair<int, int>> index;
    for (int i = 0; ++cnt_cmp && i <= N - M; i++) {
        int j;
        for (j = 0; ++cnt_cmp && j < M; j++){
            if (++cnt_cmp && txt[i + j] != pat[j])
                break;
        }
        if (j== M) 
            temp = cnt_cmp;
            index.push_back(make_pair(i, i + M - 1));
    }
    cnt_cmp = temp;
    return index;
}

