#pragma once
#include <qstring.h>
#include <qvector.h>

//写csv文件单例类
class CSVWriter
{
public:
    static CSVWriter* GetInstance();

    bool writeCSV(QString filename, const QVector<QPointF>& data);

    ~CSVWriter();

private:
    CSVWriter();

    static CSVWriter* m_instance;
};

