#include <windows.h>
#include <gdiplus.h>
#include "resource1.h"

using namespace Gdiplus;

VOID OnPaint(HDC hdc)
{
	Graphics graphics(hdc);

	Pen      pen(Color(255, 0, 0, 255));
	graphics.DrawLine(&pen, 700, 0, 800, 100);	

	// Create a Pen object.
	Pen blackPen(Color(255, 0, 0, 0), 3);
	SolidBrush solidBrush(Color(255, 255, 0, 0));

	// Create two Point objects that define the line.
	Point point1(800, 100);
	Point point2(900, 100);

	graphics.FillEllipse(&solidBrush, 800, 200, 60, 100);
	// Draw the line.
	graphics.DrawLine(&blackPen, point1, point2);

	Image image(L"demo.jpg");
	UINT height = image.GetHeight();
	UINT width = image.GetWidth();
	//graphics.DrawImage(&image, 300, 0, image.GetWidth()/10, image.GetHeight()/10);
	TextureBrush tBrush(&image);
	//x_ = ax + cy + e;
	//y_ = bx + dy + f;
	Status stat = tBrush.SetTransform(&Matrix(0.1f, 0.0f, 0.0f, 0.1f, 300.0f, 0.0f));
	stat = graphics.FillRectangle(&tBrush,Rect(300, 0, (width/10), (height/10)));

	PointF point3(700.0f, 0.0f);
	SolidBrush solidBrush2(Color(255, 255, 0, 0));
	FontFamily  fontFamily(L"Times New Roman");
	Font font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	graphics.DrawString(L"Demo", -1, &font,  point3, &solidBrush2);

	Point pts[] = {\
		Point(0, 0), 
		Point(100, 0), 
		Point(100, 100)};

	Color cols[] = {\
		Color(255, 255, 0, 0),  // red
		Color(255, 0, 255, 0),  // green
		Color(255, 0, 0, 0)};   // black

	INT count = 3;
	PathGradientBrush pthGrBrush(pts, 3);
	pthGrBrush.SetSurroundColors(cols, &count);

	// Fill an area with the path gradient brush (no transformation).
	graphics.FillRectangle(&pthGrBrush, 0, 0, 200, 200);

	// Set the transformation for the brush (rotate, then translate).
	Matrix matrix(1.0f, 0.0f, 0.0f, 1.0f, 100.0f, 100.0f);
	pthGrBrush.SetTransform(&matrix);

	// Fill the same area with the transformed path gradient brush.
	graphics.FillRectangle(&pthGrBrush, 0, 0, 200, 200);  

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,  WPARAM wParam, LPARAM lParam)
{
   HDC          hdc;
   PAINTSTRUCT  ps;

   int x = 10;           // horizontal coordinate of cursor 
   int y = 400;           // vertical coordinate of cursor 
   int nWidth = 2;      // width of cursor 
   int nHeight = 10;     // height of cursor 
   char *lpszChar;  // pointer to character 

   switch(message)
   {
   case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
	  TextOut( hdc, 10, 300, TEXT("Hello, Windows!"), 15);
      OnPaint(hdc);
      EndPaint(hWnd, &ps);
      return 0;
   case WM_DESTROY:
      PostQuitMessage(0);
	  return 0;
   case WM_SETFOCUS: 
	   {
		   //HBITMAP hCaret = LoadBitmap(g_hInstance, MAKEINTRESOURCE(120));
		   //HBITMAP hCaret = CreateBitmap(20, 20, 0, 0, cols);
		   //SetCaretBlinkTime(500);
		   // Create a solid black caret. 
		   CreateCaret(hWnd, NULL, nWidth, nHeight); 
		   // Adjust the caret position, in client coordinates. 
		   SetCaretPos(x, y); 
		   // Display the caret. 
		   ShowCaret(hWnd); 
	   }
	   return 0; 
   case WM_KILLFOCUS: 
	   // The window is losing the keyboard focus, so destroy the caret.
	   DestroyCaret(); 
	   return 0; 
   case WM_CHAR: 
	   switch (wParam) 
	   { 
	   case 0x08: 
		   // Process a backspace. 
		   break; 
	   case 0x09: 
		   // Process a tab.  
		   break; 
	   case 0x0D: 
		   // Process a carriage return. 
		   ShowCaret(hWnd); 
		   break; 
	   case 0x1B: 
		   // Process an escape.
		   break; 
	   case 0x0A: 
		   // Process a linefeed. 
		   break; 
	   default: 
		   CHAR ch = 0;
		   WCHAR wch = 0;
		   // Hide the caret. 
		   HideCaret(hWnd);
		   // Draw the character on the screen. 
		   hdc = GetDC(hWnd); 
		   SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT)); 
		   ch = LOBYTE(wParam);
		   lpszChar = &ch;
		   MultiByteToWideChar(CP_ACP, 0, lpszChar, 2, &wch, 1);
		   TextOut(hdc, x, y, (LPCTSTR)&wch, 1); 
		   ReleaseDC(hWnd, hdc); 
		   // Display the caret. 
		   while (ShowCaret(hWnd) != TRUE); 
		   break; 
	   } 
	   return 0; 
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
} // WndProc

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wndClass.style          = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc    = WndProc;
	wndClass.cbClsExtra     = 0;
	wndClass.cbWndExtra     = 0;
	wndClass.hInstance      = hInstance;
	wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU1);
	wndClass.lpszClassName  = TEXT("GettingStarted");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(
		TEXT("GettingStarted"),   // window class name
		TEXT("Getting Started"),  // window caption
		WS_OVERLAPPEDWINDOW,      // window style
		CW_USEDEFAULT,            // initial x position
		CW_USEDEFAULT,            // initial y position
		CW_USEDEFAULT,            // initial x size
		CW_USEDEFAULT,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                // program instance handle
		NULL);                    // creation parameters

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}  // WinMain

