#include "Header.h"

void FindLastOccur(string pat,int L[],int size,long long &cnt_cmp)//Vị trí xuất hiện cuối cùng của mỗi kí tự trong chuỗi pat
{
	for (int i = 0;cnt_cmp++ && i < 255; i++)// 255 là số kí tự trong bảng mã ascii
		L[i] = -1;
	for (int i = 0;cnt_cmp++ && i < size; i++)
	{
		L[(int)pat[i]] = i;
	}
}

vector<pair<int, int>> Boyer_Moore_Search(string pat, string str, long long &cnt_cmp)
{
	vector<pair<int, int>> index;
	int m = pat.size();
	int LastOccur[255];

	FindLastOccur(pat, LastOccur, m,cnt_cmp);
	static long long temp;
	int n = str.size();
	int s = 0;
	int time = 0;//Đếm số lần xuất hiện chuỗi con

	while (cnt_cmp++ && s + m <= n)
	{
		int j = m - 1;

		while ((cnt_cmp++ && j >= 0) && (cnt_cmp++ && pat[j] == str[s + j]))
			j--;

		if (cnt_cmp++ && j < 0)
		{
			temp = cnt_cmp;
			cout << "Chuoi con xuat hien tai vi tri tu s = " << s << endl;
			index.push_back(make_pair(s, s + m - 1));
			time++;
			if (cnt_cmp++ && s + m < n)
				s = s + m - LastOccur[(int)str[s + m]];
			else
				s = s + 1;
		}
		else
		{
			s = s + max(1, j - LastOccur[(int)str[s + j]]);
		}
	}
	if (time == 0)
	{
		cout << "Khong ton tai chuoi con trong chuoi ban dau. \n";
	}
	cnt_cmp = temp;
	return index;
}
