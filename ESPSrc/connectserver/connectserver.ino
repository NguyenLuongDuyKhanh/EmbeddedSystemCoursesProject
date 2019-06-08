#include <ESP8266WiFi.h>
#include <SocketIOClient.h>
#include <HardwareSerial.h>
#include <ArduinoJson.h>
#include <String.h>
SocketIOClient client;
//const char* ssid = "UIT_Guest";          //Tên mạng Wifi mà Socket server của bạn đang kết nối
//const char* password = "1denmuoi1";  //Pass mạng wifi ahihi, anh em rãnh thì share pass cho mình với.

const char* ssid = "khanh";
const char* password = "123456789";

//const char* ssid = "UP BKHCM";
//const char* password = "Start@Up";

//const char* ssid = "Do_biet_nha_ai!!";
//const char* password = "02862550020";

char host[] = "13.250.12.60";  //Địa chỉ IP dịch vụ, hãy thay đổi nó theo địa chỉ IP Socket server của bạn.
int port = 65432;                  //Cổng dịch vụ socket server do chúng ta tạo!
 
//từ khóa extern: dùng để #include các biến toàn cục ở một số thư viện khác. Trong thư viện SocketIOClient có hai biến toàn cục
// mà chúng ta cần quan tâm đó là
// RID: Tên hàm (tên sự kiện
// Rfull: Danh sách biến (được đóng gói lại là chuối JSON)
extern String RID;
extern String Rfull;
 
 
//Một số biến dùng cho việc tạo một task
unsigned long previousMillis = 0;
long interval = 2000;
String str;

void setup()
{
    //Bật baudrate ở mức 115200 để giao tiếp với máy tính qua Serial
    
    Serial.begin(9600);
    delay(10);
    StaticJsonBuffer<100> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["Time"] = 5;
    root["Temp"] = 6;
    root["Hum"] = 7;
    root["Bat"] = 8;
    
    root.printTo(str);
    Serial.print(str);
    //Việc đầu tiên cần làm là kết nối vào mạng Wifi
    Serial.print("Ket noi vao mang ");
    Serial.println(ssid);
 
    //Kết nối vào mạng Wifi
    WiFi.begin(ssid, password);
 
    //Chờ đến khi đã được kết nối
    while (WiFi.status() != WL_CONNECTED) { //Thoát ra khỏi vòng 
        delay(500);
        Serial.print('.');
    }
 
    Serial.println();
    Serial.println(F("Da ket noi WiFi"));
    Serial.println(F("Di chi IP cua ESP8266 (Socket Client ESP8266): "));
    Serial.println(WiFi.localIP());

    client.connect(host, port);
    //client.send("atime", "message", "{ "fruit": "Apple", "size": "Large", "color": "Red" }");
    client.send("atime", "message",str);
    //client.sendMessage(str);
    client.disconnect();
}
 
void loop()
{
    if(Serial.available())
    {
      client.connect(host, port);
    }else client.disconnect();
  
//    //tạo một task cứ sau "interval" giây thì chạy lệnh:
//    if (millis() - previousMillis > interval) {
//        //lệnh:
//        previousMillis = millis();
// 
//        //gửi sự kiện "atime" là một JSON chứa tham số message có nội dung là Time please?
//        
//    }
// 
//    //Khi bắt được bất kỳ sự kiện nào thì chúng ta có hai tham số:
//    //  +RID: Tên sự kiện
//    //  +RFull: Danh sách tham số được nén thành chuỗi JSON!
//    if (client.monitor()) {
//        Serial.println(RID);
//        Serial.println(Rfull);
//    }
// 
//    //Kết nối lại!
//    if (!client.connected()) {
//      client.reconnect(host, port);
//    }
}
