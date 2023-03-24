#include "viewer.h"

#include <QMessageBox>
#include <QMouseEvent>

Viewer::Viewer(QWidget *parent) : QOpenGLWidget(parent) {
  settings = new QSettings(this);
  LoadSettings();
}

Viewer::~Viewer() { delete md_; }

void Viewer::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}
void Viewer::resizeGL(int w, int h) { glViewport(0, 0, w, h); }
void Viewer::paintGL() {
  projection_matrix_.setToIdentity();
  if (projection_type_ == 0) {
    projection_matrix_.ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 6.0f);
  } else {
    projection_matrix_.frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 6.0f);
  }
  projection_matrix_.translate(0.0, 0.0, -2.05);
  glLineWidth((GLfloat)line_width_);
  if (line_type_ == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0X00FF);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glEnable(GL_PROGRAM_POINT_SIZE);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  initShaders();
  program_->bind();

  glClearColor((GLfloat)background_color_[0], (GLfloat)background_color_[1],
               (GLfloat)background_color_[2], (GLfloat)background_color_[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (md_ != NULL) {
    vertex_buffer_.bind();
    program_->setUniformValue("qt_ModelViewProjectionMatrix",
                              projection_matrix_ * md_->modelViewMatrix_);
    program_->setUniformValue("color", line_color_);
    int vertLoc = program_->attributeLocation("qt_Vertex");
    program_->enableAttributeArray(vertLoc);
    program_->setAttributeBuffer(vertLoc, GL_FLOAT, 0, 3, 0);
    program_->setUniformValue("point_size", vertex_size_);
    for (int i = 0; i <= md_->s_.pos; ++i) {
      glDrawElements(GL_LINE_LOOP, md_->s_.polygons[i].pos + 1, GL_UNSIGNED_INT,
                     md_->s_.polygons[i].data);
    }
    if (vertex_type_ != 0) {
      program_->setUniformValue("color", vertex_color_);
      if (vertex_type_ == 1)
        glEnable(GL_POINT_SMOOTH);
      else
        glDisable(GL_POINT_SMOOTH);
      for (int i = 0; i <= md_->s_.pos; ++i) {
        glDrawElements(GL_POINTS, md_->s_.polygons[i].pos + 1, GL_UNSIGNED_INT,
                       md_->s_.polygons[i].data);
      }
    }
  }
  delete (program_);
}

int Viewer::LoadModel(QString path) {
  if (md_ != NULL && md_->err_ == -1) {
    delete md_;
  }
  md_ = new ModelData(path);
  int err = md_->err_;
  if (md_->err_ != -1) {
    delete md_;
    md_ = NULL;

  } else {
    InitModel();
    update();
  }
  return err;
}

void Viewer::LoadSettings() {
  QColor tmp =
      settings->value("background_color", QColor(Qt::black)).value<QColor>();
  background_color_[0] = (GLfloat)tmp.red() / 255;
  background_color_[1] = (GLfloat)tmp.green() / 255;
  background_color_[2] = (GLfloat)tmp.blue() / 255;
  background_color_[3] = (GLfloat)tmp.alpha() / 255;
  tmp = settings->value("line_color", QColor(Qt::white)).value<QColor>();
  line_color_[0] = (GLfloat)tmp.red() / 255;
  line_color_[1] = (GLfloat)tmp.green() / 255;
  line_color_[2] = (GLfloat)tmp.blue() / 255;
  line_color_[3] = (GLfloat)tmp.alpha() / 255;
  tmp = settings->value("vertex_color", QColor(Qt::blue)).value<QColor>();
  vertex_color_[0] = (GLfloat)tmp.red() / 255;
  vertex_color_[1] = (GLfloat)tmp.green() / 255;
  vertex_color_[2] = (GLfloat)tmp.blue() / 255;
  vertex_color_[3] = (GLfloat)1.0;
  line_type_ = settings->value("line_type", 0).toInt();
  vertex_type_ = settings->value("vertex_type", 0).toInt();
  vertex_size_ = settings->value("vertex_size", 1.0).toFloat();
  line_width_ = settings->value("line_width", 1.0).toFloat();
  projection_type_ = settings->value("projection_type", 0).toInt();
}

void Viewer::InitModel() {
  vertex_buffer_.create();
  vertex_buffer_.bind();
  vertex_buffer_.allocate(md_->v_.data, (md_->v_.pos + 1) * sizeof(GLfloat));
  vertex_buffer_.release();
}

void Viewer::mousePressEvent(QMouseEvent *mo) { pos_ = mo->pos(); }

void Viewer::mouseMoveEvent(QMouseEvent *mo) {
  x_rot_ = (mo->pos().y() - pos_.y());
  y_rot_ = (mo->pos().x() - pos_.x());
  pos_ = mo->pos();
  if (md_ != NULL) {
    md_->RotateModel(x_rot_, y_rot_, 0);
  }
  update();
}

void Viewer::wheelEvent(QWheelEvent *event) {
  GLfloat scale = event->angleDelta().y() / 1200.0;
  if (md_ != NULL) {
    md_->ScaleModel(scale);
  }
  update();
}

void Viewer::initShaders() {
  program_ = new QOpenGLShaderProgram();
  if (!program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         ":/vertex_shader.vsh")) {
    qDebug() << "vertex shader not compilated";
    close();
  }
  if (!program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         ":/flagment_shader.fsh")) {
    qDebug() << "fragment shader not compilated";
    close();
  }
  if (!program_->link()) {
    qDebug() << "shader program not linked";
    close();
  }
}
