#include "calcugap.h"

CalcuGap::CalcuGap(QObject *parent)
    :QObject(parent)
{

}

CalcuGap::~CalcuGap(){

}

QVector<QPointF> CalcuGap::ConstGapFunc(cv::Mat& mat, float gap)//固定间距
{
    const float scaleRate = 10.f;
    QVector<QPointF> ret;
    cv::Mat tMat;
    float wRate = 1.f * M_AREAWIDTH / mat.cols, hRate = 1.f * M_AREAHEIGHT / mat.rows;
    float rate = (hRate < wRate ? hRate : wRate);
    cv::resize(mat, tMat, cv::Size(mat.cols * rate * scaleRate, mat.rows * rate * scaleRate));	//1位小数

    int tGap = gap * 10;
    int count = 0;
    int row_count=0;
    int col_count=0;
    for (int i = 0; i < tMat.rows; i += tGap) {
        uchar*pdata = tMat.ptr<uchar>(i);
        col_count=0;
        for (int j = 0; j < tMat.cols; j += tGap) {
            if (pdata[j] != 0&&(row_count%2==0&&col_count%2==0||row_count%2==1&&col_count%2==1)) {
                count++;
                ret.push_back(QPoint(j, i));
            }
            col_count++;
        }
        row_count++;
    }

    m_agtNum=count;
    //坐标系回归
    for (auto& i : ret) {
        i.setX(i.x() / scaleRate);
        i.setY(i.y() / scaleRate);
    }

    return ret;
}

QVector<QPointF> CalcuGap::ConstNumFunc(cv::Mat& mat, int agtNum)//固定人数
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
    count=count/2;
    int gap = sqrt(1.f * count / agtNum);
    bool done = false;
    int row_count=0;
    int col_count=0;
    //迭代直到刚好能把人放进去
    while (!done) {
        count = 0;
        row_count=0;
        for (int i = 0; i < tMat.rows; i += gap) {
            uchar*pdata = tMat.ptr<uchar>(i);
            col_count=0;
            for (int j = 0; j < tMat.cols; j += gap) {
                if (pdata[j] != 0&&(row_count%2==0&&col_count%2==0||row_count%2==1&&col_count%2==1)) {
                    count++;
                    ret.push_back(QPoint(j, i));
                }
                col_count++;
            }
            row_count++;
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

int CalcuGap::getAgtNum(){
    return m_agtNum;
}

float CalcuGap::getGap(){
    return m_gap;
}
