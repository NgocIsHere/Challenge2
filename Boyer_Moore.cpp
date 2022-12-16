#include<iostream>
#include<string>
using namespace std;

void FindLastOccur(string pat,int L[],int size,int &comp)//Vị trí xuất hiện cuối cùng của mỗi kí tự trong chuỗi pat
{
	for (int i = 0;comp++ && i < 255; i++)// 255 là số kí tự trong bảng mã ascii
		L[i] = -1;
	for (int i = 0;comp++ && i < size; i++)
	{
		L[(int)pat[i]] = i;
	}
}

int Boyer_Moore_Search(string pat, string str)
{
	int comp = 0;
	int m = pat.size();
	int LastOccur[255];

	FindLastOccur(pat, LastOccur, m,comp);

	int n = str.size();
	int s = 0;
	int time = 0;//Đếm số lần xuất hiện chuỗi con

	while (comp++ && s + m <= n)
	{
		int j = m - 1;

		while ((comp++ && j >= 0) && (comp++ && pat[j] == str[s + j]))
			j--;

		if (comp++ && j < 0)
		{
			cout << "Chuoi con xuat hien tai vi tri tu s = " << s << endl;
			time++;
			if (comp++ && s + m < n)
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
	return comp;
}