#include "ArtifactDetector.h"
#include <QString>
#include <QtGlobal>

class ExampleDetector : public ArtifactDetector {
public:
    QString name() const override { return "ExampleDetector"; }
    bool initialize(int width, int height) override { Q_UNUSED(width); Q_UNUSED(height); return true; }
    void processFrame(const unsigned char*, int, int) override {}
    float lastScore() const override { return 0.f; }
};

extern "C" ArtifactDetector* createDetector() {
    return new ExampleDetector();
}
