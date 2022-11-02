#ifdef HOOKWINDOWSKEYDLL_EXPORTS
#define HOOKWINDOWSKEYDLL_API __declspec(dllexport)
#else
#define HOOKWINDOWSKEYDLL_API __declspec(dllimport)
#endif

int WM_TOGGLELAUNCHPAD = WM_APP + 0x0808;

extern "C"
{
    HOOKWINDOWSKEYDLL_API LRESULT HookProgManThread(int code, WPARAM wParam, LPARAM lParam)
    {
        if (code == HC_ACTION && wParam)
        {
            MSG* msg = (MSG*)lParam;
            if (msg->message == WM_SYSCOMMAND && (msg->wParam & 0xFFF0) == SC_TASKLIST)
            {
                // Win button pressed
                msg->message = WM_NULL;
                
				HWND hWnd = FindWindowEx(NULL, NULL, NULL, L"WinLaunch");

				if (hWnd == NULL)
					return CallNextHookEx(NULL, code, wParam, lParam);

				//send activation
				SendMessage(hWnd, WM_TOGGLELAUNCHPAD, 0, 0);
            }
        }
        return CallNextHookEx(NULL, code, wParam, lParam);
    }
}