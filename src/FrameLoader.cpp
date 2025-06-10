#include "FrameLoader.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

#include <QDebug>
#include <mutex>

FrameLoader::FrameLoader(QObject* parent)
    : QObject(parent) {}

FrameLoader::~FrameLoader() {
    if (m_frame)
        av_frame_free(&m_frame);
    if (m_packet)
        av_packet_free(&m_packet);
    if (m_codecCtx)
        avcodec_free_context(&m_codecCtx);
    if (m_fmtCtx)
        avformat_close_input(&m_fmtCtx);
    if (m_sws)
        sws_freeContext(m_sws);
}

bool FrameLoader::loadVideo(const QString& path) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_path = path;

    avformat_network_init();

    if (avformat_open_input(&m_fmtCtx, path.toUtf8().constData(), nullptr, nullptr) < 0) {
        emit errorOccurred("Could not open input");
        return false;
    }

    if (avformat_find_stream_info(m_fmtCtx, nullptr) < 0) {
        emit errorOccurred("Could not find stream info");
        return false;
    }

    for (unsigned i = 0; i < m_fmtCtx->nb_streams; ++i) {
        if (m_fmtCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            m_videoStream = i;
            break;
        }
    }
    if (m_videoStream == -1) {
        emit errorOccurred("No video stream found");
        return false;
    }

    AVCodecParameters* params = m_fmtCtx->streams[m_videoStream]->codecpar;
    const AVCodec* codec = avcodec_find_decoder(params->codec_id);
    if (!codec) {
        emit errorOccurred("Unsupported codec");
        return false;
    }

    m_codecCtx = avcodec_alloc_context3(codec);
    if (avcodec_parameters_to_context(m_codecCtx, params) < 0) {
        emit errorOccurred("Failed to copy codec parameters");
        return false;
    }

    if (avcodec_open2(m_codecCtx, codec, nullptr) < 0) {
        emit errorOccurred("Could not open codec");
        return false;
    }

    m_width = m_codecCtx->width;
    m_height = m_codecCtx->height;

    m_frame = av_frame_alloc();
    m_packet = av_packet_alloc();
    m_sws = sws_getContext(m_width, m_height, m_codecCtx->pix_fmt,
                           m_width, m_height, AV_PIX_FMT_RGB24, SWS_BILINEAR,
                           nullptr, nullptr, nullptr);

    return true;
}

std::vector<unsigned char> FrameLoader::getFrame(int index) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_fmtCtx)
        return {};

    if (av_seek_frame(m_fmtCtx, m_videoStream, index, AVSEEK_FLAG_FRAME) < 0) {
        emit errorOccurred("Seek failed");
        return {};
    }
    avcodec_flush_buffers(m_codecCtx);

    int gotFrame = 0;
    while (!gotFrame && av_read_frame(m_fmtCtx, m_packet) >= 0) {
        if (m_packet->stream_index == m_videoStream) {
            if (avcodec_send_packet(m_codecCtx, m_packet) == 0) {
                if (avcodec_receive_frame(m_codecCtx, m_frame) == 0) {
                    gotFrame = 1;
                }
            }
        }
        av_packet_unref(m_packet);
    }

    if (!gotFrame)
        return {};

    std::vector<unsigned char> rgb(m_width * m_height * 3);
    uint8_t* dest[4] = { rgb.data(), nullptr, nullptr, nullptr };
    int linesize[4] = { m_width * 3, 0, 0, 0 };
    sws_scale(m_sws, m_frame->data, m_frame->linesize, 0, m_height, dest, linesize);

    return rgb;
}
