#include "MainWindow.hpp"

#include <QApplication>
#include <QDebug>
#include "Tetris/Tetromino.hpp"
#include "Tetris/fixed_point.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    
    MainWindow window;
    window.show();
    
    return app.exec();
}
