#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QColorDialog>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QMovie>

#include "mywidget.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  QGifImage *gif;
  QImage *frame;
  QTimer *timer;
  int count;

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_Button_translate_x_clicked();

  void on_Button_translate_y_clicked();

  void on_Button_translate_z_clicked();

  void on_Button_rotate_x_clicked();

  void on_Button_rotate_y_clicked();

  void on_Button_rotate_z_clicked();

  void on_Button_scale_clicked();
  void setBackColor();

  void on_gif_clicked();

  void save_gif();

  void on_capture_image_clicked();

 private:
  Ui::MainWindow *ui;
  void connectSetup();
  void paintfile();
};
#endif  // MAINWINDOW_H
