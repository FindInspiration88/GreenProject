#include "stdafx.h"
#include <windows.h> 
#include <stdio.h>
#include <gdiplus.h> 
#include<iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#pragma comment (lib,"Gdiplus.lib") 
using namespace Gdiplus;
using namespace std;



int main()
{	
	vector<vector<vector<int> > > arr;
	vector<vector<int> > NewArr;
	vector <int> NewNewArr(255);
	for (int i = 0; i < 255; i++)
		NewArr.push_back(NewNewArr);
	for (int i = 0; i < 255; i++)
		arr.push_back(NewArr);
	int   R=0, G=0, B=0, co=0;
	UINT sum = 0, count = 0;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	Gdiplus::Bitmap* image = new Gdiplus::Bitmap(L"C://Dev-cpp//green.png");
	UINT SizeCol = image->GetWidth();
	UINT SizeRow = image->GetHeight();
	Gdiplus::Rect mRect(0, 0, SizeCol, SizeRow);
	Gdiplus::BitmapData bd;
	image->LockBits(&mRect, ImageLockModeRead | ImageLockModeWrite, image->GetPixelFormat(), &bd);
	BYTE* WholeCurrRastData = (BYTE*)bd.Scan0;
	image->UnlockBits(&bd);
	std::ifstream fin("C://Dev-cpp//output.txt");
	while (!fin.eof())
	{
		fin >> R >> G >> B>>count;
		arr[R][G][B] = count;
		sum += count;
		co++;
	}
	sum /= co;

	for (int i = 0; i < 3 * SizeCol*SizeRow - 3; i += 3)
	{
		R = (int)WholeCurrRastData[i];
		G = (int)WholeCurrRastData[i + 1];
		B = (int)WholeCurrRastData[i + 2];
		arr[R][G][B]++;
		R = 0;
		G = 0;
		B = 0;
	}
			
	std::ofstream fout("C://Dev-cpp//output.txt");
	for (int i = 0; i < 255; i++)
		for (int j = 0; j < 255; j++)
			for (int k = 0; k < 255; k++)
				if (arr[i][j][k]>sum)
					fout<<i<<" "<<j<<" "<<k<<" "<< arr[i][j][k]<<endl;
	
	Gdiplus::GdiplusShutdown(gdiplusToken);
	system("pause");
	return 0;
}


