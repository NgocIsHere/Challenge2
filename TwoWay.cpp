#include "TwoWay.h"

using namespace std;

int Max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

/*Maximal suffix of a string x: Let x = p.u, no prefix of u will be equal to a prefix of v
Ex: x = u.v = ac.dcdcddc , no suffix of u equal to a prefix of v*/
/*If a maximal suffix of string x satifies that length of that maximal suffix equal of less
than length of x divides by 2, it' ll be short maximal suffix of x*/
/*Ex: 'ddc' is a short maximal suffix or example above*/
/*Reference: https://www-igm.univ-mlv.fr/~lecroq/string/node26.html
https://codebrowser.dev/glibc/glibc/string/str-two-way.h.html
https://www.slideserve.com/swain/two-way-algorithm */
/*Index for maximal suffix for <= */
int maxSuffix(string pat, int lengthPat, int &period)
{
	int ms, j, k;
	char m, n;

	ms = -1;
	j = 0;
	k = period = 1;
	while (j + k < lengthPat) {
		m = pat[j + k];
		n = pat[ms + k];
		if (m < n) {
			j += k;
			k = 1;
			period = j - ms;
		}
		else
		{
			if (m == n) {
				if (k != period)
					k++;
				else
				{
					j += period;
					k = 1;
				}
			}
			else {
				//a > b
				ms = j;
				j = ms + 1;
				k = period = 1;
			}
		}
	}

	return ms;
}

/*Maximal suffix for another way (>=)*/
int maxSuffixRev(string pat, int lengthPat, int &period)
{
	int ms, j, k;
	char m, n;

	ms = -1;
	j = 0;
	k = period = 1;
	while (j + k < lengthPat) {
		m = pat[j + k];
		n = pat[ms + k];
		if (m > n) {
			j += k;
			k = 1;
			period = j - ms;
		}
		else
		{
			if (m == n) {
				if (k != period)
					k++;
				else
				{
					j += period;
					k = 1;
				}
			}
			else {
				//a < b
				ms = j;
				j = ms + 1;
				k = period = 1;
			}
		}
	}

	return ms;
}

void TwoWayMatching(string pat, int patLength, string txt, int txtLength, string outputDir)
{
	fstream file;
	file.open(outputDir.c_str(), ios::out | ios::trunc);
	if (!file) {
		cout << "Error opening file" << endl;
		return;
	}
	int i;
	int j;
	int suffix, period; //Index of the maximal suffix and period of pattern string
	int memory; //Store the last period of pattern string to avoid scanning again
	int p, q; //Period by scanning to find maximal suffix in two ways

	//Preprocessing (critical factorization)
	i = maxSuffix(pat, pat.size(), p);
	j = maxSuffixRev(pat, pat.size(), q);
	if (i > j)
	{
		suffix = i;
		period = p;
	}
	else
	{
		suffix = j;
		period = q;
	}

	//Searching
	if (pat.substr(0, suffix + 1).compare(pat.substr(period, suffix + 1)) == 0)
	{
		/*The reference from glibc will add 1 to the suffix index, reference from
		univ-mlv.fr doesn't (which I reimplemented in C++)*/
		/*Entire pattern string is periodic*/
		j = 0; //Index to the current window of matched string txt
		memory = -1;
		while (j <= txtLength - patLength)
		{
			i = Max(suffix, memory) + 1; //Index of current character of pattern string
			while (i < patLength && pat[i] == txt[i + j])
				i++;
			if (i >= patLength) {
				/*Scan for matches in left half*/
				i = suffix;
				while (i > memory && pat[i] == txt[i + j])
					i--;
				if (i <= memory)
				{
					file << j << " " << j + patLength - 1 << endl;
					cout << "Pattern found at: " << j << endl;
				}
				j += period;
				memory = patLength - period - 1;
			}
			else {
				j += i - suffix;
				memory = -1;
			}
		}
	}
	else
	{
		/*The two halves of pattern string are distinct, no extra memory required, any mismatch
		results in maximal shift*/
		period = Max(suffix + 1, patLength - suffix - 1) + 1;
		j = 0;
		while (j <= txtLength - patLength) {
			i = suffix + 1;
			while (i < patLength && pat[i] == txt[i + j])
				i++;
			if (i >= patLength) {
				i = suffix;
				while (i >= 0 && pat[i] == txt[i + j])
					i--;
				if (i < 0)
				{
					file << j << " " << j + patLength - 1 << endl;
					cout << "Pattern found at: " << j << endl;
				}
				j += period;
			}
			else
				j += i - suffix;
		}
	}
}
