#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("3DViewer V1.0");
  connect(ui->ChangeBackgroundColor, SIGNAL(clicked()), this,
          SLOT(setBackColor()));
  connectSetup();
}

void MainWindow::connectSetup() {
  connect(ui->draw, &QPushButton::clicked, this, &MainWindow::paintfile);
}

bool isPainted = false;

void MainWindow::paintfile() {
  QString path =
      QFileDialog::getOpenFileName(0, "Open File .obj", "/Users/", "*.obj");
  if (path == "") return;
  isPainted = true;
  QByteArray ba = path.toLocal8Bit();
  ui->widget->filename = ba.data();
  ui->widget->initializeGL();
  ui->widget->initialize_data();
  ui->label_V_count->setText(
      QString::number(ui->widget->data->count_of_vertexes));
  ui->label_F_count->setText(
      QString::number(ui->widget->data->count_of_facets));

  int lastIndex = path.lastIndexOf('/');
  QString substring = path.mid(lastIndex + 1);
  ui->label_filename_out->setText(substring);
  ui->widget->update();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_Button_translate_x_clicked() {
  ui->widget->translate_x(ui->trans_x->text());
  ui->widget->update();
}

void MainWindow::on_Button_translate_y_clicked() {
  ui->widget->translate_y(ui->trans_y->text());
  ui->widget->update();
}
void MainWindow::setBackColor() {
  ui->widget->colorBack = QColorDialog::getColor(Qt::gray);
  ui->widget->update();
}

void MainWindow::on_Button_translate_z_clicked() {
  ui->widget->translate_z(ui->trans_z->text());
  ui->widget->update();
}

void MainWindow::on_Button_rotate_x_clicked() {
  ui->widget->rotate_x(ui->rotate_x->text());
  ui->widget->update();
}

void MainWindow::on_Button_rotate_y_clicked() {
  ui->widget->rotate_y(ui->rotate_y->text());
  ui->widget->update();
}

void MainWindow::on_Button_rotate_z_clicked() {
  ui->widget->rotate_z(ui->rotate_z->text());
  ui->widget->update();
}

void MainWindow::on_Button_scale_clicked() {
  ui->widget->scale(ui->scale_v->text());
  ui->widget->update();
}

void MainWindow::on_gif_clicked() {
  if (isPainted) {
    ui->gif->setEnabled(0);
    gif = new QGifImage;
    frame = new QImage;
    timer = new QTimer(this);
    count = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(save_gif()));
    timer->start(50);
  }
}

void MainWindow::save_gif() {
  count++;
  ui->gif->setText(QString::number(count / 10));
  timer->setInterval(250);
  *frame = ui->widget->grab().toImage();
  gif->addFrame(*frame);

  if (count == 50) {
    timer->stop();
    QString save = NULL;
    gif->setDefaultDelay(100);
    save = QFileDialog::getSaveFileName();
    if (!save.isNull()) gif->save(save);

    ui->gif->setText("GIF");
    ui->gif->setEnabled(1);
  }
}

void MainWindow::on_capture_image_clicked() {
  if (isPainted) {
    QString filePath = QFileDialog::getSaveFileName();
    if (!filePath.isEmpty()) {
      QImage image = ui->widget->grab().toImage();
      if (filePath.endsWith(".jpeg", Qt::CaseInsensitive)) {
        image.save(filePath, "JPEG", 85);

      } else if (filePath.endsWith(".bmp", Qt::CaseInsensitive)) {
        image.save(filePath, "BMP");
      }
      ui->widget->update();
    }
  }
}
