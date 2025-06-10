#ifndef VAST_FRAMELOADER_H
#define VAST_FRAMELOADER_H

#include <QObject>
#include <QString>
#include <vector>

class FrameLoader : public QObject {
  Q_OBJECT
public:
  explicit FrameLoader(QObject* parent = nullptr);
  bool loadVideo(const QString& path);
  std::vector<unsigned char> getFrame(int index);

private:
  QString m_path;
};

#endif // VAST_FRAMELOADER_H
