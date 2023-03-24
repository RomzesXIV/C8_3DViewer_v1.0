#include "mainwindow.h"

#include "ui_mainwindow.h"
// #include "ui_settings_widget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QValidator>

#include "../../extLibs/QtGifImage-master/src/gifimage/qgifimage.h"
// #include "../../extLibs/QtGifImage-master/src/3rdParty/giflib/gifalloc.c"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("3DViewer");
  QDoubleValidator* d_valid = new QDoubleValidator(-360.0, 360.0, 4, this);
  d_valid->setNotation(QDoubleValidator::StandardNotation);
  d_valid->setLocale(QLocale::English);
  ui->scale_line->setValidator(d_valid);
  ui->x_move_line->setValidator(d_valid);
  ui->y_move_line->setValidator(d_valid);
  ui->z_move_line->setValidator(d_valid);
  ui->x_rotate_line->setValidator(d_valid);
  ui->y_rotate_line->setValidator(d_valid);
  ui->z_rotate_line->setValidator(d_valid);
  viewer_ = new Viewer(this);
  viewer_->sw_ = new SettingsWidget(this);  // проверить утечку памяти
  viewer_->sw_->setModal(true);
  ui->gridLayout->addWidget(viewer_, 0, 3, 14, 1);
  connect(ui->load_btn, SIGNAL(clicked()), this, SLOT(SlotLoadBtnClicked()));
  connect(ui->apply_btn, SIGNAL(clicked()), this, SLOT(SlotApplyBtnClicked()));
  connect(ui->settings_btn, SIGNAL(clicked()), this,
          SLOT(SlotSettngsBtnClicked()));
  connect(ui->record_button, SIGNAL(clicked(bool)), this,
          SLOT(SlotRecorBtnClicked()));
  connect(&tmr, SIGNAL(timeout()), this, SLOT(SlotAddImgToGif()));
}

MainWindow::~MainWindow() {
  delete ui;
  delete gif;
}

void MainWindow::SlotLoadBtnClicked() {
  QString path = QFileDialog::getOpenFileName(this, "Выбор модели", "",
                                              "OBJ Files (*.obj)");
  //  qDebug() << path;
  if (!path.isEmpty()) {
    viewer_->LoadModel(path);
    if (viewer_->md_ != NULL) {
      // QMessageBox::critical(this, tr("error"), tr("model error"));
      QString mess = viewer_->md_->GetFileName() +
                     " v = " + QString::number((viewer_->md_->v_.pos + 1) / 3) +
                     " f = " + QString::number(viewer_->md_->s_.pos + 1);
      ui->statusbar->showMessage(mess);
    } else {
      QMessageBox::critical(this, tr("error"), tr("model error"));
    }
  }
}

void MainWindow::SlotApplyBtnClicked() {
  if (viewer_->md_ != NULL) {
    GLfloat rot_x = (GLfloat)ui->x_rotate_line->text().toFloat();
    GLfloat rot_y = (GLfloat)ui->y_rotate_line->text().toFloat();
    GLfloat rot_z = (GLfloat)ui->z_rotate_line->text().toFloat();
    viewer_->md_->RotateModel(rot_x, rot_y, rot_z);
    GLfloat move_x = (GLfloat)ui->x_move_line->text().toFloat();
    GLfloat move_y = (GLfloat)ui->y_move_line->text().toFloat();
    GLfloat move_z = (GLfloat)ui->z_move_line->text().toFloat();
    viewer_->md_->MoveModel(move_x, move_y, move_z);
    GLfloat scale = (GLfloat)ui->scale_line->text().toFloat();
    if (scale == 0) scale = 0.001;
    viewer_->md_->ScaleModelFromForm(scale);
    viewer_->update();
  }
}

void MainWindow::SlotSettngsBtnClicked() {
  viewer_->sw_ = new SettingsWidget(this);  // проверить утечку памяти
  viewer_->sw_->setModal(true);

  if (viewer_->sw_->exec() == QDialog::Accepted) {
    viewer_->LoadSettings();
    viewer_->update();
  }
}

void MainWindow::SlotRecorBtnClicked() {
  QImage img = viewer_->grabFramebuffer();
  if (ui->comboBox->currentIndex() == 0) {
    QString file_name = QFileDialog::getSaveFileName(this, tr("save"), "~/",
                                                     tr("Images (*.jpg)"));
    img.save(file_name, "JPG");
  } else if (ui->comboBox->currentIndex() == 1) {
    QString file_name = QFileDialog::getSaveFileName(this, tr("save"), "~/",
                                                     tr("Images (*.bmp)"));
    img.save(file_name, "BMP");
  } else if (ui->comboBox->currentIndex() == 2) {
    tmr.start(100);
  }
  // qDebug() << img.save("/Users/a1234/Desktop/img.png", "PNG");
}
void MainWindow::SlotAddImgToGif() {
  if (gif == NULL) {
    gif = new QGifImage;
    QGifImage gif(QSize(640, 480));
    gif.setDefaultTransparentColor(Qt::black);
    gif.setDefaultDelay(100);
  }
  QImage img = viewer_->grabFramebuffer();
  gif->addFrame(img);
  if (gif->frameCount() == 50) {
    QString file_name = QFileDialog::getSaveFileName(this, tr("save"), "~/",
                                                     tr("Images (*.gif)"));
    gif->save(file_name);
    // GifFreeSavedImages(gif);
    //        GifFreeSavedImages(gif);
    delete gif;
    gif = NULL;
    tmr.stop();
  }
}
