


#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "usmart.h" 
#include "remote.h"
#include "wkup.h" 
#include "beep.h" 
//ALIENTEK 探索者STM32F407开发板 实验29
//红外遥控 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
 
int main(void)
{    
	u8 key;
	u16 t=0;	
	u8 *str=0;
	u8 ss=0;
	
        u8 a[255]={0};//放置第一个数的数组
	u8 b[255]={0}; //放置第二个数的数组
	u8 flag=0;
	u8 s=0;//操作符对应的按键值
	u16 i=0;//a数组的长度
	u16 j=0;//b数组的长度
	u8 aSum=0;//a 对应的十进制的值
	u8 bSum=0; //b 对应的十进制的值
	//
	u8 x=0;
	u8 y=0;
	u8 len;	
	u16 n=0;
	Stm32_Clock_Init(336,8,2,7);//设置时钟,168Mhz 
	delay_init(168);			//延时初始化  
	uart_init(84,115200);		//初始化串口波特率为115200  	  
	LED_Init();					//初始化LED 
 	LCD_Init();					//LCD初始化 
 	Remote_Init();				//红外接收初始化		 
	BEEP_Init(); 
	
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"first number:");	 
        LCD_ShowString(30,70,200,16,16,"operatCode:");	
        LCD_ShowString(30,90,200,16,16,"seconde number:");	 		
	LCD_ShowString(30,110,200,16,16,"result:");	//显示SYMBOL
	while(1)
	{
		
		key=Remote_Scan();	
		if(key)
		{	
		 //设置延时
	   delay_ms(200);	
	    n++;
	//解决按一次按键，多次执行问题
	if(n%2==0){
	    //  printf("n===if====>%d",n);
				continue;
			}
		//printf("n===if==43==>%d",n);   		
				LED0=1;	  
				BEEP=1;  
				delay_ms(100);
				LED0=0;
				BEEP=0;		  
				delay_ms(10);
			switch(key)
			{
				case 0:str="ERROR";break;			   
				case 162:{str="POWER";
				  if(ss==0){
						 	WKUP_Init();			
						  ss=1;
					}else{
						WKUP_Sleep1();//待机状态
						ss=0;
					}			
				
				};break;	    
			case 98:{
					//str="UP";    +  
					     if(i==0){//防止未输入第一个操作数时，点击操作符
							    break;
							 }
					     LCD_ShowString(150,70,200,16,16,"+");			
				       s=98;
				       flag=1;		
							 printf("+");
				        }break;	    
				case 2:{//计算总和
				     printf("=");
					   if(i==0 && j==0){
							continue;
						 }
					   if(GetArrayToInt(a,i)<GetArrayToInt(b,j) && s==168){
							  LCD_ShowString(164,110,200,16,16,"-");
							 	LCD_ShowNum(170,110,GetSum(b,j,a,i,s),8,16);	
							  printf("%d\r\n",-GetSum(b,j,a,i,s));
						 }else{
							LCD_ShowString(164,110,200,16,16," ");
						 	LCD_ShowNum(170,110,GetSum(a,i,b,j,s),8,16);	
							  printf("%d\r\n",GetSum(a,i,b,j,s));
						 }	
							i=0;
			        j=0;
						  s=0;
							flag=0;
				}break;		 
				case 226:str="ALIENTEK";break;		  
				case 194:{
					//str="RIGHT"; /  ?
				      	if(i==0){
								// LCD_ShowString(30,130,200,16,16,"65");	//显示SYMBOL
							    break;
							 }
				        LCD_ShowString(150,70,200,16,16,"/");		
				        s=194;
				       flag=1;
							 printf("/");
				}break;	   
				case 34:{
					//str="LEFT";  *  
					      if(i==0){
							//	 LCD_ShowString(30,130,200,16,16,"654");	//显示SYMBOL
							    break;
							 }
			         LCD_ShowString(150,70,200,16,16,"*");		
				        s=34;
				       flag=1;
							 printf("*");
				}break;		  
				case 224:str="VOL-";break;		  
				case 168:{
					//str="DOWN";  -  
					     if(i==0){
								// LCD_ShowString(30,130,200,16,16,"654");	//显示SYMBOL
							    break;
							 }
				       LCD_ShowString(150,70,200,16,16,"-");		
			       	 s=168;
				       flag=1;	
								printf("-");							 
				}break;		   
				case 144:str="VOL+";break;		    
				case 104:{
				  //   str="1"; 
				         if(flag==0){
								 a[i]=1;
									 i++;
									 x=1;
								 }else{
									 b[j]=1;
									 j++;
									 y=1;
								 }
								 
				     }break;		  
				case 152:{					
					//	str="2";
						 if(flag==0){
										 a[i]=2;
											 i++;
							 x=2;
										 }else{
											 b[j]=2;
											 j++;
											 y=2;
										 }
						}break;	   
				case 176:{	
				
				//str="3";
					if(flag==0){
										 a[i]=3;
											 i++;
						x=3;
										 }else{
											 b[j]=3;
											 j++;
											 y=3;
										 }
						}break;	    
				case 48:{
					//		str="4";
							if(flag==0){
										 a[i]=4;
											 i++;
								x=4;
										 }else{
											 b[j]=4;
											 j++;
											 y=4;
										 }
						}break;		    
				case 24:{
				
				//		str="5";
						if(flag==0){
										 a[i]=5;
											 i++;
							x=5;
										 }else{
											 b[j]=5;
											 j++;
										 }
										 y=5;
						}break;		    
				case 122:{
				    if(flag==0){
										 a[i]=6;
											 i++;
							x=6;
										 }else{
											 b[j]=6;
											 j++;
											 y=6;
										 }
						//str="6";
				}break;		  
				case 16:{
					//	str="7";
							if(flag==0){
										 a[i]=7;
											 i++;
								x=7;
										 }else{
											 b[j]=7;
											 j++;
											 y=7;
										 }
				}break;			   					
				case 56:{
				//str="8";
							if(flag==0){
										 a[i]=8;
											 i++;
								x=8;
										 }else{
											 b[j]=8;
											 j++;
											 y=8;
										 }
				}break;	 
				case 90:{
				
				//str="9";
							if(flag==0){
										 a[i]=9;
											 i++;
								x=9;
										 }else{
											 b[j]=9;
											 j++;
											 y=9;
										 }
				}break;
				case 66:{
			//	str="0";
			          	if(flag==0){
										 a[i]=0;
											 i++;
										x=0;
										 }else{
											 b[j]=0;
											 j++;
										 y=0;
										 }
				}break;
				case 82:{str="DELETE";
					printf("delete");
					  if(j!=0){
						  j--;
							break;
						}
						if(s!=0){
						   s=0;
							LCD_ShowString(150,70,200,16,16," ");
							break;
						}
						if(i!=0&&j==0){
						  flag=0;
							i--;
							break;
						}		   

				}break;		 
			}

			 

			
			if(i!=0&&j==0){
				LCD_ShowNum(170,50,GetArrayToInt(a,i),8,16);	
				LCD_ShowNum(170,90,0,8,16);	
				LCD_ShowString(164,110,200,16,16," ");
				LCD_ShowNum(170,110,0,8,16);
				if(s==0){
					printf("%d",a[i-1]);
				}
				
			}
		  if(i!=0&&j!=0){
				
			LCD_ShowNum(170,90,GetArrayToInt(b,j),8,16);	
			if(s!=0){
			   printf("%d",b[j-1]);
			}
			
			//  LCD_ShowString(86,110,200,16,16,str);
			}		
	
		} 
		
	}
}














