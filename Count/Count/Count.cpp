#include "stdafx.h"
#include <windows.h> 
#include <stdio.h>
#include <gdiplus.h> //библиотека для обработки изображения
#include<iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <math.h>
#include <assert.h>
#include <urlmon.h> //import URLDownLoadToFile
#include <string>
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "urlmon.lib")
using namespace Gdiplus;
using namespace std;

class Picture//работа с изображением, структура класса
{
private:
	BYTE* WholeCurrRastData=new BYTE[256*256*3];//массив пикселей(int)
	BYTE Mask[256 * 256 * 3];
	Gdiplus::Bitmap* image; //картинка, как объект
	UINT SizeCol;		//длина
	UINT SizeRow;		//ширина
	wstring Url;
	wchar_t* FileName;
	void translate()
	{
		image = new Gdiplus::Bitmap(FileName);//указываем файл (переход пикселей в байты)
		SizeCol = image->GetWidth();
		SizeRow = image->GetHeight();
		Gdiplus::Rect mRect(0, 0, SizeCol, SizeRow);
		Gdiplus::BitmapData bd;
		image->LockBits(&mRect, ImageLockModeRead | ImageLockModeWrite, image->GetPixelFormat(), &bd);
		WholeCurrRastData = (BYTE*)bd.Scan0;
		image->UnlockBits(&bd);
	}
public:
	Picture(wstring getUrl, wchar_t* getWay)
	{
		Url = getUrl;
		FileName = getWay;
	}
	void Download(double x, double y)//откуда-куда(кодировка юникод)
	{
		wstring strURL = Url.substr(0, Url.find(L"#")) + to_wstring(x) + L"," + to_wstring(y) + Url.substr(Url.find(L"*") + 1, Url.length() - Url.find(L"*") - 1);
		assert(!strURL.empty());
		wchar_t* chrURL = &strURL[0];
		URLDownloadToFile(0, chrURL, FileName, 0, 0);	//скачивание картинки
		translate();
	}
	vector<int> getColor(UINT i)//получаем массив rgb с помощью обращения к getColor
	{
		vector<int> Color;
		for (int j = 0; j < 3; j++)
		{
 			Color.push_back((int)WholeCurrRastData[3 * i + j]);
		}
		return Color;
	}
	void Save(wstring fname, double x, double y)
	{
		fname = fname.substr(0, fname.find(L"#")) + to_wstring(x) + L"," + to_wstring(y) + fname.substr(fname.find(L"*") + 1, fname.length() - fname.find(L"*") - 1);
		assert(!fname.empty());
		wchar_t* Newfname = &fname[0];
		CLSID jpgClsid;
		CLSIDFromString(L"{557cf401-1a04-11d3-9a73-0000f81ef32e}", &jpgClsid);
		image->Save(Newfname, &jpgClsid,NULL);
	}
	void Draw()
	{
		HDC hdc = CreateCompatibleDC(NULL);
		Gdiplus::Graphics graphics(hdc);
		BitmapData bitmapData;
		bitmapData.Width = 256,
			bitmapData.Height = 256,
			bitmapData.Stride = 2 * bitmapData.Width;
		bitmapData.Scan0 = (VOID*)Mask;
		bitmapData.Reserved = NULL;
		graphics.DrawImage(image, 0, 0);
		Rect rect(0, 0, 255, 255);
		image->LockBits(&rect, ImageLockModeWrite | ImageLockModeUserInputBuf, image->GetPixelFormat(), &bitmapData);
		image->UnlockBits(&bitmapData);
		graphics.DrawImage(image, 0, 0);
	}
	void setColor(int i, vector<int>Color)
	{
		for (int j = 0; j < 3; j++)
		{
			Mask[3*i + j] =(BYTE)Color[j];
		}
	}
	void Delete()
	{
		delete[] image;
	}

};
bool SearchParks(vector<int>&Color)
{
	if (!Color.empty() && Color[0] + Color[1] + Color[2] == 0)
		return true;
	else
		return false;
}
void showVector(vector<int> Color)
{
	for (int i = 0; i < Color.size(); i++)
	{
		cout << Color[i] << " ";
	}
	system("pause");
}
void findFirstSecond(double &first, double &second)
{
	double t;
	if (first > second)
	{
		t = first;
		first = second;
		second = t;
	}
}
void getCoordinate(double& firstX, double& firstY, double& secondX, double& secondY)
{
	cin >> firstX >> firstY >> secondX >> secondY;
	findFirstSecond(firstX, secondX);
	findFirstSecond(firstY, secondY);
}

int main()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wstring PalleteSaveWay = L"pallete(#,*).jpg";
	Picture map(L"https://maps.googleapis.com/maps/api/staticmap?center=#,*&zoom=17&size=512x512&style=feature:road|color:0x000000&style=feature:water|color:0x000000&style=feature:all|element:labels|visibility:off&key=AIzaSyBd7DMOTTilre43iTilXMGru34D15yHxO4&key=AIzaSyBd7DMOTTilre43iTilXMGru34D15yHxO4", L"map.jpg");//объекты
	Picture sputnik(L"https://maps.googleapis.com/maps/api/staticmap?center=#,*&zoom=17&size=512x512&maptype=satellite&key=AIzaSyBd7DMOTTilre43iTilXMGru34D15yHxO4", L"sputnik.jpg");
	Picture pallete(L"https://maps.googleapis.com/maps/api/staticmap?center=#,*&zoom=17&size=512x512&key=AIzaSyBd7DMOTTilre43iTilXMGru34D15yHxO4", L"pallete.jpg");

	int ch;
	double firstX= 56.818973, firstY=60.579797, secondX= 56.840856, secondY= 60.640565;
	cin >> ch;
	if (ch==1)
		getCoordinate(firstX, firstY, secondX, secondY);

	for (double x =firstX; x < secondX; x += 0.001935)//координаты Екатеринбурга, шаг
		for (double y = firstY; y < secondY; y += 0.001935)
		{
			sputnik.Download(x, y);
			map.Download(x, y);
			pallete.Download(x, y);
			for (int i = 0; i < 256 * 256; i++)
			{
				vector<int> SputnikColor = sputnik.getColor(i);
				vector<int> DrawColor = { 0, 255, 0 };
				vector<int> MapColor = map.getColor(i);
				if (sqrt((SputnikColor[0] - 0)*(SputnikColor[0] - 0) +(SputnikColor[1]-107)*(SputnikColor[1] - 107) +(SputnikColor[2]-108)*(SputnikColor[2] - 108))<90
					&&MapColor[0]+MapColor[1]+MapColor[2]!=0)
				{
					pallete.setColor(i, DrawColor);
				}
				else
				{
					pallete.setColor(i, pallete.getColor(i));
				}
			}
			pallete.Draw();
			pallete.Save(PalleteSaveWay, 7, 8);
			sputnik.Delete();
			map.Delete();
			pallete.Delete();
		}

	Gdiplus::GdiplusShutdown(gdiplusToken);
}