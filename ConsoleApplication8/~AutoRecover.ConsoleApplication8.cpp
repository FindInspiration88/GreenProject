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

void MakeArrayOfPixeles(string str, int*&array)
{
	Gdiplus::Bitmap* sputnik = new Gdiplus::Bitmap(L"C://Dev-cpp//sputnik.jpg");
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
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	
	Bitmap* map = new Gdiplus::Bitmap(L"C://Dev-cpp//map.jpg");

	UINT SizeColOfSputnik = sputnik->GetWidth();
	UINT SizeRowOfSputnik = sputnik->GetHeight();
	UINT SizeColOfMap = map->GetWidth();
	UINT SizeRowOfMap = map->GetHeight();

	Gdiplus::Rect mRectOfSputnik(0, 0, SizeColOfSputnik, SizeRowOfSputnik);


	Gdiplus::BitmapData bdOfSputnik;
	Gdiplus::BitmapData bdOfMap;

	sputnik->LockBits(&mRect, ImageLockModeRead | ImageLockModeWrite, sputnik->GetPixelFormat(), &bdOfSputnik);
	map->LockBits(&mRect, ImageLockModeRead | ImageLockModeWrite, map->GetPixelFormat(), &bdOfMap);

	BYTE* WholeCurrRastDataOfSputnik = (BYTE*)bdOfSputnik.Scan0;
	BYTE* WholeCurrRastDataOfMap = (BYTE*)bdOfMap.Scan0;

	sputnik->UnlockBits(&bdOfSputnik);
	map->UnlockBits(&bdOfMap);

	std::ifstream fin("C://Dev-cpp//output.txt");
	while (!fin.eof())
	{
		fin >> R >> G >> B >> count;
		arr[R][G][B] = count;
		sum += count;
		co++;
	}
	sum /= co;

	for (int i = 0; i < 3 * SizeCol*SizeRow - 3; i += 3)
	{
		R = (int)WholeCurrRastDataOfMap[i];
		G = (int)WholeCurrRastDataOfMap[i+1];
		B = (int)WholeCurrRastDataOfMap[i+2];
		if (R==206&&  G==229 &&B== 212)
			arr[(int)WholeCurrRastDataOfSputnik[i]][(int)WholeCurrRastDataOfSputnik[i + 1]][(int)WholeCurrRastDataOfSputnik[i + 2]]++;
		R = 0;
		G = 0;
		B = 0;
	}

	std::ofstream fout("C://Dev-cpp//output.txt");
	for (int i = 0; i < 255; i++)
		for (int j = 0; j < 255; j++)
			for (int k = 0; k < 255; k++)
				if (arr[i][j][k]>sum)
					fout << i << " " << j << " " << k << " " << arr[i][j][k] << endl;
	Gdiplus::GdiplusShutdown(gdiplusToken);
	system("pause");
	return 0;
}
