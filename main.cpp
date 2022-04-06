#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QPainter>
#include <QThread>
#include <thread>
#include <csignal>

class MainWindows : public QWidget {
public:

    QPainter *painter;
private:
    void paintEvent(QPaintEvent *) override;
};


void MainWindows::paintEvent(QPaintEvent *) {

    painter = new QPainter;

    painter->begin(this);
    pid_t pid = fork();

    if (pid == 0) {

        painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        qDebug("drawSquare");
        painter->drawRect(20, 20, 160, 160);
    } else {

        painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));
        qDebug("drawCircle");
        painter->drawEllipse(200, 20, 160, 160);
    }
    painter->end();
}


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindows w1;
    w1.show();
    return QApplication::exec();
}
