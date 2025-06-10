#include "PluginManager.h"
#include "ArtifactDetector.h"

#include <QLibrary>
#include <QDebug>

PluginManager::PluginManager(QObject* parent)
    : QObject(parent) {}

PluginManager::~PluginManager() {
    for (auto* lib : m_libs) {
        if (lib->isLoaded())
            lib->unload();
        delete lib;
    }
    for (auto* det : m_detectors)
        delete det;
}

bool PluginManager::loadPlugin(const QString& path) {
    QLibrary* lib = new QLibrary(path);
    if (!lib->load()) {
        qWarning() << "Failed to load plugin" << path << lib->errorString();
        delete lib;
        return false;
    }

    using CreateFn = ArtifactDetector*(*)();
    CreateFn create = (CreateFn)lib->resolve("createDetector");
    if (!create) {
        qWarning() << "Invalid plugin" << path;
        lib->unload();
        delete lib;
        return false;
    }

    ArtifactDetector* det = create();
    if (det) {
        m_detectors.push_back(det);
        m_libs.push_back(lib);
        return true;
    }
    lib->unload();
    delete lib;
    return false;
}

std::vector<ArtifactDetector*> PluginManager::detectors() const {
    return m_detectors;
}
