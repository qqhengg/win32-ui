#include <windows.h>
#include <gdiplus.h>
#include "resource.h"
#include "resource1.h"

BOOL CALLBACK DlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam); 

// Global variables.
HINSTANCE   hInst;
HWND        hDlg;
HWND        hwDlg;
HDC         hdc;                          // device context  
PAINTSTRUCT ps;                   // client area paint info 

HCURSOR     hCurs;     
HICON       hIcon;
HBITMAP     hBitmap;    
BOOL        Ret;

void ImportRes(void)
{
	// Initialize the cursor resource.
	HRSRC hResLoad;     // handle to loaded resource 
	HMODULE hExe;        // handle to existing .EXE file 
	HRSRC hRes;         // handle/ptr. to res. info. in hExe 
	HANDLE hUpdateRes;  // update resource handle 
	char *lpResLock;    // pointer to resource data 

	BOOL result; 
	UINT error = 0;

	// Load the .EXE file that contains the dialog box you want to copy. 
	hExe = LoadLibrary(TEXT("res_dll.dll")); 
	if (hExe == NULL) 
	{ 
	} 

	{
		hCurs = LoadCursor(hExe, MAKEINTRESOURCE(IDC_CURSOR1)); 
		if (hCurs == NULL)
		{
			error = GetLastError();
		}	
		hIcon = LoadIcon(hExe, MAKEINTRESOURCE(IDI_ICON1));
		if (hIcon == NULL)
		{
			error = GetLastError();
		}
		hBitmap = LoadBitmap(hExe, MAKEINTRESOURCE(IDB_BITMAP1)); 
		if (hBitmap == NULL)
		{
			error = GetLastError();
		}
	}

	{
		hRes = FindResource(hExe, MAKEINTRESOURCE(IDD_DIALOG1), RT_DIALOG);
		if (hRes == NULL) 
		{ 
			error = GetLastError();
		} 
		else
		{			
			hDlg = CreateDialog(hExe, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);						
		}

	}

	{
		// if the resource is ICON, it should refer RT_GROUP_ICON type.
		//hRes = FindResource(hExe, MAKEINTRESOURCE(IDD_DIALOG1), RT_DIALOG);
		hRes = FindResource(hExe, MAKEINTRESOURCE(IDC_CURSOR1), RT_GROUP_CURSOR);
		if (hRes == NULL) 
		{ 
			error = GetLastError();
		} 

		// Load the dialog box into global memory. 
		hResLoad = (HRSRC)LoadResource(hExe, hRes); 

		// Lock the dialog box into global memory. 
		lpResLock = (char *)LockResource(hResLoad); 

		// Open the file to which you want to add the dialog box resource. 
		hUpdateRes = BeginUpdateResource(TEXT("../Debug/generic.exe"), FALSE); 
		if (hUpdateRes == NULL) 
		{ 
			MessageBox(NULL, TEXT("Upadte failed!"), TEXT("Warning"), MB_OK);
			error = GetLastError();
		} 

		// Add the dialog box resource to the update list. 
		result = UpdateResource(\
			hUpdateRes,       // update resource handle 
			RT_GROUP_CURSOR,                   // change dialog box resource 
			MAKEINTRESOURCE(IDC_CURSOR1),                  // dialog box name 
			MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED),  // neutral language
			lpResLock,                   // ptr to resource info 
			SizeofResource(hExe, hRes)); // size of resource info. 
		if (result == FALSE) 
		{ 
			error = GetLastError();
		} 

		// Write changes to FOOT.EXE and then close it. 
		if (!EndUpdateResource(hUpdateRes, FALSE)) 
		{ 
		} 
	}

	{
		// if the resource is ICON, it should refer RT_GROUP_ICON type.
		//hRes = FindResource(hExe, MAKEINTRESOURCE(IDD_DIALOG1), RT_DIALOG);
		hRes = FindResource(hExe, MAKEINTRESOURCE(IDI_ICON1), RT_GROUP_ICON);
		if (hRes == NULL) 
		{ 
			error = GetLastError();
		} 

		// Load the dialog box into global memory. 
		hResLoad = (HRSRC)LoadResource(hExe, hRes); 

		// Lock the dialog box into global memory. 
		lpResLock = (char *)LockResource(hResLoad); 

		// Open the file to which you want to add the dialog box resource. 
		hUpdateRes = BeginUpdateResource(TEXT("../Debug/generic.exe"), FALSE); 
		if (hUpdateRes == NULL) 
		{ 
			MessageBox(NULL, TEXT("Upadte failed!"), TEXT("Warning"), MB_OK);
			error = GetLastError();
		} 

		// Add the dialog box resource to the update list. 
		result = UpdateResource(\
			hUpdateRes,       // update resource handle 
			RT_GROUP_ICON,                   // change dialog box resource 
			MAKEINTRESOURCE(IDI_ICON1),                  // dialog box name 
			MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED),  // neutral language
			lpResLock,                   // ptr to resource info 
			SizeofResource(hExe, hRes)); // size of resource info. 
		if (result == FALSE) 
		{ 
			error = GetLastError();
		} 

		// Write changes to FOOT.EXE and then close it. 
		if (!EndUpdateResource(hUpdateRes, FALSE)) 
		{ 
		} 
	}

	{
		// if the resource is ICON, it should refer RT_GROUP_ICON type.
		hRes = FindResource(hExe, MAKEINTRESOURCE(IDB_BITMAP1), RT_BITMAP);
		if (hRes == NULL) 
		{ 
			error = GetLastError();
		} 

		// Load the dialog box into global memory. 
		hResLoad = (HRSRC)LoadResource(hExe, hRes); 

		// Lock the dialog box into global memory. 
		lpResLock = (char *)LockResource(hResLoad); 

		// Open the file to which you want to add the dialog box resource. 
		hUpdateRes = BeginUpdateResource(TEXT("../Debug/generic.exe"), FALSE); 
		if (hUpdateRes == NULL) 
		{ 
			MessageBox(NULL, TEXT("Upadte failed!"), TEXT("Warning"), MB_OK);
			error = GetLastError();
		} 

		// Add the dialog box resource to the update list. 
		result = UpdateResource(\
			hUpdateRes,       // update resource handle 
			RT_BITMAP,                   // change dialog box resource 
			MAKEINTRESOURCE(IDB_BITMAP1),                  // dialog box name 
			MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED),  // neutral language
			lpResLock,                   // ptr to resource info 
			SizeofResource(hExe, hRes)); // size of resource info. 
		if (result == FALSE) 
		{ 
			error = GetLastError();
		} 

		// Write changes to FOOT.EXE and then close it. 
		if (!EndUpdateResource(hUpdateRes, FALSE)) 
		{ 
		} 
	}

	// Clean up. 
	if (!FreeLibrary(hExe)) 
	{ 
	} 
}

BOOL CALLBACK DlgProc(HWND hwndDlg, 
					  UINT message, 
					  WPARAM wParam, 
					  LPARAM lParam) 
{ 
	switch (message) 
	{ 
	case WM_COMMAND: 
		switch (LOWORD(wParam)) 
		{ 
		case IDOK: 
		case IDCANCEL: 
			//EndDialog(hwndDlg, wParam); //model dialog
			DestroyWindow(hwndDlg); //modeless dialog
			return TRUE; 
		case IDC_COMBO:
		case IDC_EDIT:
		case IDC_BUTTON:
			return FALSE;
		} 
		return FALSE;

	case WM_USER+10:
		MessageBox(NULL, TEXT("Received message from father!"), TEXT("Warning"), MB_OK);
		return TRUE;

	case WM_CHAR:
		MessageBox(NULL, TEXT("Dialog key down"), TEXT("Demo"), MB_OK);
		return TRUE;

	} 
	return FALSE; 
} 

LONG CALLBACK WndProc(HWND hwnd, UINT message, UINT wParam, LONG lParam)          
{ 
	switch (message) 
	{ 
	case WM_CREATE: 
		hwDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG), hwnd, (DLGPROC)DlgProc);
		ShowWindow(hwDlg, SW_SHOW);
		ShowWindow(hDlg, SW_SHOW);
		// "WM_USER+1" maybe confilict.
		SendMessage(hDlg, WM_USER+10, NULL, NULL);
		break;

	case WM_PAINT: 
		// Draw all the characters in the buffer, line by line.
		hdc = BeginPaint(hwnd, &ps); 
		{
			HDC m_dc;
			HBITMAP *pbitmap;
			m_dc = CreateCompatibleDC(hdc);
			pbitmap = (HBITMAP*)SelectObject(m_dc, hBitmap);
			Ret = BitBlt(hdc, 100, 100, 20, 20, m_dc, 0, 0, SRCCOPY);
			// if not released by this call,the next call will no longer work.
			DeleteDC(m_dc);
		}
		EndPaint(hwnd, &ps); 
		break;

	case WM_SETFOCUS: 
		// Create the caret. 
		CreateCaret(hwnd, hBitmap, 2, 10); 
		// Set the caret position. 
		SetCaretPos(10, 200); 
		// Display the caret. 
		ShowCaret(hwnd); 
		break; 

	case WM_KILLFOCUS: 
		// The window is losing the input focus, so destroy the caret. 
		DestroyCaret(); 
		// The window is losing the input focus, so destroy the Cursor. 
		DestroyCursor(hCurs);
		break; 

	case WM_SETCURSOR:  
		if (IsIconic(hwnd)) 
		{ 
			SetCursor(hCurs); 
		} 
		else
		{
			SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);	//The application including the dialog will be terminated.
		break; 

	case WM_COMMAND: 	
		MessageBox(NULL, TEXT("Window command"), TEXT("Demo"), MB_OK);
		break; 

	case WM_CHAR:
		MessageBox(NULL, TEXT("Window key down"), TEXT("Demo"), MB_OK);
		return TRUE;

	default: 
		return DefWindowProc(hwnd, message, wParam, lParam); 

	} 

	return NULL; 
} 

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wndClass;

	ImportRes();
	hInst = hInstance;

	wndClass.style          = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc    = WndProc;
	wndClass.cbClsExtra     = 0;
	wndClass.cbWndExtra     = 0;
	wndClass.hInstance      = hInstance;
	wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName   = NULL;
	wndClass.lpszClassName  = TEXT("Window");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(
		TEXT("Window"),           // window class name
		TEXT("Window"),           // window caption
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

	BOOL bRet;

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) 
	{ 
		if (bRet == -1)
		{
			// Handle the error and possibly exit
		}
		else if (\
			!IsWindow(hDlg) ||\
			!IsDialogMessage(hDlg, &msg) ||\
			!IsWindow(hwDlg) ||\
			!IsDialogMessage(hwDlg, &msg)\
			) 
		{ 
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		} 
	}

	return msg.wParam;
}

