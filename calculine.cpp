#include "calculine.h"

CalcuLine::CalcuLine(QObject *parent)
    :QObject(parent)
{

}

CalcuLine::~CalcuLine(){

}

QVector<QPointF> CalcuLine::ConstGapFunc(cv::Mat& mat, float gap)//固定间距
{
    const float scaleRate = 10.f;
    QVector<QPointF> ret;
    cv::Mat tMat;
    float wRate = 1.f * M_AREAWIDTH / mat.cols, hRate = 1.f * M_AREAHEIGHT / mat.rows;
    float rate = (hRate < wRate ? hRate : wRate);
    cv::resize(mat, tMat, cv::Size(mat.cols * rate * scaleRate, mat.rows * rate * scaleRate));	//1位小数
    m_mat=tMat;
    //cv::imshow("test",m_mat);
    int tGap = gap * 10;
    int count = 0;
    bool point_OK;
    for (int i = 0; i < tMat.rows; i += 3*tGap) {
        uchar*pdata = tMat.ptr<uchar>(i);
        for (int j = 0; j < tMat.cols; j += 3*tGap) {
            if (pdata[j] != 0) {
                 j=goPikachu(j,i);
            }
        }
    }

    m_agtNum=count;
    //坐标系回归
    for (auto& i : m_rawPoint) {
        i.setX(i.x() / scaleRate);
        i.setY(i.y() / scaleRate);
    }

    return m_rawPoint;
}

QVector<QPointF> CalcuLine::ConstNumFunc(cv::Mat& mat, int agtNum)//固定人数
{
    const float scaleRate = 10.f;
    QVector<QPointF> ret;
    cv::Mat tMat;
    float wRate = 1.f * M_AREAWIDTH / mat.cols, hRate = 1.f * M_AREAHEIGHT / mat.rows;
    float rate = (hRate < wRate ? hRate : wRate);
    cv::resize(mat, tMat, cv::Size(mat.cols * rate * scaleRate, mat.rows * rate * scaleRate));	//1位小数

    //统计所有点
    int count = 0;
    for (int i = 0; i < tMat.rows; i++) {
        uchar*pdata = tMat.ptr<uchar>(i);
        for (int j = 0; j < tMat.cols; j++) {
            if (pdata[j] != 0)
                count++;
        }
    }
    int gap = sqrt(1.f * count / agtNum);
    bool done = false;

    //迭代直到刚好能把人放进去
    while (!done) {
        count = 0;

        for (int i = 0; i < tMat.rows; i += 3*gap) {
            uchar*pdata = tMat.ptr<uchar>(i);
            for (int j = 0; j < tMat.cols; j += gap) {
                if (pdata[j] != 0) {
                    count++;
                    ret.push_back(QPoint(j, i));
                }

            }

        }

        if (count < agtNum) {
            gap--;
            continue;
        }
        else
            done = true;
    }

    m_gap=gap/scaleRate;
    //m_inputCtrl->SetGap(gap / scaleRate);

    //剪切人数并将坐标系回归
    count = 0;
    for (auto i = ret.begin(); i != ret.end();) {
        count++;
        if (count > agtNum) {
            i = ret.erase(i);
        }
        else {
            i->setX(i->x() / scaleRate);
            i->setY(i->y() / scaleRate);
            i++;
        }
    }

    return ret;
}

int CalcuLine::goPikachu(int x, int y){
    uchar *pdata = m_mat.ptr<uchar>(y);
    int count=0;
    x++;
    while (1) {
        if(pdata[x]!=0){
            count++;
//            if(count%5000==0)//超过最大线段宽度，可能是一条直线
//                m_rawPoint.push_back(QPoint(x,y));
        }
        else{
            //if(count<=5000)
                m_rawPoint.push_back(QPoint(x-count/2,y));
            return x;
        }
        x++;
    }
}

int CalcuLine::getAgtNum(){
    return m_agtNum;
}

float CalcuLine::getGap(){
    return m_gap;
}
