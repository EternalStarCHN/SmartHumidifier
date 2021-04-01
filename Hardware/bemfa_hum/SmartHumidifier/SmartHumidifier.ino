#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>     

//巴法云服务器地址默认即可
#define TCP_SERVER_ADDR "bemfa.com"
//服务器端口，tcp创客云端口8344
#define TCP_SERVER_PORT "8344"

//********************需要修改的部分*******************//
//WIFI名称，区分大小写，不要写错
#define DEFAULT_STASSID  "TP-LINK_DF5B"
//WIFI密码
#define DEFAULT_STAPSW   "yx990510"
//用户私钥，可在控制台获取,修改为自己的UID
#define UID  "b9e4ceb2c84ab8e8368d1a88e352540b"
//主题名字，可在控制台新建
#define TOPIC  "Humidifier003"
//单片机引脚值
const int Hum_Pin = 4;//加湿器控制引脚(LOW:运行;HIGH:停止)
const int Con_Pin = 5;//模块联网状态(LOW:连接;HIGH:断开)
//**************************************************//

//最大字节数
#define MAX_PACKETSIZE 512
//设置心跳值30s
#define KEEPALIVEATIME 30*1000

//tcp客户端相关初始化，默认即可
WiFiClient TCPclient;
String TcpClient_Buff = "";
unsigned int TcpClient_BuffIndex = 0;
unsigned long TcpClient_preTick = 0;
unsigned long preHeartTick = 0;//心跳
unsigned long preTCPStartTick = 0;//连接
bool preTCPConnected = false;

//相关函数初始化
//连接WIFI
unsigned int WifiXTimes = 0;
void doWiFiTick();
void startSTA();

//TCP初始化连接
void doTCPClientTick();
void startTCPClient();
void sendtoTCPServer(String p);

//led 控制函数
void turnOnLed();
void turnOffLed();

/*
  *发送数据到TCP服务器
 */
void sendtoTCPServer(String p){
  
  if (!TCPclient.connected()) 
  {
    Serial.println("Client is not readly");
    return;
  }
  TCPclient.print(p);
  Serial.println("[Send to TCPServer]:String");
  Serial.println(p);
}

/*
  *初始化和服务器建立连接
*/
void startTCPClient(){
  if(TCPclient.connect(TCP_SERVER_ADDR, atoi(TCP_SERVER_PORT))){
    Serial.print("\nConnected to server:");
    Serial.printf("%s:%d\r\n",TCP_SERVER_ADDR,atoi(TCP_SERVER_PORT));
    char tcpTemp[128];
    sprintf(tcpTemp,"cmd=1&uid=%s&topic=%s\r\n",UID,TOPIC);

    sendtoTCPServer(tcpTemp);
    preTCPConnected = true;
    preHeartTick = millis();
    TCPclient.setNoDelay(true);
  }
  else{
    Serial.print("Failed connected to server:");
    Serial.println(TCP_SERVER_ADDR);
    TCPclient.stop();
    preTCPConnected = false;
  }
  preTCPStartTick = millis();
}

/*
  *检查数据，发送心跳
*/
void doTCPClientTick(){
 //检查是否断开，断开后重连
  if(WiFi.status() != WL_CONNECTED) return;

  if (!TCPclient.connected()){//断开重连
  digitalWrite(Con_Pin,HIGH);//连接失败熄灭
  if(preTCPConnected == true){
    preTCPConnected = false;
    preTCPStartTick = millis();
    Serial.println();
    Serial.println("TCP Client disconnected.");
    TCPclient.stop();
  }
  else if(millis() - preTCPStartTick > 1*1000)//重新连接
    startTCPClient();
    digitalWrite(Con_Pin,HIGH);
  }
  else
  {
    digitalWrite(Con_Pin,LOW);//连接成功亮灯
    if (TCPclient.available()) {//收数据
      char c =TCPclient.read();
      TcpClient_Buff +=c;
      TcpClient_BuffIndex++;
      TcpClient_preTick = millis();
      
      if(TcpClient_BuffIndex>=MAX_PACKETSIZE - 1){
        TcpClient_BuffIndex = MAX_PACKETSIZE-2;
        TcpClient_preTick = TcpClient_preTick - 200;
      }
      preHeartTick = millis();
    }
    if(millis() - preHeartTick >= KEEPALIVEATIME){//保持心跳
      preHeartTick = millis();
      Serial.println("--Keep alive:");
      sendtoTCPServer("cmd=0&msg=keep\r\n");
    }
  }
  if((TcpClient_Buff.length() >= 1) && (millis() - TcpClient_preTick>=200))
  {//data ready
    TCPclient.flush();
    Serial.println("Buff");
    Serial.println(TcpClient_Buff);
    if((TcpClient_Buff.indexOf("&msg=on") > 0)) {
      turnOnLed();
    }else if((TcpClient_Buff.indexOf("&msg=off") > 0)) {
      turnOffLed();
    }
   TcpClient_Buff="";
   TcpClient_BuffIndex = 0;
  }
}

void startSTA(){
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(DEFAULT_STASSID, DEFAULT_STAPSW);

}

/**************************************************************************
                                 WIFI
***************************************************************************/
/*
  WiFiTick
  检查是否需要初始化WiFi
  检查WiFi是否连接上，若连接成功启动TCP Client
  控制指示灯
*/
void doWiFiTick(){
  static bool startSTAFlag = false;
  static bool taskStarted = false;
  static uint32_t lastWiFiCheckTick = 0;
  
  if (!startSTAFlag) {
    startSTAFlag = true;
    startSTA();
    Serial.printf("Heap size:%d\r\n", ESP.getFreeHeap());
  }
  //未连接1s重连
  if ( WiFi.status() != WL_CONNECTED ) {
    if (millis() - lastWiFiCheckTick > 1000) {
      lastWiFiCheckTick = millis();
      WifiXTimes++;
    }
    if  ( WifiXTimes >= 10){
      WiFiManager wifiManager;
      Serial.printf("AutoConnecting...\r\n");
      wifiManager.autoConnect("SmartHumidifier");
    }
  }
  //连接成功建立
  else {
    if (taskStarted == false) {
      WifiXTimes = 0;
      taskStarted = true;
      Serial.print("Successful connection !!!\r\n");
      Serial.print("ESP8266 Connected to ");
      Serial.println(WiFi.SSID());              // WiFi名称
      Serial.print("\r\nGet IP Address: ");
      Serial.println(WiFi.localIP());
      startTCPClient();
    }
  }
}

//打开加湿器
void turnOnLed(){
  //Serial.println("Turn ON");
  digitalWrite(Hum_Pin,LOW);
}

//关闭加湿器
void turnOffLed(){
  //Serial.println("Turn OFF");
    digitalWrite(Hum_Pin,HIGH);
}

// 初始化，相当于main 函数
void setup() {
  Serial.begin(115200);
  pinMode(Hum_Pin,OUTPUT);
  pinMode(Con_Pin,OUTPUT);
  digitalWrite(Con_Pin,HIGH);//GPIO0引脚初始值
  digitalWrite(Hum_Pin,LOW);//GPIO2引脚初始值
}

//循环
void loop() {
  doWiFiTick();
  doTCPClientTick();
}
