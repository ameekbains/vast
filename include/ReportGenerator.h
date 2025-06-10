#ifndef VAST_REPORTGENERATOR_H
#define VAST_REPORTGENERATOR_H

#include <QString>
#include <vector>

class ReportGenerator {
public:
    bool generateHtml(const QString& file, const std::vector<QString>& images);
};

#endif // VAST_REPORTGENERATOR_H
