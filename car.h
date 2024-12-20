#ifndef CAR_H
#define CAR_H

#include<QString>

const QString setStatusTip[34] = {
    "京", "津", "冀", "晋", "蒙", "辽", "吉", "黑",
    "沪", "苏", "浙", "皖", "闽", "赣", "鲁", "豫",
    "鄂", "湘", "粤", "桂", "琼", "渝", "川", "贵",
    "云", "藏", "陕", "甘", "青", "宁", "新", "港", "澳", "台"
};

enum class carPlace
{
    BeiJigng = 0, TianJin = 1, HeBei = 2, Shan1Xi = 3, NeiMenGu = 4,
    LiaoNing = 5, JiLin = 6, HeiLongJiang = 7, ShangHai = 8, JiangSu = 9,
    ZheJiang = 10, AnHui = 11, FuJian = 12, JiangXi = 13, ShanDong = 14,
    HeNan = 15, HuBei = 16, HuNan = 17, GuangDong = 18, GuangXi = 19,
    HaiNan = 20, ChongQing = 21, SiChuan = 22, GuiZhou = 23, YunNan = 24,
    XiZang = 25, Shan3Xi = 26, GanSu = 27, QingHai = 28, NingXia = 29,
    XinJiang = 30, XiangGang = 31, AoMen = 32, TaiWan = 33
};

class Car
{
private:
    carPlace _place;
    QString _plate_num;
public:
    Car(carPlace place, QString plate_num); // 指定车牌号
    Car();        // 无指定，随机生成
    void show(); const
    inline carPlace getPlace() const
    {
        return _place;
    }
    inline QString getPlate_num() const
    {
        return _plate_num;
    }
    inline bool operator==(Car other)
    {
        return _place == other._place && _plate_num == other._plate_num;
    }
    QString toString();
};

#endif // CAR_H
