#ifndef VIEWAPPLICATION_H
#define VIEWAPPLICATION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ViewApplication; }
QT_END_NAMESPACE

class ViewApplication : public QMainWindow
{
    Q_OBJECT

public:
    ViewApplication(QWidget *parent = nullptr);
    ~ViewApplication();

private:
    Ui::ViewApplication *ui;
};
#endif // VIEWAPPLICATION_H
