#include "myQuickView.h"

#include <qt_windows.h>

myQuickView::myQuickView(QWindow * parent)
    :
      QQuickView(parent)
{

}

void myQuickView::showEvent(QShowEvent *event)
{
    QQuickView::showEvent(event);

    // Keyboard should NOT not take focus. Therefore this is required on windows:
    HWND winHandle = (HWND)winId();
    ShowWindow(winHandle, SW_HIDE);
    SetWindowLong(winHandle, GWL_EXSTYLE, GetWindowLong(winHandle, GWL_EXSTYLE)
        | WS_EX_NOACTIVATE | WS_EX_APPWINDOW);
    ShowWindow(winHandle, SW_SHOW);
}