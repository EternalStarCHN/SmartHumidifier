/*******************************************/
/*@版权所有：广州奥松电子有限公司          */
/*@作者：温湿度传感器事业部                */
/*@版本：V1.2                              */
/*******************************************/
/*******************************************/
/*@版本说明：                              */
/*@版本号：V1.2 修改AC命令的参数。         */
/*@版本号：V1.1 增加校准输出使能检测。     */
/*@版本号：V1.0 最初版本。                 */
/*******************************************/



void Delay_N10us(uint32_t t)//延时函数
{
  uint32_t k;

   while(t--)
  {
    for (k = 0; k < 2; k++)//110
      ;
  }
}



void SensorDelay_us(uint32_t t)//延时函数
{
	t = t-2;	
	for(; t>0; t--)
	{
		Delay_N10us(1);
	}

}

void Delay_3us(void)		//延时函数
{	
	Delay_N10us(1);
	Delay_N10us(1);
	Delay_N10us(1);
	Delay_N10us(1);
}
void Delay_1us(void)		//延时函数
{	
	Delay_N10us(1);
	Delay_N10us(1);
	Delay_N10us(1);
	Delay_N10us(1);
	Delay_N10us(1);

}


void SDA_Pin_Output_High(void)   //将P15配置为输出 ， 并设置为高电平， P15作为I2C的SDA
{

 Gpio_InitIOExt(1,5,GpioDirOut,TRUE, FALSE, TRUE, FALSE);//config P15 to output
 Gpio_SetIO(1,5,1); 
}

void SDA_Pin_Output_Low(void)  //将P15配置为输出  并设置为低电平
{
 Gpio_InitIOExt(1,5,GpioDirOut,TRUE, FALSE, TRUE, FALSE);//config P15 to output
 Gpio_SetIO(1,5,0);  
}

void SDA_Pin_IN_FLOATING(void)  //SDA配置为悬浮输入
{
 Gpio_InitIO(1, 5, GpioDirIn);
}



void SCL_Pin_Output_High(void) //SCL输出高电平，P14作为I2C的SCL
{
 Gpio_SetIO(1, 4, 1);
}

void SCL_Pin_Output_Low(void) //SCL输出低电平
{
 Gpio_SetIO(1, 4, 0);
}

void Init_I2C_Sensor_Port(void) //初始化I2C接口
{	

 Gpio_InitIOExt(1,5,GpioDirOut,TRUE, FALSE, TRUE, FALSE);//将P15配置为开漏输出  并设置为高电平
 Gpio_SetIO(1,5,1);
	

 Gpio_InitIOExt(1,4,GpioDirOut,TRUE, FALSE, TRUE, FALSE);//将P14配置为开漏输出  并设置为高电平
 Gpio_SetIO(1,4,1);
	
}


void I2C_Start(void)		 //I2C主机发送START信号
{
 SDA_Pin_Output_High();
 SensorDelay_us(8);
 SCL_Pin_Output_High();
 SensorDelay_us(8);
 SDA_Pin_Output_Low();
 SensorDelay_us(8);
 SCL_Pin_Output_Low();
 SensorDelay_us(8);   
}


void ZSSC_I2C_WR_Byte(uint8_t Byte) //往AHT10写一个字节
{
	uint8_t Data,N,i;	
	Data=Byte;
	i = 0x80;
	for(N=0;N<8;N++)
	{
		SCL_Pin_Output_Low();
	  
		Delay_3us();	
		
		if(i&Data)
		{
			SDA_Pin_Output_High();
		}
		else
		{
			SDA_Pin_Output_Low();
		}	
			
        SCL_Pin_Output_High();
		Delay_3us();
		
		Data <<= 1;
		 
	}
	SCL_Pin_Output_Low();
	SensorDelay_us(8);   
	SDA_Pin_IN_FLOATING();
	SensorDelay_us(8);	
}	


uint8_t ZSSC_I2C_RD_Byte(void)//从AHT10读取一个字节
{
	uint8_t Byte,i,a;
	Byte = 0;
	SCL_Pin_Output_Low();
	SDA_Pin_IN_FLOATING();
	SensorDelay_us(8);	
	for(i=0;i<8;i++)
	{
    SCL_Pin_Output_High();		
		Delay_1us();
		a=0;
		if(Gpio_GetIO(1,5))a=1;
		Byte = (Byte<<1)|a;
		SCL_Pin_Output_Low();
		Delay_1us();
	}
    SDA_Pin_IN_FLOATING();
	SensorDelay_us(8);	
	return Byte;
}


uint8_t Receive_ACK(void)   //看AHT10是否有回复ACK
{
	uint16_t CNT;
	CNT = 0;
	SCL_Pin_Output_Low();	
	SDA_Pin_IN_FLOATING();
	SensorDelay_us(8);	
	SCL_Pin_Output_High();	
	SensorDelay_us(8);	
	while((Gpio_GetIO(1,5))  && CNT < 100) 
	CNT++;
	if(CNT == 100)
	{
		return 0;
	}
 	SCL_Pin_Output_Low();	
	SensorDelay_us(8);	
	return 1;
}

void Send_ACK(void)		  //主机回复ACK信号
{
	SCL_Pin_Output_Low();	
	SensorDelay_us(8);	
	SDA_Pin_Output_Low();
	SensorDelay_us(8);	
	SCL_Pin_Output_High();	
	SensorDelay_us(8);
	SCL_Pin_Output_Low();	
	SensorDelay_us(8);
	SDA_Pin_IN_FLOATING();
	SensorDelay_us(8);
}

void Send_NOT_ACK(void)	//主机不回复ACK
{
	SCL_Pin_Output_Low();	
	SensorDelay_us(8);
	SDA_Pin_Output_High();
	SensorDelay_us(8);
	SCL_Pin_Output_High();	
	SensorDelay_us(8);		
	SCL_Pin_Output_Low();	
	SensorDelay_us(8);
    SDA_Pin_Output_Low();
	SensorDelay_us(8);
}

void Stop_I2C(void)	  //一条协议结束
{
	SDA_Pin_Output_Low();
	SensorDelay_us(8);
	SCL_Pin_Output_High();	
	SensorDelay_us(8);
	SDA_Pin_Output_High();
	SensorDelay_us(8);
}

uint8_t JH_Read_Status(void)//读取AHT10的状态寄存器
{

	uint8_t Byte_first;	
	I2C_Start();
	ZSSC_I2C_WR_Byte(0x71);
	Receive_ACK();
	Byte_first = ZSSC_I2C_RD_Byte();
		

	Send_NOT_ACK();
	Stop_I2C();


	return Byte_first;
}

uint8_t JH_Read_Cal_Enable(void)  //查询cal enable位有没有使能？
{
	uint8_t val = 0;//ret = 0,
 
  val = JH_Read_Status();
  if((val & 0x68)==0x08)  //判断NOR模式和校准输出是否有效
  return 1;
  else  return 0;
 }



void JH_SendAC(void) //向AHT10发送AC命令
{

 I2C_Start();
 ZSSC_I2C_WR_Byte(0x70);
 Receive_ACK();
 ZSSC_I2C_WR_Byte(0xac);
 Receive_ACK();
 ZSSC_I2C_WR_Byte(0x33);
 Receive_ACK();
 ZSSC_I2C_WR_Byte(0x00);
 Receive_ACK();
 Stop_I2C();

}

void JH_Send_BA(void)//向AHT10发送BA命令
{


 I2C_Start();
 ZSSC_I2C_WR_Byte(0x70);
 Receive_ACK();
 ZSSC_I2C_WR_Byte(0xba);
 Receive_ACK();
 Stop_I2C();


}

void JH_Read_CTdata(uint32_t *ct) //读取AHT10的温度和湿度数据
{
	volatile uint8_t  Byte_1th=0;
	volatile uint8_t  Byte_2th=0;
	volatile uint8_t  Byte_3th=0;
	volatile uint8_t  Byte_4th=0;
	volatile uint8_t  Byte_5th=0;
	volatile uint8_t  Byte_6th=0;
	 uint32_t RetuData = 0;
	
	uint16_t cnt = 0;


	JH_SendAC();//向AHT10发送AC命令

	delay_ms(75);//等待75ms
    cnt = 0;
	while(((JH_Read_Status()&0x80)==0x80))//等待忙状态结束
	{
	 SensorDelay_us(1508);
	 if(cnt++>=100)
	 {
	  break;
	  }
	}
	I2C_Start();

	ZSSC_I2C_WR_Byte(0x71);//0x70+1   0x70为设备地址 1为方向位
	Receive_ACK();
	Byte_1th = ZSSC_I2C_RD_Byte();//状态字
	Send_ACK();
	Byte_2th = ZSSC_I2C_RD_Byte();//湿度字节
	Send_ACK();
	Byte_3th = ZSSC_I2C_RD_Byte();//湿度字节
	Send_ACK();
	Byte_4th = ZSSC_I2C_RD_Byte();//高4位为湿度  低4位为温度
	Send_ACK();
	Byte_5th = ZSSC_I2C_RD_Byte();//温度字节
	Send_ACK();
	Byte_6th = ZSSC_I2C_RD_Byte();//温度字节
	Send_NOT_ACK();
	Stop_I2C();

	RetuData = (RetuData|Byte_2th)<<8;
	RetuData = (RetuData|Byte_3th)<<8;
	RetuData = (RetuData|Byte_4th);
	RetuData =RetuData >>4;
	ct[0] = RetuData;
	RetuData = 0;
	RetuData = (RetuData|Byte_4th)<<8;
	RetuData = (RetuData|Byte_5th)<<8;
	RetuData = (RetuData|Byte_6th);
	RetuData = RetuData&0xfffff;
	ct[1] =RetuData; 

}


u8 JH_Init(void)   //初始化AHT10
{

	
	Init_I2C_Sensor_Port();
	SensorDelay_us(11038);

	I2C_Start();
	ZSSC_I2C_WR_Byte(0x70);
	Receive_ACK();
	ZSSC_I2C_WR_Byte(0xe1);//写系统配置寄存器
	Receive_ACK();
	ZSSC_I2C_WR_Byte(0x08);
	Receive_ACK();
	ZSSC_I2C_WR_Byte(0x00);
	Receive_ACK();
	Stop_I2C();

	delay_ms(500);//延时0.5S
   while(JH_Read_Cal_Enable()==0)//需要等待状态字status的Bit[3]=1时才去读数据。如果Bit[3]不等于1 ，发软件复位0xBA给AHT10，再重新初始化AHT10，直至Bit[3]=1
   {
    
	JH_Send_BA();  //复位
	delay_ms(100);
	SensorDelay_us(11038);

	I2C_Start();
	ZSSC_I2C_WR_Byte(0x70);
	Receive_ACK();
	ZSSC_I2C_WR_Byte(0xe1);//写系统配置寄存器
	Receive_ACK();
	ZSSC_I2C_WR_Byte(0x08);
	Receive_ACK();
	ZSSC_I2C_WR_Byte(0x00);
	Receive_ACK();
	Stop_I2C();
	count++;
	if(count>=10)return 0;
	delay_ms(500);
    }
   return 1;
}

int32_t main(void)
{
 uint32_t CT_data[2];
	volatile int  c1,t1;
	u8 ret=0;
	ret = JH_Init(); //初始化
	if(ret == 0)
	{
	 LCD_display("ERROR"):
	 while(1);
	 }
	
	while(1)
	{
	 while(JH_Read_Cal_Enable()==0)//等到校准输出使能位为1，才读取。
	 {
	  JH_Init();//如果为0再使能一次
      delay_ms(30);
	 }
	 //DisableIrq(); //由于是模拟I2C,为读取数据更准确 ，读取之前禁止中断
	 JH_Read_CTdata(CT_data);  //读取温度和湿度 ， 可间隔1.5S读一次
	 c1 = CT_data[0]*1000/1024/1024;  //计算得到湿度值（放大了10倍,如果c1=523，表示现在湿度为52.3%）
	 t1 = CT_data[1] *200*10/1024/1024-500;//计算得到温度值（放大了10倍，如果t1=245，表示现在温度为24.5℃）
	 //EnableIrq(); //恢复中断
	 delay_ms(1500); //延时1.5S
	 
	 //为读取的数据更稳定，还可以使用平均值滤波或者窗口滤波，或者前面读取的值与后面的值相差不能太大。
	 }
	

 }	
