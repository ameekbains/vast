#ifndef VAST_FRAMELOADER_H
#define VAST_FRAMELOADER_H

#include <QObject>
#include <QString>
#include <vector>
#include <mutex>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

class FrameLoader : public QObject {
  Q_OBJECT
public:
  explicit FrameLoader(QObject* parent = nullptr);
  ~FrameLoader();
  bool loadVideo(const QString& path);
  std::vector<unsigned char> getFrame(int index);

  int width() const { return m_width; }
  int height() const { return m_height; }

signals:
  void errorOccurred(const QString& msg);

private:
  QString m_path;
  AVFormatContext* m_fmtCtx = nullptr;
  AVCodecContext* m_codecCtx = nullptr;
  int m_videoStream = -1;
  AVFrame* m_frame = nullptr;
  AVPacket* m_packet = nullptr;
  SwsContext* m_sws = nullptr;
  int m_width = 0;
  int m_height = 0;
  std::mutex m_mutex;
};

#endif // VAST_FRAMELOADER_H
