#include <windows.h>
#include "Const.h"  // Include the header file for Constants
#include "UI.h"

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    PowermeterIndicatorConstants::PowermeterIndicatorConstants myPowermeterIndicatorConstants;
    LabelPowermeterConstants::LabelPowermeterConstants myLabelPowermeterConstants;
    LabelNeutralDensityStageConstants::LabelNeutralDensityStageConstants myLabelNutralDensityStageConstants;
    NeutralDensityStageIndicatorConstants::NeutralDensityStageIndicatorConstants myNeutralDensityStageIndicatorConstants;
    HWND indicatorPowermeterStatus;
    HWND labelPowermeterstauts;
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

        labelPowermeterstauts = CreateWindow(L"STATIC", L"Powermeterstauts", WS_VISIBLE | WS_CHILD | WS_BORDER,
            myLabelPowermeterConstants.xLabel(),
            myLabelPowermeterConstants.yLabel(),
            myLabelPowermeterConstants.WidthLabel(),
            myLabelPowermeterConstants.HeightLabel(),
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
