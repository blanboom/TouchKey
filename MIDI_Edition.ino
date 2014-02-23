//MakeyMakey MIDI 版本
//参考了以下两个程序：
//http://www.instructables.com/id/Arduino-Xylophone/
//http://www.geek-workshop.com/thread-1192-1-1.html
//2013.6.1

byte PadNote[6] =
    {60,61,62,63,64,65};          //定义音符
int MaxPlayTime[6] = 
    {90,90,90,90,90,90};          //最长播放时间
int Hitavg = 127;                 //音量，127最大
int TouchSensitivity = 80;        //灵敏度，越大越不灵敏
int Midichannel = 9;              //MIDI通道，9为打击乐器

boolean activePad[6] = 
    {0,0,0,0,0,0};                //记录对应音符是否正在播放
int pinPlayTime[6] =
    {0,0,0,0,0,0};                //记录对应音符播放时间
int inData = 0;                  

void setup()
{
    Serial.begin(9600);              //串口波特率，根据 MIDI 设备调整
}

void loop()
{

    for(int pin = 0; pin < 6; pin++)  
    {
        inData = 1024 - analogRead(pin);
        if(inData >= TouchSensitivity)
        {
            if((activePad[pin] == false))
            {
                MIDI_TX(144,PadNote[pin],Hitavg); //发送音符
                pinPlayTime[pin] = 0;
                activePad[pin] = true;
            }
            else
            {
                pinPlayTime[pin] = pinPlayTime[pin] + 1;
            }
        }
        else if((activePad[pin] == true))
        {
            pinPlayTime[pin] = pinPlayTime[pin] + 1;
            if(pinPlayTime[pin] > MaxPlayTime[pin])
            {
                activePad[pin] = false;
                MIDI_TX(144,PadNote[pin],0);//停止播放该音符
            }
        }
        delay(10);  //根据情况增加或减少
    }
}

//发送 MIDI 信号
void MIDI_TX(byte MESSAGE, byte PITCH, byte VELOCITY)
{
    int status1;
    status1 = MESSAGE + Midichannel;
    Serial.write(status1);
    Serial.write(PITCH);
    Serial.write(VELOCITY);
}
