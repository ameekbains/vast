#include "ReportGenerator.h"
#include <QFile>
#include <QTextStream>

bool ReportGenerator::generateHtml(const QString& file, const std::vector<QString>& images)
{
    QFile f(file);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&f);
    out << "<html><body>\n";
    for (const auto& img : images) {
        out << "<img src='" << img << "'/><br/>\n";
    }
    out << "</body></html>\n";
    return true;
}
