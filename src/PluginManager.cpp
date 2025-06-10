#include "PluginManager.h"

PluginManager::PluginManager(QObject* parent)
    : QObject(parent) {}

bool PluginManager::loadPlugin(const QString& path) {
    // TODO: dynamically load plugin and register detectors
    return true;
}

std::vector<ArtifactDetector*> PluginManager::detectors() const {
    return m_detectors;
}
