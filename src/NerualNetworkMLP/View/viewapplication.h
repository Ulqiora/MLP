#ifndef VIEWAPPLICATION_H
#define VIEWAPPLICATION_H

#include <QMainWindow>

namespace Ui {
class ViewApplication;
}

class ViewApplication : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewApplication(QWidget *parent = nullptr);
    ~ViewApplication();

private:
    Ui::ViewApplication *ui;
};

#endif // VIEWAPPLICATION_H
