#include "stdafx.h"
#include "HWPenIme.h"

 
/**********************************************************************/
/*                                                                    */
/* UI_IsIMEMessage(message)                                            */
/*                                                                    */
/* Any UI window should not pass the IME messages to DefWindowProc.   */
/*                                                                    */
/**********************************************************************/
BOOL Helper_IsIMEMessage(UINT message)
{
    switch(message)
    {
	case WM_IME_STARTCOMPOSITION:
	case WM_IME_ENDCOMPOSITION:
	case WM_IME_COMPOSITION:
	case WM_IME_NOTIFY:
	case WM_IME_SETCONTEXT:
	case WM_IME_CONTROL:
	case WM_IME_COMPOSITIONFULL:
	case WM_IME_SELECT:
	case WM_IME_CHAR:
		return TRUE;
	default:
		return FALSE;
    }
}

//*****************************************************
//	工具接口：显示位图
//******************************************************
void Helper_DrawBMP(HDC hdc,RECT rc,UINT bmpID)
{
	HDC memdc=CreateCompatibleDC(hdc);
	HBITMAP hbkbmp=(HBITMAP)LoadBitmap(g_hInst,MAKEINTRESOURCE(bmpID));
	HBITMAP holdbmp=(HBITMAP) SelectObject(memdc,hbkbmp);
	BitBlt(hdc,rc.left,rc.top,rc.right,rc.bottom,memdc,0,0,SRCCOPY);
	SelectObject(memdc,holdbmp);
	DeleteObject(hbkbmp);
	DeleteDC(memdc);
}

void Helper_Trace(TCHAR * pszFormat,...)
{
	va_list args; 
	TCHAR buf[1024];
	memset(buf, 0, sizeof(buf));
	va_start( args, pszFormat );
	_vsntprintf(buf, 1024 - 1, pszFormat, args);
	va_end (args);
	//buf[sizeof(buf) - 1] = 0;
	OutputDebugString(buf);
}

void Helper_CenterWindow(HWND hWnd)
{
	RECT rc,screenrc;
	int x,y;
	SystemParametersInfo(SPI_GETWORKAREA,
		0,
		&screenrc,
		0);
	GetWindowRect(hWnd,&rc);
	x=(screenrc.right-rc.right+rc.left)/2;
	y=(screenrc.bottom-rc.bottom+rc.top)/2;
	SetWindowPos(hWnd,NULL,x,y,0,0,SWP_NOSIZE|SWP_NOZORDER);
}