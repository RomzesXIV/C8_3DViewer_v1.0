#include "model_data.h"

#include "../../model/model.h"
#include "../../model/parser.h"
ModelData::ModelData(QString path) {
  path_ = path;
  std::string str = path.toStdString();
  const char* c_str = str.c_str();
  err_ = Parse(c_str, &v_, &s_);
  // qDebug() << err_;
  modelViewMatrix_.setToIdentity();
  scale_ = 1.0;
}

ModelData::~ModelData() {
  FreeSurface(&s_);
  FreeVertex(&v_);
}

void ModelData::RotateModel(GLfloat x, GLfloat y, GLfloat z) {
  modelViewMatrix_.rotate(x, 1.0, 0.0, 0.0);
  modelViewMatrix_.rotate(y, 0.0, 1.0, 0.0);
  modelViewMatrix_.rotate(z, 0.0, 0.0, 1.0);
}

void ModelData::ScaleModel(GLfloat scale_change) {
  if (scale_ != 0) modelViewMatrix_.scale(1 / scale_);
  if (scale_ + scale_change <= 0)
    scale_ = 0.001;
  else
    scale_ += scale_change;
  modelViewMatrix_.scale(scale_);
  // qDebug() << scale_;
}

void ModelData::ScaleModelFromForm(GLfloat scale) {
  if (scale_ != 0)
    modelViewMatrix_.scale(1 / scale_);
  else
    modelViewMatrix_.scale(1);
  scale_ = scale;
  modelViewMatrix_.scale(scale_);
}

void ModelData::MoveModel(GLfloat x, GLfloat y, GLfloat z) {
  modelViewMatrix_.translate(x, y, z);
}

QString ModelData::GetFileName() {
  QString res;
  auto it = path_.rbegin();
  for (; it != path_.rend(); ++it) {
    if (*it == '/') break;
    res += *it;
  }
  std::reverse(res.begin(), res.end());
  return res;
}
