#include "FrameLoader.h"

FrameLoader::FrameLoader(QObject* parent)
    : QObject(parent) {}

bool FrameLoader::loadVideo(const QString& path) {
    m_path = path;
    // TODO: implement ffmpeg loading
    return true;
}

std::vector<unsigned char> FrameLoader::getFrame(int index) {
    // TODO: return decoded frame bytes
    return {};
}
