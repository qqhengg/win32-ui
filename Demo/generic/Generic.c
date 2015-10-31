/********************************************************************\
*  generic.c: Source code for generic                                *
*                                                                    *
*  Comments: Generic Application                                     *
*                                                                    *
*  Functions:                                                        *
*     WinMain      - Application entry point                         *
*     MainWndProc  - main window procedure                           *
*     AboutDlgProc - dialog procedure for About dialog               *
*                                                                    *
*                                                                    *
\********************************************************************/

/*********************  Header Files  *********************/

#include <windows.h>
#include "generic.h"
#include "resource.h"

HBITMAP hBitmap;
HICON   hIcon;
HCURSOR hCurs;     

/*********************  Prototypes  ***********************/

LRESULT CALLBACK MainWndProc( HWND, UINT, WPARAM, LPARAM );
INT_PTR CALLBACK AboutDlgProc( HWND, UINT, WPARAM, LPARAM );

/*******************  Global Variables ********************/

HINSTANCE ghInstance;

/********************************************************************\
*  Function: int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)  *
*                                                                    *
*   Purpose: Initializes Application                                 *
*                                                                    *
*  Comments: Register window class, create and display the main      *
*            window, and enter message loop.                         *
*                                                                    *
*                                                                    *
\********************************************************************/

int CALLBACK WinMain( HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdLine,
					 int nCmdShow )
{
	WNDCLASS wc;
	MSG msg;
	HWND hWnd;
	HWND hlabel;
	BOOL bRet;

	UINT error = 0;
	hCurs = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	if (hCurs == NULL)
	{
		error = GetLastError();
	}
	hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	if (hIcon == NULL)
	{
		error = GetLastError();
	}
	hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	if (hBitmap == NULL)
	{
		error = GetLastError();
	}

	if( !hPrevInstance )
	{
		wc.lpszClassName = TEXT("GenericAppClass");
		wc.lpfnWndProc = MainWndProc;
		wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
		wc.hCursor = LoadCursor( NULL, IDC_ARROW );
		wc.hbrBackground = (HBRUSH)( COLOR_WINDOW+1 );
		wc.lpszMenuName = TEXT("GenericAppMenu");
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;

		RegisterClass( &wc );
	}

	ghInstance = hInstance;

	hWnd = CreateWindow( TEXT("GenericAppClass"),
		TEXT("Generic Application"),
		WS_OVERLAPPEDWINDOW|WS_HSCROLL|WS_VSCROLL,
		0,
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
		);


	hlabel = CreateWindow(TEXT("static"), 
		TEXT("x:"), 
		WS_CHILD | WS_VISIBLE,
		10,
		50,
		20,
		20,
		hWnd,
		NULL,
		NULL,
		NULL);


	ShowWindow( hWnd, nCmdShow );

	while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0 ) 
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit
		}
		else
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}

	return (int)msg.wParam;
}

/********************************************************************\
* Function: LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM) *
*                                                                    *
*  Purpose: Processes Application Messages                           *
*                                                                    *
* Comments: The following messages are processed                     *
*                                                                    *
*           WM_PAINT                                                 *
*           WM_COMMAND                                               *
*           WM_DESTROY                                               *
*                                                                    *
*                                                                    *
\********************************************************************/

LRESULT CALLBACK MainWndProc( 
							 HWND hWnd, 
							 UINT msg, 
							 WPARAM wParam,
							 LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT rect;
	static wchar_t buf[10];
	wchar_t * pbuf = buf;

	switch( msg ) {

		/**************************************************************\
		*     WM_PAINT:                                                *
		\**************************************************************/

	  case WM_PAINT:
		  {
			  BOOL ret;
			  HDC m_dc;
			  HBITMAP *pbitmap;

			  hDC = BeginPaint( hWnd, &ps );
			  m_dc = CreateCompatibleDC(hDC);
			  pbitmap = (HBITMAP*)SelectObject(m_dc, hBitmap);
			  ret = BitBlt(hDC, 100, 100, 20, 20, m_dc, 0, 0, SRCCOPY);
			  if (ret != TRUE)
			  {
			  }

			  TextOut( hDC, 10, 10, TEXT("Hello, Windows!"), 15 );
			  TextOut( hDC, 50, 50, pbuf, wcslen(buf));
			  EndPaint( hWnd, &ps );
		  }
		  break;

	  case WM_KEYDOWN:
		  switch (wParam)
		  {
		  case VK_ESCAPE:
			  SendMessage(hWnd, WM_CLOSE, 0, 0);
			  break;
		  }

	  case	WM_MOVE:
		  GetWindowRect(hWnd, &rect);
		  _itow_s(rect.left, buf, sizeof(rect.left), 10);
		  InvalidateRect(hWnd,NULL,TRUE);
		  SendMessage(hWnd, WM_PAINT, 0, 0);
		  break;
		  /**************************************************************\
		  *     WM_COMMAND:                                              *
		  \**************************************************************/

	  case WM_COMMAND:
		  switch( wParam ) 
		  {
		  case IDM_ABOUT:
			  DialogBox( ghInstance, TEXT("AboutDlg"), hWnd, 
				  (DLGPROC) AboutDlgProc );
			  break;
		  }
		  break;

		  /**************************************************************\
		  *     WM_DESTROY: PostQuitMessage() is called                  *
		  \**************************************************************/

	  case WM_DESTROY:
		  // MessageBox(NULL, TEXT("You are about to quit"), TEXT("Warning"), MB_OK);
		  PostQuitMessage( 0 );
		  break;

		  /**************************************************************\
		  *     Let the default window proc handle all other messages    *
		  \**************************************************************/

	  default:
		  return( DefWindowProc( hWnd, msg, wParam, lParam ));
	}

	return 0;
}

/********************************************************************\
* Function: INT_PTR CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM)*
*                                                                    *
*  Purpose: Processes "About" Dialog Box Messages                    *
*                                                                    *
* Comments: The About dialog box is displayed when the user clicks   *
*           About from the Help menu.                                *
*                                                                    *
\********************************************************************/

INT_PTR CALLBACK AboutDlgProc( 
							  HWND hDlg, 
							  UINT uMsg, 
							  WPARAM wParam, 
							  LPARAM lParam )
{
	switch( uMsg ) {
	  case WM_INITDIALOG:
		  return TRUE;
	  case WM_COMMAND:
		  switch( wParam ) {
	  case IDOK:
		  EndDialog( hDlg, TRUE );
		  return TRUE;
		  }
		  break;
	}

	return FALSE;
}
