//串口版 MakeyMakey
//修改自: http://www.geek-workshop.com/thread-1192-1-1.html
int InData1 = 0, InData2 = 0, InData3 = 0, InData4 = 0, InData5 = 0, InData0 = 0;  //触摸输入值暂存
int TouchSensitivity = 80; //触摸灵敏度。0~1023，越大越不灵敏
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  //读取所有引脚电压值，并且由于上拉电阻原因，
  //默认所有引脚为最高电平1023，通过触摸拉低引脚电平。
  //所以数值由1024-analogRead(A0);
  InData0 = 1024 - analogRead(A0);                
  InData1 = 1024 - analogRead(A1);
  InData2 = 1024 - analogRead(A2);
  InData3 = 1024 - analogRead(A3);
  InData4 = 1024 - analogRead(A4);
  InData5 = 1024 - analogRead(A5);
  //按照各种可能触发键盘事件
  if(InData0 >= TouchSensitivity)
  {
    Serial.write('a'); //发送字符，支持 ASCII 码
  }
  if(InData1 >= TouchSensitivity)
  {
    Serial.write('s');  
  }
  if(InData2 >= TouchSensitivity)
  {
    Serial.write('d');  
  }
  if(InData3 >= TouchSensitivity)
  {
    Serial.write('w');  
  }
  if(InData4 >= TouchSensitivity)
  {
    Serial.write(' ');  
  }
  if(InData5 >= TouchSensitivity)
  {
    Serial.write(13);  //Enter
  }
  delay(100);   //可根据实际情况增加或减少
}
