#ifndef MYQUICKVIEW_H
#define MYQUICKVIEW_H

#include <QQuickView>

class myQuickView : public QQuickView
{
public:
    myQuickView(QWindow * parent = 0);

protected:

    void showEvent(QShowEvent *event) override;
};

#endif // MYQUICKVIEW_H
