#include "Header.h"

int Max(int a, int b, long long &count_cmp)
{
	if (++count_cmp && a > b)
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
int maxSuffix(string pat, int lengthPat, int &period, long long &count_cmp)
{
	int ms, j, k;
	char m, n;

	ms = -1;
	j = 0;
	k = period = 1;
	while (++count_cmp && j + k < lengthPat) {
		m = pat[j + k];
		n = pat[ms + k];
		if (++count_cmp && m < n) {
			j += k;
			k = 1;
			period = j - ms;
		}
		else
		{
			if (++count_cmp && m == n) {
				if (++count_cmp && k != period)
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
int maxSuffixRev(string pat, int lengthPat, int &period, long long &count_cmp)
{
	int ms, j, k;
	char m, n;

	ms = -1;
	j = 0;
	k = period = 1;
	while (++count_cmp && j + k < lengthPat) {
		m = pat[j + k];
		n = pat[ms + k];
		if (++count_cmp && m > n) {
			j += k;
			k = 1;
			period = j - ms;
		}
		else
		{
			if (++count_cmp && m == n) {
				if (++count_cmp && k != period)
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

void TwoWayMatching(string pat, string txt, string outputDir, long long &count_cmp)
{
	count_cmp = 0;
	vector<long long>total_cmp;/*Count of comparisons each time the pattern (needle) met
	in the compared (haystack) string*/
	int patLength = pat.length();
	int txtLength = txt.length();
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
	i = maxSuffix(pat, pat.size(), p, count_cmp);
	j = maxSuffixRev(pat, pat.size(), q, count_cmp);
	if (++count_cmp && i > j)
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
	if (++count_cmp && pat.substr(0, suffix + 1).compare(pat.substr(period, suffix + 1)) == 0)
	{
		/*The reference from glibc will add 1 to the suffix index, reference from
		univ-mlv.fr doesn't (which I reimplemented in C++)*/
		/*Entire pattern string is periodic*/
		j = 0; //Index to the current window of matched string txt
		memory = -1;
		while (++count_cmp && j <= txtLength - patLength)
		{
			i = Max(suffix, memory, count_cmp) + 1; //Index of current character of pattern string
			while (++count_cmp && i < patLength && pat[i] == txt[i + j])
				i++;
			if (++count_cmp && i >= patLength) {
				/*Scan for matches in left half*/
				i = suffix;
				while (++count_cmp && i > memory && pat[i] == txt[i + j])
					i--;
				if (++count_cmp && i <= memory)
				{
					file << j << " " << j + patLength - 1 << endl;
					total_cmp.push_back(count_cmp);
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
		period = Max(suffix + 1, patLength - suffix - 1, count_cmp) + 1;
		j = 0;
		while (++count_cmp && j <= txtLength - patLength) {
			i = suffix + 1;
			while (++count_cmp && i < patLength && pat[i] == txt[i + j])
				i++;
			if (++count_cmp && i >= patLength) {
				i = suffix;
				while (++count_cmp && i >= 0 && pat[i] == txt[i + j])
					i--;
				if (i < 0)
				{
					file << j << " " << j + patLength - 1 << endl;
					total_cmp.push_back(count_cmp);
				}
				j += period;
			}
			else
				j += i - suffix;
		}
	}
	file.close();
	//If the total_cmp vector is not empty(pattern met at least once), change to the comparison of the first instance
	if (!total_cmp.empty())
		count_cmp = total_cmp[0];
	
}
