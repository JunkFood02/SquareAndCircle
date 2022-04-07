#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QPainter>
#include <QThread>
#include <thread>
#include <csignal>

int sign = 1;

class MainWindows : public QWidget {
public:

    QPainter *painter;

    void paintEvent(QPaintEvent *) override;

private:
};


void MainWindows::paintEvent(QPaintEvent *) {

    painter = new QPainter;

    painter->begin(this);
    pid_t pid = fork();

    if (pid == 0) {
        if (sign % 2)
            painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        else
            painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));
        qDebug("drawSquare");
        painter->drawRect(20, 20, 160, 160);
    } else {
        if (sign % 2)
            painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));
        else
            painter->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        qDebug("drawCircle");
        painter->drawEllipse(200, 20, 160, 160);
    }
    painter->end();
}

void changeColor(MainWindows *w) {
    for (; sign < 20; sign++) {
        sleep(1);
        w->repaint();
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindows w1;
    w1.show();
    std::thread th1(changeColor, &w1);
    th1.detach();
    return QApplication::exec();
}
