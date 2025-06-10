#ifndef VAST_PLUGINMANAGER_H
#define VAST_PLUGINMANAGER_H

#include <QObject>
#include <QString>
#include <vector>

class ArtifactDetector;

class PluginManager : public QObject {
  Q_OBJECT
public:
  explicit PluginManager(QObject* parent = nullptr);
  bool loadPlugin(const QString& path);
  std::vector<ArtifactDetector*> detectors() const;

private:
  std::vector<ArtifactDetector*> m_detectors;
};

#endif // VAST_PLUGINMANAGER_H
