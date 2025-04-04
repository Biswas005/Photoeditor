#pragma once

#include <QMainWindow>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openImage();
    void saveImage();
    void resizeImage();
    void cropImage();

private:
    Ui::MainWindow *ui;
    QImage currentImage;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmapItem;

    void updateView();
};
