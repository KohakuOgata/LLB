#include "Fps.h"

#include "Config.h"

#include <DxLib.h>

const static int ListLenMax = 120;	//最大120フレームで待機処理を計算する(2以上にすること)
const static int FPS = Config::FPS; //FPS
const static int UpInterval = 60;	//60フレームに一度更新する

Fps::Fps() :counter(0), fps(0) {}

void Fps::Wait()
{
    counter++;
    Sleep(GetWaitTime());   //待つべき時間を取得して待つ
    Regist();
    if (counter == UpInterval) {  //更新タイミングに1回平均値を更新する
        UpdateAverage();
        counter = 0;
    }
}

void Fps::Draw() const
{
    if (fps == 0) {
        return;
    }
    printfDx("%04.1ffps\n\n", fps);
}

void Fps::Regist()
{
    flameTimes.push_back(GetNowCount());   //現在の時刻を記憶
    if (flameTimes.size() > ListLenMax) {  //器から漏れたら前からポップ
        flameTimes.pop_front();
    }
}

unsigned Fps::GetWaitTime() const
{
    int len = (int)flameTimes.size();
    if (len == 0) {
        return 0;
    }
    int shouldTookTime = (int)(1000 / 60.f * (len));            //計算上かかるべき時間
    int actuallyTookTime = GetNowCount() - flameTimes.front();   //実際にかかった時間
    int waitTime = shouldTookTime - actuallyTookTime;       //計算上かかるべき時間 - 実際にかかった時間　はすなわち待つべき時間
    waitTime = waitTime > 0 ? waitTime : 0;
    return (unsigned)(waitTime);
}

void Fps::UpdateAverage() {
    int len = (int)flameTimes.size();
    if (len < ListLenMax) {   //まだ平均を計算するレベルにまでたまっていなければ計算しない
        return;
    }
    int tookTime = flameTimes.back() - flameTimes.front();//LIST_LEN_MAXフレームにかかった時間
    float average = (float)tookTime / (len - 1);//1フレームあたりにかかった時間の平均を取る
    if (average == 0) {//0割り防止
        return;
    }
    fps = 1000 / average;
}