#include "MainWindow.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QImage>
#include <QPixmap>
#include <QVBoxLayout>
#include <QDebug>

#include "FrameLoader.h"
#include <QCoreApplication>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    setWindowTitle("VAST");
    setAcceptDrops(true);

    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);
    m_label = new QLabel(tr("Drop video file here"), central);
    m_label->setAlignment(Qt::AlignCenter);
    layout->addWidget(m_label);
    setCentralWidget(central);

    QString pluginDir = QCoreApplication::applicationDirPath() + "/plugins";
    m_pluginMgr.loadPlugins(pluginDir);
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent* event) {
    const QUrl url = event->mimeData()->urls().value(0);
    if (!url.isLocalFile())
        return;

    if (m_loader.loadVideo(url.toLocalFile())) {
        auto frame = m_loader.getFrame(0);
        if (!frame.empty()) {
            QImage img(frame.data(), m_loader.width(), m_loader.height(), QImage::Format_RGB888);
            m_label->setPixmap(QPixmap::fromImage(img));
        }
    }
}
