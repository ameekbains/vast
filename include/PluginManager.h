#ifndef VAST_PLUGINMANAGER_H
#define VAST_PLUGINMANAGER_H

#include <QObject>
#include <QString>
#include <vector>
#include <QLibrary>

class ArtifactDetector;

class PluginManager : public QObject {
  Q_OBJECT
public:
  explicit PluginManager(QObject* parent = nullptr);
  ~PluginManager();
  bool loadPlugin(const QString& path);
  void loadPlugins(const QString& dir);
  std::vector<ArtifactDetector*> detectors() const;

private:
  std::vector<ArtifactDetector*> m_detectors;
  std::vector<QLibrary*> m_libs;
};

#endif // VAST_PLUGINMANAGER_H
