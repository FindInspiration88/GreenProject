#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "urlmon.lib")
#include<iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include "Pictire_Header.h"
#include "stdafx.h" 

using namespace Gdiplus;
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


	wstring SputnikUrl = L"https://maps.googleapis.com/maps/api/staticmap?center=#,*&zoom=17&size=512x512&maptype=satellite&key=AIzaSyBd7DMOTTilre43iTilXMGru34D15yHxO4";
	//скачиваем картинку-спутник
	wstring PalleteUrl = L"https://maps.googleapis.com/maps/api/staticmap?center=#,*&zoom=17&size=512x512&key=AIzaSyBd7DMOTTilre43iTilXMGru34D15yHxO4";
	//скачиваем карту-схему, на которой будем рисовать пиксели
	wstring MapUrl = L"https://maps.googleapis.com/maps/api/staticmap?center=#,*&zoom=17&size=512x512&style=feature:road|color:0x000000&style=feature:water|color:0x000000&style=feature:all|element:labels|visibility:off&key=AIzaSyBd7DMOTTilre43iTilXMGru34D15yHxO4";
	// закрашиваем дороги черным
	wstring PalleteSaveWay = L"C://Users//nikab//Desktop//GreenProject//pictures//pallete(#,*).jpg";
	picture sputnik;
	picture pallete;//конечная картинка озелененной местности на карте
	picture map;//карта черных дорог и водных участков

	double firstX, firstY, secondX, secondY;
	getCoordinate(firstX, firstY, secondX, secondY);
	for (double x = firstX; x <secondX; x += 0.001935)//координаты Екатеринбурга, шаг
		for (double y = firstY; y <secondY; y += 0.001935)
		{
			sputnik.Download(SputnikUrl, L"C://Users//nikab//Desktop//GreenProject//sputnik.jpg", x, y);
			sputnik.Translate(L"C://Users//nikab//Desktop//GreenProject//sputnik.jpg");

			pallete.Download(PalleteUrl, L"C://Users//nikab//Desktop//GreenProject//pallete.jpg", x, y);
			pallete.Translate(L"C://Users//nikab//Desktop//GreenProject//pallete.jpg");

			map.Download(MapUrl, L"C://Users//nikab//Desktop//GreenProject//maps.jpg", x, y);
			map.Translate(L"C://Users//nikab//Desktop//GreenProject//maps.jpg");
			for (int i = 0; i < 256 * 256; i++)
			{

				vector<int> SputnikColor = sputnik.getColor(i);//массив, в нулевой ячейке хранится x(Red от ргб), в первой ячейке y(G), в третьей z(B)
				vector<int> GreenColor = { 0, 255, 0 };
				vector<int> MapColor = map.getColor(i);


				if (sqrt((SputnikColor[0] * SputnikColor[0] - 0) + (SputnikColor[1] - 107)*(SputnikColor[1] - 107) + (SputnikColor[2] - 108)*(SputnikColor[2] - 108))<90
					&& sqrt((SputnikColor[0] * SputnikColor[0] - 0) + (SputnikColor[1] - 0)*(SputnikColor[1] - 0) + (SputnikColor[2] - 0)*(SputnikColor[2] - 0))>100
					&& sqrt((SputnikColor[0] * SputnikColor[0] - 0) + (SputnikColor[1] - 0)*(SputnikColor[1] - 0) + (SputnikColor[2] - 0)*(SputnikColor[2] - 0))>100
					&& sqrt((SputnikColor[0] - 255)*(SputnikColor[0] - 255) + (SputnikColor[1] - 255)*(SputnikColor[1] - 255) + (SputnikColor[2] - 255)*(SputnikColor[2] - 255))>100
					&& sqrt((SputnikColor[0] - 140)*(SputnikColor[0] - 140) + (SputnikColor[1] - 141)*(SputnikColor[1] - 141) + (SputnikColor[2] - 141)*(SputnikColor[2] - 141))>100
					&& MapColor[0] + MapColor[1] + MapColor[2] != 0)
					//точка (0;107;108) - узнать, попадает ли эта точка в круг с радиусом sqrt(90), с центром в данной точке
				{
					pallete.setColor(i, GreenColor);
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
			cout << x << " " << y << " ";
		}
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

