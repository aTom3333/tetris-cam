#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <memory>


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT;
    
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    Ui::MainWindow* ui;
};


#endif // MAINWINDOW_HPP