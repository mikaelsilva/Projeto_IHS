#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>



#include <stdio.h>

#define C1  33
#define CS1 35
#define D1  37
#define DS1 39
#define E1  41
#define F1  44
#define FS1 46
#define G1  49
#define GS1 52
#define A1  55
#define AS1 58
#define B1  62

#define C2  65
#define CS2 69
#define D2  73
#define DS2 78
#define E2  82
#define F2  87
#define FS2 93
#define G2  98
#define GS2 104
#define A2  110
#define AS2 117
#define B2  123

#define C3  131
#define CS3 139
#define D3  147
#define DS3 156
#define E3  165
#define F3  175
#define FS3 185
#define G3  196
#define GS3 208
#define A3  220
#define AS3 233
#define B3  247

#define C4  262
#define CS4 277
#define D4  294
#define DS4 311
#define E4  330
#define F4  349
#define FS4 370
#define G4  392
#define GS4 415
#define A4  440
#define AS4 466
#define B4  494

#define C5  523
//#define CS5 554
#define D5  587
#define DS5 622
#define E5  659
#define F5  698
#define FS5 740
#define G5  784
#define GS5 831
#define A5  880
#define AS5 932
#define B5  988

#define C6  1047
//#define CS6 1109
#define D6  1175
#define DS6 1245
#define E6  1319
#define F6  1397
#define FS6 1480
#define G6  1568
#define GS6 1661
#define A6  1760
#define AS6 1865
#define B6  1976

#define C7  2093
//#define CS7 2217
#define D7  2349
#define DS7 2489
#define E7  2637
#define F7  2794
#define FS7 2960
#define G7  3136
#define GS7 3322
#define A7  3520
#define AS7 3729
#define B7  3951

#define C8  4186
//#define CS8 4435
#define D8  4699
#define DS8 4978

#define Oitava_1 7
#define Oitava_2 13
#define Oitava_3 18
#define Oitava_4 23
#define Oitava_5 28
#define Oitava_6 33
#define Oitava_7 38
#define Oitava_8 43

#define Nota_C 7
#define Nota_CS 13
#define Nota_D 18
#define Nota_DS 23
#define Nota_E 28
#define Nota_F 33
#define Nota_FS 38
#define Nota_G 43
#define Nota_GS 48
#define Nota_A 53
#define Nota_AS 58
#define Nota_B 63


int notas[13][9]={{0,0,0,0,0,0,0,0,0},
				  {0,A1,A2,A3,A4,A5,A6,A7,0},
				  {0,B1,B2,B3,B4,B5,B6,B7,0},
				  {0,C1,C2,C3,C4,C5,C6,C7,C8},
				  {0,D1,D2,D3,D4,D5,D6,D7,D8},
     			  {0,E1,E2,E3,E4,E5,E6,E7,0},
                  {0,F1,F2,F3,F4,F5,F6,F7,0},
				  {0,G1,G2,G3,G4,G5,G6,G7,0},
    			  {0,CS1,CS2,CS3,CS4,CS5,CS6,CS7,CS8},
   		 		  {0,DS1,DS2,DS3,DS4,DS5,DS6,DS7,DS8},
				  {0,FS1,FS2,FS3,FS4,FS5,FS6,FS7,0},
				  {0,GS1,GS2,GS3,GS4,GS5,GS6,GS7,0},
				  {0,AS1,AS2,AS3,AS4,AS5,AS6,AS7,0}};




int main(int argc,char** argv)
{
        struct termios tio;
        struct termios stdio;
        struct termios old_stdio;
        int tty_fd;

        unsigned char c='D';
        tcgetattr(STDOUT_FILENO,&old_stdio);

        printf("Please start with %s /dev/ttyS1 (for example)\n",argv[0]);
        memset(&stdio,0,sizeof(stdio));
        stdio.c_iflag=0;
        stdio.c_oflag=0;
        stdio.c_cflag=0;
        stdio.c_lflag=0;
        stdio.c_cc[VMIN]=1;
        stdio.c_cc[VTIME]=0;
        tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
        tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking

        memset(&tio,0,sizeof(tio));
        tio.c_iflag=0;
        tio.c_oflag=0;
        tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
        tio.c_lflag=0;
        tio.c_cc[VMIN]=1;
        tio.c_cc[VTIME]=5;

        tty_fd=open(argv[1], O_RDWR | O_NONBLOCK);      
        cfsetospeed(&tio,B115200);            // 115200 baud
        cfsetispeed(&tio,B115200);            // 115200 baud

        tcsetattr(tty_fd,TCSANOW,&tio);
		FILE *arq = fopen("/home/jdps/Imagens/music.txt","rt");
		char nota, oitava;
		int temp;	
        while (c!='q')
        {
                if (read(tty_fd,&c,1)>0)        write(STDOUT_FILENO,&c,1);              // if new data is available on the serial port, print it out
                if (fscanf(arq,"%c %c %d ",&nota,&oitava,&temp) != EOF){  
					int i = ((int)(nota-'A')+1);
					int j = ((int)oitava-'1'+1);
					
					c = (i*9)+j;

					write(tty_fd,&c,1);                     // if new data is available on the console, send it to the serial port
					
				}else{
					break;
				}
        }

        close(tty_fd);
		fclose(arq);
        tcsetattr(STDOUT_FILENO,TCSANOW,&old_stdio);

        return EXIT_SUCCESS;
}
