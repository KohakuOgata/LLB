#include "Fps.h"

#include "Config.h"

#include <DxLib.h>

const static int ListLenMax = 120;	//�ő�120�t���[���őҋ@�������v�Z����(2�ȏ�ɂ��邱��)
const static int FPS = Config::FPS; //FPS
const static int UpInterval = 60;	//60�t���[���Ɉ�x�X�V����

Fps::Fps() :counter(0), fps(0) {}

void Fps::Wait()
{
    counter++;
    Sleep(GetWaitTime());   //�҂ׂ����Ԃ��擾���đ҂�
    Regist();
    if (counter == UpInterval) {  //�X�V�^�C�~���O��1�񕽋ϒl���X�V����
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
    flameTimes.push_back(GetNowCount());   //���݂̎������L��
    if (flameTimes.size() > ListLenMax) {  //�킩��R�ꂽ��O����|�b�v
        flameTimes.pop_front();
    }
}

unsigned Fps::GetWaitTime() const
{
    int len = (int)flameTimes.size();
    if (len == 0) {
        return 0;
    }
    int shouldTookTime = (int)(1000 / 60.f * (len));            //�v�Z�ォ����ׂ�����
    int actuallyTookTime = GetNowCount() - flameTimes.front();   //���ۂɂ�����������
    int waitTime = shouldTookTime - actuallyTookTime;       //�v�Z�ォ����ׂ����� - ���ۂɂ����������ԁ@�͂��Ȃ킿�҂ׂ�����
    waitTime = waitTime > 0 ? waitTime : 0;
    return (unsigned)(waitTime);
}

void Fps::UpdateAverage() {
    int len = (int)flameTimes.size();
    if (len < ListLenMax) {   //�܂����ς��v�Z���郌�x���ɂ܂ł��܂��Ă��Ȃ���Όv�Z���Ȃ�
        return;
    }
    int tookTime = flameTimes.back() - flameTimes.front();//LIST_LEN_MAX�t���[���ɂ�����������
    float average = (float)tookTime / (len - 1);//1�t���[��������ɂ����������Ԃ̕��ς����
    if (average == 0) {//0����h�~
        return;
    }
    fps = 1000 / average;
}