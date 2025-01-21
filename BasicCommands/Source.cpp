// The source of everything
#include <windows.h>
#include "UI.h"
#include "Const.h"
#include <iostream>
#include <iomanip>
#include "OphirLMMeasurement.h"
#include "InstrumentRoutines.h"
// for powermeter
struct CoInitializer
{
    CoInitializer() { CoInitialize(nullptr); }
    ~CoInitializer() { CoUninitialize(); }
};

CoInitializer initializer;// must call for COM initialization and deinitialization
InstrumentRoutines Instrument;


// This is were the program starts 
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    WindowConstants::WindowConstants myWindowConstants;
    MainWindow win;

    if (!win.Create(
        L"Micro/Spirit Test Panel",               // Window Name
        WS_OVERLAPPEDWINDOW,                      // Window Style
        0,                                        // Extended Style
        CW_USEDEFAULT, CW_USEDEFAULT,             // Position
        myWindowConstants.windowWidth(),            // Window Width (from Constants)
        myWindowConstants.windowHeight(),           // Window Height (from Constants)
        NULL,                                     // Parent Window
        NULL                                      // Menu
    ))
    {
        return 0;
    }

    ShowWindow(win.Window(), nCmdShow);

    // Run the message loop.
    // This is the 
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        Instrument.ScanPowerMeter();
    }
    return 0;


}

