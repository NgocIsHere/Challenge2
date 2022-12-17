#include "Header.h"

map<string, int> matching_list = {{"-bf", 1}, {"-rk", 2}, {"-kmp", 3}, {"-bm", 4}, {"-tw", 5}};
map<string, int> outp = {{"-t", 1}, {"-n", 2}, {"-ind", 3}};

vector<pair<int,int>> OutInfo(int out, int Alg, string pat, string txt, string outputDir)
{
    long long cnt_cmp = 0;
    double time = 0;
    vector<pair<int,int>> pos;
    switch (Alg)
    {
    case 1:
    {
        cout << "# Thuat toan Brute-force" << endl;
        auto start = high_resolution_clock::now();
        pos = Brute_force_Cmp(pat, txt, cnt_cmp);
        auto end = high_resolution_clock::now();
        time = duration_cast<nanoseconds>(end - start).count() / 1000000.0;
        break;
            
    }
    case 2:
    {
        cout << "# Thuat toan Rabin-Karp" << endl;
        auto start = high_resolution_clock::now();
        pos = RabinKarpAlgo(pat, txt, cnt_cmp);
        auto end = high_resolution_clock::now();
        time = duration_cast<nanoseconds>(end - start).count() / 1000000.0;
        break;
    }
    case 3:
    {
        cout << "# Thuat toan Knuth-Morris-Pratt" << endl;
        auto start = high_resolution_clock::now();
        pos = KMPAlgo(pat, txt, cnt_cmp);
        auto end = high_resolution_clock::now();
        time = duration_cast<nanoseconds>(end - start).count() / 1000000.0;
        break;
    }
    case 4:
    {
        cout << "# Thuat toan Boyer–Moore" << endl;
        auto start = high_resolution_clock::now();
        pos = Boyer_Moore_Search(pat, txt, cnt_cmp);
        auto end = high_resolution_clock::now();
        time = duration_cast<nanoseconds>(end - start).count() / 1000000.0;
        break;
    }
    case 5:
        cout << "# Thuat toan Two-way" << endl;
        TwoWayMatching(pat, txt, outputDir, cnt_cmp);
        break;
    default:
        break;
    }

    switch (out)
    {
    case 1:
        cout << "Thoi gian: " << time << endl;
        break;
    case 2:
        cout << "So phep so sanh: " << cnt_cmp << endl;
        break;
    case 3:
        cout << "Thoi gian: " << time << endl;
        cout << "So phep so sanh: " << cnt_cmp << endl;
        break;
    default:
        break;
    }
    return pos;
}
void saveOutF(string opath, vector<pair<int, int>> pos)
{
    fstream file;
    file.open(opath.c_str(), ios::out | ios::trunc);
    for (int i = 0; i < pos.size(); i++)
    {
        file << pos[i].first << " " << pos[i].second << endl;
    }
    file.close();
}
void Cmd(int argc, char **argv)
{
    int Alg = matching_list[string(argv[1])];
    int out = outp[string(argv[4])];
    string ipath = argv[2];
    string opath = argv[3];
    string pat;
    string txt;
    int s[7] = {1, 5, 10, 100, 200, 500, 1000};
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 7; j++)
        {
            if (s[i] * 100 > s[j] * 10)
            {
                createData(s[j] * 10, s[i] * 100, ipath+to_string(i)+to_string(j), false);
                ifstream readfile;
                readfile.open((ipath+to_string(i)+to_string(j)).c_str());
                getline(readfile, pat);
                getline(readfile, txt);
                readfile.close();
                cout<<"  #"<<(ipath+to_string(i)+to_string(j)).c_str()<<" "<<s[j] * 10<<" "<< s[i] * 100<<endl;
                vector<pair<int,int>> pos = OutInfo(out, Alg, pat, txt, opath+to_string(i)+to_string(j));
                saveOutF(opath+to_string(i)+to_string(j), pos);
            }
        }
}
int main(int argc, char **argv)
{
    Cmd(argc, argv);
    return 0;
}
