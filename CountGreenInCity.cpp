#include "stdafx.h"
#include <windows.h> 
#include <stdio.h>
#include <gdiplus.h> 
#include<iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#pragma comment (lib,"Gdiplus.lib") 
using namespace Gdiplus;
using namespace std;

void MakeArrayOfPixeles(WCHAR* way, BYTE*&WholeCurrRastData)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	Gdiplus::Bitmap* image = new Gdiplus::Bitmap(way);
	UINT SizeCol = image->GetWidth();
	UINT SizeRow = image->GetHeight();
	Gdiplus::Rect mRect(0, 0, SizeCol, SizeRow);
	Gdiplus::BitmapData bd;
	image->LockBits(&mRect, ImageLockModeRead | ImageLockModeWrite, image->GetPixelFormat(), &bd);
	WholeCurrRastData = (BYTE*)bd.Scan0;
	image->UnlockBits(&bd);
	Gdiplus::GdiplusShutdown(gdiplusToken);
	//return SizeCol*SizeRow;
}

int main()
{
	vector<vector<vector<int> > > arr;
	vector<vector<int> > NewArr;
	vector <int> NewNewArr(255);
	for (int i = 0; i < 255; i++)
		NewArr.push_back(NewNewArr);
	for (int i = 0; i < 255; i++)
		arr.push_back(NewArr);
	int   R = 0, G = 0, B = 0, co = 0;
	UINT sum = 0, count = 0;
	


	BYTE* WholeCurrRastDataOfSputnik;
	BYTE* WholeCurrRastDataOfMap;

	//UINT Area = 
	MakeArrayOfPixeles(L"C://Dev-cpp//map.jpg", WholeCurrRastDataOfMap);
	MakeArrayOfPixeles(L"C://Dev-cpp//sputnik.jpg", WholeCurrRastDataOfSputnik);
	
	cout << (int)WholeCurrRastDataOfSputnik[1];
	//cout << WholeCurrRastDataOfMap[0];
	std::ifstream fin("C://Dev-cpp//output.txt");
	while (!fin.eof())
	{
		fin >> R >> G >> B >> count;
		arr[R][G][B] = count;
		sum += count;
		co++;
	}
	sum /= co;
	/*for (int i = 0; i < 3 * Area - 3; i += 3)
	{
		if ((int)WholeCurrRastDataOfMap[i] == 206 && (int)WholeCurrRastDataOfMap[i + 1] == 229 && (int)WholeCurrRastDataOfMap[i + 2] == 212)
		{
			arr[(int)WholeCurrRastDataOfSputnik[i]][(int)WholeCurrRastDataOfSputnik[i + 1]][(int)WholeCurrRastDataOfSputnik[i + 2]]++;
			cout << (int)WholeCurrRastDataOfSputnik[i] << " " << (int)WholeCurrRastDataOfSputnik[i + 1] << " " << (int)WholeCurrRastDataOfSputnik[i + 2] << endl;
		}

	}*/

	std::ofstream fout("C://Dev-cpp//output.txt");
	for (int i = 0; i < 255; i++)
		for (int j = 0; j < 255; j++)
			for (int k = 0; k < 255; k++)
				if (arr[i][j][k]>sum)
					fout << i << " " << j << " " << k << " " << arr[i][j][k] << endl;
	
	system("pause");
	return 0;
}
