#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "../../extLibs/QtGifImage-master/src/gifimage/qgifimage.h"
#include "viewer.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
/*!
 * \brief Основное окно приложения
 *
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  Viewer *viewer_;
  QGifImage *gif = NULL;

 public slots:
  /**
   * Кнопка загрузки модели
   */
  void SlotLoadBtnClicked();
  /**
   * Кнопка применения насстроек смещения модели
   */
  void SlotApplyBtnClicked();
  /**
   * Кнопка открытия формы настроек отображения модели
   */
  void SlotSettngsBtnClicked();
  /**
   * Кнопка сохранения изображения или анимации
   */
  void SlotRecorBtnClicked();
  void SlotAddImgToGif();

 private:
  Ui::MainWindow *ui;
  QTimer tmr;
};
#endif  // MAINWINDOW_H
