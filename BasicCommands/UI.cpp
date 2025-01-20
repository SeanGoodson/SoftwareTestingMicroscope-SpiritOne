#include <windows.h>
#include "Const.h"  // Include the header file for Constants

template <class UI>
class BaseWindow
{
public:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        UI* pThis = NULL;

        if (uMsg == WM_NCCREATE)
        {
            CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
            pThis = (UI*)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

            pThis->m_hwnd = hwnd;
        }
        else
        {
            pThis = (UI*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        }
        if (pThis)
        {
            return pThis->HandleMessage(uMsg, wParam, lParam);
        }
        else
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    BaseWindow() : m_hwnd(NULL) {}

    WindowConstants::WindowConstants myWindowConstants;  // Define the Constants instance here
    MultimeterIndicatorConstants::MultimeterIndicatorConstants myMultimeterIndicatorConstants;
    PowermeterIndicatorConstants::PowermeterIndicatorConstants myPowermeterIndicatorConstants;
    LabelMultimeterConstants::LabelMultimeterConstants myLabelMultimeterConstants;
    LabelPowermeterConstants::LabelPowermeterConstants myLabelPowermeterConstants;
    LabelNeutralDensityStageConstants::LabelNeutralDensityStageConstants myLabelNutralDensityStageConstants;
    NeutralDensityStageIndicatorConstants::NeutralDensityStageIndicatorConstants myNeutralDensityStageIndicatorConstants;
    BOOL Create(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = 800,  // Default to 800 for width if not passed
        int nHeight = 700, // Default to 700 for height if not passed
        HWND hWndParent = 0,
        HMENU hMenu = 0
    )
    {
        WNDCLASS wc = { 0 };

        wc.lpfnWndProc = UI::WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = ClassName();

        RegisterClass(&wc);

        m_hwnd = CreateWindowEx(
            dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
            nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
        );

        return (m_hwnd ? TRUE : FALSE);
    }

    HWND Window() const { return m_hwnd; }

protected:

    virtual PCWSTR  ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

    HWND m_hwnd;
};

class MainWindow : public BaseWindow<MainWindow>
{
public:
    PCWSTR ClassName() const { return L"Sample Window Class"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    MainWindow win;

    if (!win.Create(
        L"Micro/Spirit Test Panel",               // Window Name
        WS_OVERLAPPEDWINDOW,                      // Window Style
        0,                                        // Extended Style
        CW_USEDEFAULT, CW_USEDEFAULT,             // Position
        win.myWindowConstants.windowWidth(),            // Window Width (from Constants)
        win.myWindowConstants.windowHeight(),           // Window Height (from Constants)
        NULL,                                     // Parent Window
        NULL                                      // Menu
    ))
    {
        return 0;
    }

    ShowWindow(win.Window(), nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND indicatorPowermeterStatus;
    HWND indicatorMultimeterStatus;
    HWND labelPowermeterstauts;
    HWND labelMultimeterStatus;
    HWND indicatorNeutralDensityStageStatus;
    HWND labelNeutralDensityStageStatus;
    switch (uMsg)
    {
    case WM_CREATE:
        indicatorPowermeterStatus = CreateWindow(L"STATIC", L"Not Connected", WS_VISIBLE | WS_CHILD | WS_BORDER,
            myPowermeterIndicatorConstants.xIndicator(),
            myPowermeterIndicatorConstants.yIndicator(),
            myPowermeterIndicatorConstants.WidthIndicator(),
            myPowermeterIndicatorConstants.HeightIndicator(),
            m_hwnd, NULL, NULL, NULL);

        indicatorMultimeterStatus = CreateWindow(L"STATIC", L"Not Connected", WS_VISIBLE | WS_CHILD | WS_BORDER,
            myMultimeterIndicatorConstants.xIndicator(),
            myMultimeterIndicatorConstants.yIndicator(),
            myMultimeterIndicatorConstants.WidthIndicator(),
            myMultimeterIndicatorConstants.HeightIndicator()
            , m_hwnd, NULL, NULL, NULL);

        labelPowermeterstauts = CreateWindow(L"STATIC", L"Powermeterstauts", WS_VISIBLE | WS_CHILD | WS_BORDER,
            myLabelPowermeterConstants.xLabel(),
            myLabelPowermeterConstants.yLabel(),
            myLabelPowermeterConstants.WidthLabel(),
            myLabelPowermeterConstants.HeightLabel(),
             m_hwnd, NULL, NULL, NULL);

        labelMultimeterStatus = CreateWindow(L"STATIC", L"MultimeterStatus", WS_VISIBLE | WS_CHILD | WS_BORDER,
            myLabelMultimeterConstants.xLabel(),
            myLabelMultimeterConstants.yLabel(),
            myLabelMultimeterConstants.WidthLabel(),
            myLabelMultimeterConstants.HeightLabel(),
            m_hwnd, NULL, NULL, NULL);

        labelNeutralDensityStageStatus = CreateWindow(L"STATIC", L"NeutralDensityStageStatus", WS_VISIBLE | WS_CHILD | WS_BORDER,
            myLabelNutralDensityStageConstants.xLabel(),
            myLabelNutralDensityStageConstants.yLabel(),
            myLabelNutralDensityStageConstants.WidthLabel(),
            myLabelNutralDensityStageConstants.HeightLabel(),
            m_hwnd, NULL, NULL, NULL);

        indicatorNeutralDensityStageStatus = CreateWindow(L"STATIC", L"Not Connected", WS_VISIBLE | WS_CHILD | WS_BORDER,
            myNeutralDensityStageIndicatorConstants.xIndicator(),
            myNeutralDensityStageIndicatorConstants.yIndicator(),
            myNeutralDensityStageIndicatorConstants.WidthIndicator(),
            myNeutralDensityStageIndicatorConstants.HeightIndicator(),
            m_hwnd, NULL, NULL, NULL);

        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(m_hwnd, &ps);
    }
    return 0;

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
       
    }
    return TRUE;
}
