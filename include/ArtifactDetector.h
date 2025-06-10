#ifndef VAST_ARTIFACTDETECTOR_H
#define VAST_ARTIFACTDETECTOR_H

#include <QObject>
#include <QString>

class ArtifactDetector : public QObject {
  Q_OBJECT
public:
  explicit ArtifactDetector(QObject* parent = nullptr) : QObject(parent) {}
  virtual QString name() const = 0;
  virtual void processFrame(const unsigned char* data, int width, int height) = 0;
};

#endif // VAST_ARTIFACTDETECTOR_H
