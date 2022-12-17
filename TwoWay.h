#pragma once
#include <iostream>
#include <fstream>
#include <string>

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

void TwoWayMatching(std::string pat, int patLength, std::string txt, int txtLength, std::string outputDir, long long &count_cmp);
