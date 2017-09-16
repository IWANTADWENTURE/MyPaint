#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

class PictureSaver {
private:
	bool FileExists(const char *fname)
	{
		return  ifstream(fname).fail();
	}
	HBITMAP MakeClientRectSnapshot(RECT& ClientRect, HWND hwnd) {
		HDC hDC = GetDC(hwnd);
		RECT rcClientRect;
		BOOL bOk = FALSE;
		HBITMAP hImage = NULL;

		GetClientRect(hwnd, &rcClientRect);
		ClientRect = rcClientRect;
		if ((hImage = CreateCompatibleBitmap(hDC,
			rcClientRect.right, rcClientRect.bottom)) != NULL) {

			HDC hMemDC;
			HBITMAP hDCBmp;

			if ((hMemDC = CreateCompatibleDC(hDC)) != NULL) {
				hDCBmp = (HBITMAP)SelectObject(hMemDC, hImage);

				BitBlt(hMemDC, 0, 0, rcClientRect.right, rcClientRect.bottom,
					hDC, 0, 0, SRCCOPY);

				SelectObject(hMemDC, hDCBmp);
				DeleteDC(hMemDC);
				bOk = TRUE;
			}
		}
		ReleaseDC(hwnd, hDC);
		if (!bOk) {
			if (hImage) {
				DeleteObject(hImage);
				hImage = NULL;
			}
		}
		return hImage;
	}
public:
	void SavePicture(HWND hwnd, CHAR* SavePath) {
		HBITMAP hSnapshot;
		RECT ClientRect;
		if ((hSnapshot = MakeClientRectSnapshot(ClientRect, hwnd)) != NULL) {
			UINT uiBytesPerRow = 3 * ClientRect.right; // RGB takes 24 bits
			UINT uiRemainderForPadding;

			if ((uiRemainderForPadding = uiBytesPerRow % sizeof(DWORD)) > 0) {
				uiBytesPerRow += (sizeof(DWORD) - uiRemainderForPadding);
			}

			UINT uiBytesPerAllRows = uiBytesPerRow * ClientRect.bottom;
			PBYTE pDataBits;

			if ((pDataBits = new BYTE[uiBytesPerAllRows]) != NULL) {
				BITMAPINFOHEADER bmi = { 0 };
				BITMAPFILEHEADER bmf = { 0 };
				HDC hDC = GetDC(hwnd);

				// Prepare to get the data out of HBITMAP:
				bmi.biSize = sizeof(bmi);
				bmi.biPlanes = 1;
				bmi.biBitCount = 24;
				bmi.biHeight = ClientRect.bottom;
				bmi.biWidth = ClientRect.right;

				// Get it:
				GetDIBits(hDC, hSnapshot, 0, ClientRect.bottom,
					pDataBits, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);

				ReleaseDC(hwnd, hDC);

				// Fill the file header:
				bmf.bfOffBits = sizeof(bmf) + sizeof(bmi);
				bmf.bfSize = bmf.bfOffBits + uiBytesPerAllRows;
				bmf.bfType = 0x4D42;

				// Writing:
				FILE* pFile;
				if (FileExists(SavePath)) {
					remove(SavePath);
				}
				fopen_s(&pFile, SavePath, "wb");
				if (pFile != NULL) {
					fwrite(&bmf, sizeof(bmf), 1, pFile);
					fwrite(&bmi, sizeof(bmi), 1, pFile);
					fwrite(pDataBits, sizeof(BYTE), uiBytesPerAllRows, pFile);
					fclose(pFile);
				}
				delete[] pDataBits;
				ReleaseCapture();
			}
			DeleteObject(hSnapshot);
		}
	}
	
protected:
};