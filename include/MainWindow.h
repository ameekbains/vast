#ifndef VAST_MAINWINDOW_H
#define VAST_MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "FrameLoader.h"
#include "PluginManager.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget* parent = nullptr);

protected:
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dropEvent(QDropEvent* event) override;

private:
  FrameLoader m_loader;
  QLabel* m_label = nullptr;
  PluginManager m_pluginMgr;
};

#endif // VAST_MAINWINDOW_H
