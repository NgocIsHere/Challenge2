#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <chrono>
#include <fstream>
#include <time.h>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <windows.h>

using namespace std::chrono;
using namespace std;

// Brute_force:
vector<pair<int, int>> Brute_force_Cmp(string pat, string txt, long long &cnt_cmp);

// RK:
vector<pair<int, int>> RabinKarpAlgo(string pattern, string text, long long &c);


// KMPAlgo:
void computePrefix(string pattern, int m, int *lps, long long &c);
vector<pair<int, int>> KMPAlgo(string pattern, string text, long long &c);

// Boyer_Moore_Search:
void FindLastOccur(string pat,int L[],int size,long long &cnt_cmp);
vector<pair<int, int>> Boyer_Moore_Search(string pat, string str, long long &cnt_cmp);

// Two way:
int Max(int a, int b, long long &count_cmp);

/*Maximal suffix of a string x: Let x = p.u, no prefix of u will be equal to a prefix ò v
Ex: x = u.v = ac.dcdcddc , no suffix of u equal to a prefix of v*/
/*If a maximal suffix of string x satifies that length of that maximal suffix equal of less
than length of x divides by 2, it' ll be short maximal suffix of x*/
/*Ex: 'ddc' is a short maximal suffix or example above*/
/*Reference: https://www-igm.univ-mlv.fr/~lecroq/string/node26.html
https://codebrowser.dev/glibc/glibc/string/str-two-way.h.html
https://www.slideserve.com/swain/two-way-algorithm */
/*Index for maximal suffix for <= */
int maxSuffix(std::string pat, int lengthPat, int &period, long long &count_cmp);

/*Maximal suffix for another way (>=)*/
int maxSuffixRev(std::string pat, int lengthPat, int &period, long long &count_cmp);

void TwoWayMatching(std::string pat, std::string txt, std::string outputDir, long long &count_cmp);

//Create Data:
void createData(int lengthPat, int lengthTxt, string fileDir, bool randTxt);