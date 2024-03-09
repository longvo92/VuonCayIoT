#define BLYNK_TEMPLATE_ID "TMPL61f2DzXKa"
#define BLYNK_TEMPLATE_NAME "tuoinuoc"
#define BLYNK_AUTH_TOKEN "v8IK0hEw7DkV-wMcAdNSIODGXAy6KNn8"
#define DHTPIN 2
#define DHTTYPE DHT11

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

const int ctrRelay = 18;
const int moveSensordata = 5;
const int ctrMaiche = 19;
int relayState = LOW;
int maiChestate = LOW;
const int LCD_ADDR = 0x27;
const int LCD_COLUMNS = 16;
const int LCD_ROWS = 2;
const int doAmdat = 32;
const int anhSang = 33;

int kiemTradoam = analogRead(doAmdat);
int percent = map(kiemTradoam, 0, 4095, 0, 100);
int trueper = 100 - percent;
int doAnhsang = analogRead(anhSang);
int percent1 = map(doAnhsang,0, 4095, 0, 100);
int rvprt = 100 - percent1;

WidgetRTC rtc;
DHT dht(DHTPIN, DHTTYPE);
float doAm = dht.readHumidity();
float nhietDo = dht.readTemperature();
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLUMNS, LCD_ROWS);
char auth[] = "v8IK0hEw7DkV-wMcAdNSIODGXAy6KNn8";

void kiemSoatmaiche(){
  int currentHour = hour();
  if (currentHour==5 && maiChestate == HIGH){       // Buổi sáng mở mái che cho cây đón nắng
    maiChestate = LOW;
    digitalWrite(ctrMaiche,maiChestate);
  };
  if (currentHour==18 && maiChestate == LOW){        // Buổi tối sẽ che cho cây
    maiChestate = HIGH;
    digitalWrite(ctrMaiche,maiChestate);
  };
  if (currentHour>7 && currentHour<18 && nhietDo<28 && rvprt <20){ // Khi nhiệt độ ngoài trời thấp và thiếu ánh sáng thì sẽ kéo mái che ra
    maiChestate = LOW;
    digitalWrite(ctrMaiche,maiChestate);
  };
  if (nhietDo>32){                                  // Nhiệt độ cao sẽ che cho cây đỡ nóng
    maiChestate = HIGH;
    digitalWrite(ctrMaiche,maiChestate);
  };
  if (trueper <50){                                // Kiểm tra độ ẩm đất, nếu thấp sẽ tưới nước
    relayState = HIGH;
    digitalWrite(ctrRelay,relayState);
  }
  else {
    relayState = LOW;
    digitalWrite(ctrRelay,relayState);
  }
  Serial.println("Tinh trang mai che: ");
  Serial.print(maiChestate);
  if(maiChestate==HIGH){
    Blynk.virtualWrite(V6,"Đang che");
  }
  else Blynk.virtualWrite(V6,"Đang không che");
}

void camBiencd(){
  int currentHour = hour();
  static int kiemtra = 0;
  static int soLuong = 0;
  int motionCatch = digitalRead(moveSensordata);        // Cảm biến phát hiện chuyển động
  if(motionCatch == 1 && kiemtra == 0){                 // Gửi tổng số lần phát hiện chuyển động lên cloud
    kiemtra = 1;
    soLuong = soLuong + 1;  
    Serial.print("Phát Hiện chuyển động");  
  }
  if (motionCatch == 0 && kiemtra == 1){              
    kiemtra=0;
  }
  if (currentHour == 1){                                // 1 giờ sáng hằng ngày sẽ reset tổng số lần phát hiện
    soLuong = 0;
  }
  Blynk.virtualWrite(V0,soLuong);
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, "Iphone", "12345678");
  Wire.begin();
  pinMode(ctrRelay,OUTPUT);
  digitalWrite(ctrRelay,relayState);
  rtc.begin();
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
  lcd.setCursor(0, 0);
  lcd.print("Hello, ESP32!");
  Serial.print("Dang bat");
  delay(5000);
}

void loop() {
  Blynk.run();
  kiemTradoam = analogRead(doAmdat);
  percent = map(kiemTradoam, 0, 4095, 0, 100);
  trueper = 100 - percent;
  doAnhsang = analogRead(anhSang);
  percent1 = map(doAnhsang,0, 4095, 0, 100);
  rvprt = 100 - percent1;
  lcd.clear();
  doAm = dht.readHumidity();
  nhietDo = dht.readTemperature();
  camBiencd();
  if (!isnan(percent)){   // Hiển thị độ ẩm đất theo % từ 0-100%
    Blynk.virtualWrite(V4, trueper);
    lcd.setCursor(0,0);
    lcd.print("Do am dat: "); 
    lcd.print(trueper);
    lcd.print(" %");
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("Do am dat loi!  "); 
  }
  if (!isnan(doAnhsang)){           // Hiển thị cường độ ánh sáng theo thang đo 0-100%
    Blynk.virtualWrite(V5, rvprt);
    lcd.setCursor(0,1);
    lcd.print("Anh sang: "); 
    lcd.print(rvprt);
  }
  else{
    lcd.setCursor(0,1);
    lcd.print("Anh sang loi!   "); 
  }

  delay(3000);
  camBiencd();
  lcd.clear();
  if (!isnan(doAm) && !isnan(nhietDo)) {   // Hiện thị nhiệt độ, độ ẩm theo DHT11
    Blynk.virtualWrite(V2, nhietDo);
    Blynk.virtualWrite(V3, doAm);    
    lcd.setCursor(0, 0);
    lcd.print("Nhiet do: ");
    lcd.print(nhietDo);
    lcd.print(" C");
  
    lcd.setCursor(0, 1);
    lcd.print("Do am: ");
    lcd.print(doAm);
    lcd.print(" %");
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("DHT11 not found");
  }

  delay(3000);
  kiemSoatmaiche();
}

BLYNK_WRITE(V1) {
  int Button = param.asInt();
  if(Button==HIGH){
  relayState = HIGH;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dang bat relay");
  delay(1000);
  lcd.clear();
  }
  else {
    relayState = LOW;
  }
  digitalWrite(ctrRelay,relayState);
}
BLYNK_READ(V0) {
  int motionCatch = digitalRead(moveSensordata);
  Serial.print("Dang quet");
  Blynk.virtualWrite(V0,motionCatch);
}
BLYNK_CONNECTED(){
  rtc.begin();
  Serial.print( " Dang dong bo thoi gian ");
}
