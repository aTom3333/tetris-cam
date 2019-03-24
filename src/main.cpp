#include "MainWindow.hpp"

#include <QApplication>
#include <QDebug>
#include "Tetromino.hpp"
#include "fixed_point.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    
    MainWindow window;
    window.show();
    
    return app.exec();
}