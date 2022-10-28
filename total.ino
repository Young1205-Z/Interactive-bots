#include "pitches.h";
//欢乐斗地主
//定义音高低
short melody[] = {
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_A3, NOTE_G3, NOTE_A3, NOTE_A3, NOTE_G3, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4
};
//定义音长，8表示8分音符
byte noteDurations[] = {
  8, 16, 16, 8, 8, 2, 8, 16, 16, 8, 8, 2, 8, 16, 16, 8, 8, 8, 8, 8, 8, 16 / 3, 16, 8, 8, 2, 8, 16, 16, 8
};
int buzzer = A5;
int itoneLen;  //蜂鸣器模块

#include <Servo.h>
int pos1;
Servo myservo1;
int pos2;
Servo myservo2;
int pos3;
Servo myservo3;
int pos4;
Servo myservo4;  //舵机模块

int swch0 = 2;
int swch1 = 3;  //开关模块

int redout = A0;  //人体红外模块

int string = 8;
int echo = 7;  //超声测距模块

int in1 = A1;
int in2 = A2;
int in3 = A3;
int in4 = A4;
int ENA = 5;
int ENB = 6;  //移动驱动模块

int t;               //次数
long randNumber;     //随机数
int touchTimes = 1;  //开关次数记录
int lastState = 0;   //上次开关状态

void setup() {
  // Serial.begin(9600);
  // put your setup code here, to run once:

  itoneLen = sizeof(melody) / sizeof(melody[0]);
  pinMode(buzzer, OUTPUT);  //蜂鸣器模块

  myservo1.attach(9, 500, 2500);
  myservo2.attach(10, 500, 2500);
  myservo3.attach(11, 500, 2500);
  myservo4.attach(12, 500, 2500);  //修正脉冲宽度，设置舵机端口

  pinMode(swch0, INPUT_PULLUP);
  pinMode(swch1, INPUT_PULLUP);  //设置开关端口

  pinMode(redout, INPUT);  //设置红外端口

  pinMode(string, OUTPUT);
  pinMode(echo, INPUT);  //设置超声测距端口

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);  //驱动模块

  myservo1.write(100);
  myservo2.write(120);
  myservo3.write(175);
  myservo4.write(75);  //舵机控制闭合
}

void loop() {
  //put your main code here, to run repeatedly:
  // Serial.print(Dis()); 不换行
  // Serial.println("cm"); 换行

  if (lastState != digitalRead(swch0)) {
    lastState = digitalRead(swch0);
    randNumber = random(0, 10);
    if (randNumber >= 0 && randNumber < 1) {
      delay(1000);
      byTouch(20);  //慢挠头
    } else if (randNumber >= 1 && randNumber < 2) {
      delay(1000);
      byTouch(10);  //快挠头
    } else if (randNumber >= 2 && randNumber < 3) {
      delay(1000);
      goBack();
      delay(1000);
      treat();
      touch(20);
      delay(3000);
      getBack(5);  //后退调戏
    } else if (randNumber >= 3 && randNumber < 4) {
      delay(1000);
      goBack();
      handUp();
      turnAround();
      delay(2000);
      handDown();  //后退举旗转圈
    } else if (randNumber >= 4 && randNumber < 5) {
      delay(1000);
      goBack();
      akimbo();
      handUp();
      delay(3000);
      akimboBack();
      handDown();  //后退叉腰举旗
    } else if (randNumber >= 5 && randNumber < 6) {
      delay(1000);
      goBack();
      delay(1000);
      treat();
      delay(1000);
      goBack();
      delay(1000);
      follow();  //调戏跟随
    } else if (randNumber >= 6 && randNumber < 7) {
      delay(1000);
      touch(5);
      turnAround();
      delay(1000);
      getBack(5);  //挠头转圈
    } else if (randNumber >= 7 && randNumber < 8) {
      delay(1000);
      akimbo();
      turnAround();
      delay(1000);
      akimboBack();  //叉腰转圈
    } else if (randNumber >= 8 && randNumber < 9) {
      delay(1000);
      handUp();
      music();
      goBack();
      handDown();  //举旗放音乐
    } else {
      delay(1000);
      turnCircle();  //绕人一圈
    }
  } else {
    delay(1000);
  }
}  //主循环程序

int Dis() {
  digitalWrite(string, LOW);
  delayMicroseconds(2);  //本段语句的目的先拉低Trig，然后发送10us的高电平信号去触发超声波传感器
  digitalWrite(string, HIGH);
  delayMicroseconds(10);
  digitalWrite(string, LOW);
  int distance = pulseIn(echo, HIGH) / 58.0;  //本语句的含义是计算距离并换算成厘米
  return distance;
}  //返回测距
void touch(int x) {
  for (pos4 = 75; pos4 <= 100; pos4++) {
    myservo4.write(pos4);
    delay(x);
  }
  for (int i = 0, a = 120, b = 175; i < 50; i++, a -= 1, b -= 1) {

    for (pos2 = a; pos2 >= (a - 1); pos2--) {
      myservo2.write(pos2);
      delay(5);
    }
    for (pos3 = b; pos3 >= (b - 1); pos3--) {
      myservo3.write(pos3);
      delay(5);
    }
  }
  for (pos4 = 100; pos4 >= 50; pos4--) {
    myservo4.write(pos4);
    delay(x);
  }
  for (pos3 = 125; pos3 >= 30; pos3--) {
    myservo3.write(pos3);
    delay(x);
  }
  for (pos4 = 50; pos4 >= 10; pos4--) {
    myservo4.write(pos4);
    delay(x);
  }
  for (int i = 0, a = 30, b = 10; i < 10; i++, a -= 3, b -= 1) {

    for (pos4 = b; pos4 >= (b - 1); pos4--) {
      myservo4.write(pos4);
      delay(5);
    }
    for (pos3 = a; pos3 >= (a - 3); pos3--) {
      myservo3.write(pos3);
      delay(10);
    }
  }
  for (pos4 = 0; pos4 <= 10; pos4++) {
    myservo4.write(pos4);
    delay(x);
  }
  for (int i = 0; i < 2; i++) {
    for (pos4 = 10; pos4 <= 20; pos4++) {
      myservo4.write(pos4);
      delay(x);
    }
    for (pos3 = 0; pos3 <= 20; pos3++) {
      myservo3.write(pos3);
      delay(x);
    }
    for (pos4 = 20; pos4 >= 10; pos4--) {
      myservo4.write(pos4);
      delay(x);
    }
    for (pos3 = 20; pos3 >= 0; pos3--) {
      myservo3.write(pos3);
      delay(x);
    }
  }
}  //摸头
void getBack(int x) {
  for (pos4 = 10; pos4 >= 0; pos4--) {
    myservo4.write(pos4);
    delay(x);
  }
  for (int i = 0, a = 0, b = 0; i < 10; i++, a += 3, b += 1) {
    for (pos3 = a; pos3 <= (a + 3); pos3++) {
      myservo3.write(pos3);
      delay(10);
    }
    for (pos4 = b; pos4 <= (b + 1); pos4++) {
      myservo4.write(pos4);
      delay(5);
    }
  }
  for (pos4 = 10; pos4 <= 50; pos4++) {
    myservo4.write(pos4);
    delay(x);
  }
  for (pos3 = 30; pos3 <= 125; pos3++) {
    myservo3.write(pos3);
    delay(x);
  }
  for (pos4 = 50; pos4 <= 100; pos4++) {
    myservo4.write(pos4);
    delay(x);
  }
  for (int i = 0, a = 70, b = 125; i < 50; i++, a += 1, b += 1) {
    for (pos3 = b; pos3 <= (b + 1); pos3++) {
      myservo3.write(pos3);
      delay(5);
    }
    for (pos2 = a; pos2 <= (a + 1); pos2++) {
      myservo2.write(pos2);
      delay(5);
    }
  }
  for (pos4 = 100; pos4 >= 75; pos4--) {
    myservo4.write(pos4);
    delay(x);
  }
}  //放回
void akimbo() {
  for (pos4 = 75; pos4 <= 100; pos4++) {
    myservo4.write(pos4);
    delay(30);
  };
  for (int i = 0, a = 120, b = 175; i < 50; i++, a -= 1, b -= 1) {
    for (pos2 = a; pos2 >= (a - 1); pos2--) {
      myservo2.write(pos2);
      delay(5);
    }
    for (pos3 = b; pos3 >= (b - 1); pos3--) {
      myservo3.write(pos3);
      delay(5);
    }
  };
  for (pos4 = 100; pos4 >= 15; pos4--) {
    myservo4.write(pos4);
    delay(10);
  };
}  //叉腰
void akimboBack() {
  for (pos4 = 15; pos4 <= 100; pos4++) {
    myservo4.write(pos4);
    delay(30);
  };
  for (int i = 0, a = 70, b = 125; i < 50; i++, a += 1, b += 1) {
    for (pos3 = b; pos3 <= (b + 1); pos3++) {
      myservo3.write(pos3);
      delay(5);
    }
    for (pos2 = a; pos2 <= (a + 1); pos2++) {
      myservo2.write(pos2);
      delay(5);
    }
  }
  for (pos4 = 100; pos4 >= 75; pos4--) {
    myservo4.write(pos4);
    delay(10);
  };
}  //叉腰放回
void turnAround() {
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);  //对驱动进行使能

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(5000);  //进行驱动转圈

  // digitalWrite(in1, LOW);
  // digitalWrite(in2, HIGH);
  // digitalWrite(in3, HIGH);
  // digitalWrite(in4, LOW);
  // delay(1000);  //进行驱动前进

  // digitalWrite(in1, HIGH);
  // digitalWrite(in2, LOW);
  // digitalWrite(in3, LOW);
  // digitalWrite(in4, HIGH);
  // delay(1000);  //进行驱动后退

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  //关机进入下一个循环
}  //原地转圈
void turnCircle() {
  analogWrite(ENA, 255);
  analogWrite(ENB, 128);  //对驱动进行使能

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(10000);  //进行前进绕一圈

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  //关机进入下一个循环
}  //绕一圈
void goBack() {
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);  //对驱动进行使能

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2000);  //进行驱动后退

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  //关机进入下一个循环
}  //后退
void goFront() {
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);  //对驱动进行使能

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(2000);  //进行驱动前进

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  //关机进入下一个循环
}  //前进
void treat() {
  t = 0;
  while (t < 2) {
    if (Dis() < 10 && analogRead(redout) > 0) {
      goBack();
      t++;
      delay(2000);
    }
  }
}  //检测，两次退后程序
void follow() {
  t = 0;
  while (t < 2) {
    if (Dis() > 200) {
      goFront();
      t++;
      delay(2000);
    }
  }
}  //跟随
void byTouch(int x) {
  touch(x);
  getBack(x);
  delay(1000);
}  //摸头放下完整过程
void handUp() {
  for (pos1 = 100; pos4 <= 180; pos4 += 5) {
    myservo1.write(pos4);
    delay(15);
  }
}  //举旗
void handDown() {
  for (pos1 = 180; pos4 >= 100; pos4 -= 5) {
    myservo1.write(pos4);
    delay(15);
  }
}  //放旗
void music() {
  for (int thisNote = 0; thisNote < itoneLen; thisNote++) {
    int noteDuration = 1.5 * 1000 / noteDurations[thisNote];  // 全音符音长1.5*1000ms，四分音符则除以4
    tone(buzzer, melody[thisNote], noteDuration);             //使用引脚
    int pauseBetweenNotes = noteDuration * 1.30;              //响完一个音后的停顿时间
    delay(pauseBetweenNotes);
    noTone(buzzer);
  }
}  //欢乐斗地主