#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), scene(new QGraphicsScene(this)), pixmapItem(nullptr) {
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::openImage);
connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveImage);
connect(ui->resizeButton, &QPushButton::clicked, this, &MainWindow::resizeImage);
connect(ui->cropButton, &QPushButton::clicked, this, &MainWindow::cropImage);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openImage() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!fileName.isEmpty()) {
        if (currentImage.load(fileName)) {
            updateView();
        } else {
            QMessageBox::warning(this, "Error", "Failed to load image.");
        }
    }
}

void MainWindow::saveImage() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG (*.png);;JPG (*.jpg *.jpeg)");
    if (!fileName.isEmpty()) {
        currentImage.save(fileName);
    }
}

void MainWindow::resizeImage() {
    bool ok;
    int width = QInputDialog::getInt(this, "Resize Image", "Enter new width:", currentImage.width(), 1, 10000, 1, &ok);
    if (!ok) return;
    int height = QInputDialog::getInt(this, "Resize Image", "Enter new height:", currentImage.height(), 1, 10000, 1, &ok);
    if (!ok) return;

    currentImage = currentImage.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    updateView();
}

void MainWindow::cropImage() {
    bool ok;
    int x = QInputDialog::getInt(this, "Crop Image", "X:", 0, 0, currentImage.width() - 1, 1, &ok);
    if (!ok) return;
    int y = QInputDialog::getInt(this, "Crop Image", "Y:", 0, 0, currentImage.height() - 1, 1, &ok);
    if (!ok) return;
    int w = QInputDialog::getInt(this, "Crop Image", "Width:", currentImage.width(), 1, currentImage.width() - x, 1, &ok);
    if (!ok) return;
    int h = QInputDialog::getInt(this, "Crop Image", "Height:", currentImage.height(), 1, currentImage.height() - y, 1, &ok);
    if (!ok) return;

    currentImage = currentImage.copy(x, y, w, h);
    updateView();
}

void MainWindow::updateView() {
    scene->clear();
    pixmapItem = scene->addPixmap(QPixmap::fromImage(currentImage));
    scene->setSceneRect(currentImage.rect());
    ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);
}
