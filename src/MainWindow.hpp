#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <memory>


namespace Ui
{
    class MainWindow;
}

//class représentant la structure de l'application
//on n'y retrouve TetrisWidget et VideoWidget
class MainWindow : public QMainWindow
{
    Q_OBJECT;
    
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    Ui::MainWindow* ui;

private slots:
    void close();
};


#endif // MAINWINDOW_HPP
