#include "SetWindowsProperties.h"

LRESULT CALLBACK WindowProc( HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    switch ( Msg ) 
	{
        case WM_CLOSE: 
			PostQuitMessage(0);
			break;

        case WM_DESTROY:
            PostQuitMessage(0);

        case WM_KEYDOWN:
            switch (wParam) 
			{
                case VK_ESCAPE:
					PostQuitMessage(0);
					break;
            }
			break;

        default:
            return DefWindowProc(hwnd, Msg, wParam, lParam);
    }

    return 0;
}

WNDCLASSEX GLSample () 
{
    WNDCLASSEX wc		= { sizeof ( WNDCLASSEX ) };

    wc.style			= CS_OWNDC;
    wc.lpfnWndProc		= WindowProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hIcon			= LoadIcon ( NULL, IDI_APPLICATION );
    wc.hCursor			= LoadCursor ( NULL, IDC_ARROW );
    wc.hbrBackground	= CreateSolidBrush ( RGB (0,128,128) );
    wc.lpszMenuName		= NULL;
    wc.lpszClassName	= "GLSample";
    wc.hIconSm			= LoadIcon ( NULL, IDI_APPLICATION );

    return wc;
}