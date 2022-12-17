#include "Header.h"
void createData(int lengthPat, int lengthTxt, string fileDir, bool randTxt)
{
	/*Ham tao file (neu file chua ton tai) chua 2 dong chuoi doi sanh 
	va duoc doi sanh cach nhau boi ky tu xuong dong */
	/*randTxt = true neu muon chuoi duoc doi sanh la ngau nhien (co the khong chua chuoi doi sanh)*/
	/*Luu y: lengthPat <= lengthTxt */
	if (lengthPat > lengthTxt)
	{
		std::cout << "Invalid pattern length"<<endl;
		return;
	}

	fstream file;
	file.open(fileDir.c_str(), ios::out | ios::trunc);
	if (!file) {
		cout << "Error opening file" << endl;
		return;
	}

	srand(time(NULL));
	string pattern = "";
	for (int i = 0; i < lengthPat; i++)
	{
		//Generate random character from '0' to 'z' in ASCII table
		pattern += '0' + rand() % 78;
	}

	//Ghi chuoi doi sanh vao file

	file << pattern; file << endl;
	if (!randTxt)
	{
		//Tao chuoi duoc doi sanh voi so lan xuat hien chuoi doi sanh trong no ngau nhien
		int maxAppearance = lengthTxt / lengthPat;
		int noOfAppearance = rand() % maxAppearance + 1;
		string st;
		int count = lengthTxt;
		int i = 0;
		while (count >= lengthPat && i < noOfAppearance)
		{
			st = "";
			int l = rand() % (count - lengthPat) + 0;
			
			for (int j = 0; j < l; j++)
			{
				st += '0' + rand() % 78;
			}
			file << st << pattern;
			count = count - (l + lengthPat);
			i++;
		}

		//Them cac ky tu cuoi vao chuoi duoc doi sanh
		st = "";
		for (int i = 0; i < count; i++)
		{
			st += '0' + rand() % 78;
		}
		file << st << endl;
	}
	else //randTxt == true
	{
		string st = "";
		for (int i = 0; i < lengthTxt; i++)
		{
			st += '0' + rand() % 78;
		}
		file << st << endl;
	}

	//Dong file
	file.close();
}
/*
int main()
{
	long long count_cmp;
	int s[7] = { 1, 5, 10, 100, 200, 500, 1000};
	for (int i = 0 ; i < 5; i++)
		for (int j = 0; j < 7; j++)
		{
			if (s[i] * 100 > s[j] * 10)
			{
				cout << "Pattern string size: " << s[i] * 100 << endl;
				cout << "Matched string size: "<< s[j] * 10 << endl;
				createData(s[j] * 10, s[i] * 100, "test.txt", false);
				ifstream readfile;
	            readfile.open("test.txt");
				string pat, txt;
				getline(readfile, pat); getline(readfile, txt);
				cout<<"Actual size of pattern string: "<<pat.size()<<" | Actual size of matched string: "<<txt.size()<<endl;

			}
				
		}

	system("pause");
	return 1;
}
*/