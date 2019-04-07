#include  <msp430g2253.h>

 unsigned int i = 0;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD; //Stop watchdog timer

  P1DIR = 0x41;  //PIDIR là thanh ghi 8bit để định nghĩa các chân của một Port(output)
  	  	  	  	 //Để thiết lập chân là output hay inptut, chúng ta viết '1' hoặc 0 tương ứng với chân.  VD để nháy led đỏ chân (P1.0):P1DIR|=00000001 hoặc P1DIR=0x01 (dạng hex chuẩn đổi từ 00000001)
  	  	  	  	 //Vì đề bài yêu cầu sáng 2 led nên ta chỉ sử dụng 2 chân P1.0 và P2.0 ứng với giá trị 01000001 tương ứng với mã hex là 0x41
 /* Ý tưởng:
  * B1 và B2:  Lần lượt thực hiện sáng led 1 và tắt toàn bộ led lần lượt, mỗi khi thực hiện đều được tạo 1 khoảng delay để mắt thường có thể nhìn thấy chớp tắt của led
  * 					Tạo vòng lặp loop1 để thực hiện 2 lần việc sáng led1 tắt led2
  * B3:	Thực hiện sáng và tắt tương tự B1 và B2 cho led2
  * Sau khi thực hiện lặp lại các bước thông qua vòng lặp vô tận
  *
 */

  for(;;) //Tạo vòng lặp vô tận
  {

	int loop1=2;
	while (loop1!=0) 	 //tạo vòng lặp thực hiện bước 1 và bước 2 chỉ sáng led 1
	{
		int delay1=0;
		for (delay1=0;delay1<20000;delay1++) //tạo độ trễ delay cho việc sáng led1
			P1OUT=0x01; //Làm sáng led1 bằng cách gắn giá trị '1' của thanh P1.0 cho P1OUT
		int delay2=0;
		for(delay2=0;delay2<20000;delay2++) //tạo độ trễ delay cho việc tắt toàn bộ led
			P1OUT=0x00; // Tương tự như trên với việc tắt toàn bộ led1
		loop1--;
	}
	int delay3=0;
	for(delay3=0;delay3<20000;delay3++) //tạo độ trễ delay cho việc sáng led2
		P1OUT=0x40; //Sáng led2
	for(delay3=0;delay3<20000;delay3++) //tạo độ trễ delay cho việc tắt led2
		P1OUT=0x00; // Tắt led2

  }
}
