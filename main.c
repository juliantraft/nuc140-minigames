#include "DrvADC.h"
#include "DrvSYS.h"
#include "DrvGPIO.h"
#include "LCD_Driver.h"
#include "ScanKey.h"
#include "Seven_Segment.h"
#include <String.h>

int tegangan;

// Variabel umum
uint32_t i;
int temp;

// Variable Vault
uint32_t adc;					// Nilai ADC
uint32_t vaultTarget;			// Target ADC
uint32_t vaultScore = 0;		// Score

// Variabel Number Sequence
uint32_t sequenceRand = 0;		// Angka target (sebelum difilter)
uint32_t seqTarget[4];			// Array angka target
uint32_t seqGuess[4];			// Array angka jawaban
uint32_t seqGuessing = 0;		// Index angka yang sedang ditebak
uint32_t seqSevSeg = 3;			// Index seven segment
uint32_t seqFail = 0; 			// Flag untuk fail


// Variable Cut The Wire
uint32_t wireRand = 0;			// Target urutan kabel (sebelum difilter)
uint32_t wireTarget = 0;		// Target urutan kabel
uint32_t wireGuess = 0;			// Tebakan urutan kabel
uint32_t wireNumber = 1;		// Index kabel yang akan dipotong


void Init();

void delayM(uint32_t d) {
	for (i = 0; i < (d*500000); i++) {
	}
}

void duar(void) {
	clr_all_pannal();
	   	   	   //----------------
	print_lcd(0,"DDHHUUUAAARRRRR");
	print_lcd(1,"DDHHUUUAAARRRRR");
	print_lcd(2,"DDHHUUUAAARRRRR");
	print_lcd(3,"DDHHUUUAAARRRRR");
	DrvGPIO_SetBit(E_GPA,12);
	DrvGPIO_SetBit(E_GPA,14);
	while(1) {
		show_seven_segment(0,8);
		show_seven_segment(1,8);
		show_seven_segment(2,8);
		show_seven_segment(3,8);
		DrvGPIO_ClrBit(E_GPA,14);
		DrvGPIO_ClrBit(E_GPB,11);
		DrvGPIO_ClrBit(E_GPC,12);
		DrvGPIO_ClrBit(E_GPC,13);
		DrvGPIO_ClrBit(E_GPC,14);
		DrvGPIO_ClrBit(E_GPC,15);
		DrvSYS_Delay(50000);
		close_seven_segment();
		DrvGPIO_SetBit(E_GPA,14);
		DrvGPIO_SetBit(E_GPB,11);
		DrvGPIO_SetBit(E_GPC,12);
		DrvGPIO_SetBit(E_GPC,13);
		DrvGPIO_SetBit(E_GPC,14);
		DrvGPIO_SetBit(E_GPC,15);
		DrvSYS_Delay(50000);
	}
}



/*						VAULT GAME					*/
void vaultOpening(void) {
	clr_all_pannal();
	print_lcd(0,"Stage: 1");
	delayM(1);
	print_lcd(1,"HACK THE SYSTEM");
	delayM(3);


	clr_all_pannal();
	print_lcd(1,"Tekan keypad");
	print_lcd(2,"untuk memulai");

	// Randomize ADC Target
	while(!vaultTarget) {
		for (i = 100; i < 4080; i++) {
			if (Scankey()) {
				vaultTarget = i;
				break;
			}
		}
	}

	clr_all_pannal();
			   //----------------
	print_lcd(0,"Putar potensio");
	print_lcd(1,"hingga mendekati");
	print_lcd(2,"nilai target.");
	delayM(5);
	clr_all_pannal();
			   //----------------
	print_lcd(0,"Semakin dekat");
	print_lcd(1,"dengan target,");
	print_lcd(2,"semakin banyak");
	print_lcd(3,"nyala LED merah");
	delayM(5);
}

void vaultGuess() {
	temp = adc - vaultTarget;
	if (temp < 0) {
		temp *= -1;
	}

	if (temp <= 10) {
		   	   	   //------------------
		print_lcd(3,"     TAHAN");
		DrvGPIO_ClrBit(E_GPC, 12);
		DrvGPIO_ClrBit(E_GPC, 13);
		DrvGPIO_ClrBit(E_GPC, 14);
		DrvGPIO_ClrBit(E_GPC, 15);
		DrvGPIO_ClrBit(E_GPA, 12);
		DrvSYS_Delay(50000);
		print_lcd(3," ");
		DrvGPIO_SetBit(E_GPC,12);
		DrvGPIO_SetBit(E_GPC,13);
		DrvGPIO_SetBit(E_GPC,14);
		DrvGPIO_SetBit(E_GPC,15);
		DrvGPIO_SetBit(E_GPA,12);
		DrvSYS_Delay(50000);
		vaultScore++;
	} else if (temp <= 50) {
		DrvGPIO_ClrBit(E_GPC, 12);
		DrvGPIO_ClrBit(E_GPC, 13);
		DrvGPIO_ClrBit(E_GPC, 14);
		DrvSYS_Delay(50000);
		DrvGPIO_SetBit(E_GPC,12);
		DrvGPIO_SetBit(E_GPC,13);
		DrvGPIO_SetBit(E_GPC,14);
		DrvSYS_Delay(50000);
	} else if (temp <= 100) {
		DrvGPIO_ClrBit(E_GPC, 12);
		DrvGPIO_ClrBit(E_GPC, 13);
		DrvSYS_Delay(50000);
		DrvGPIO_SetBit(E_GPC,12);
		DrvGPIO_SetBit(E_GPC,13);
		DrvSYS_Delay(50000);
	} else {
		DrvGPIO_ClrBit(E_GPC, 12);
		DrvSYS_Delay(50000);
		DrvGPIO_SetBit(E_GPC,12);
		DrvSYS_Delay(50000);
	}
}

void vaultOpen() {
	clr_all_pannal();
	print_lcd(0, "System Unlocked");
	DrvGPIO_ClrBit(E_GPA,13);
	DrvGPIO_ClrBit(E_GPB,11);
	delayM(1);
	DrvGPIO_SetBit(E_GPA,13);
	DrvGPIO_SetBit(E_GPB,11);
	clr_all_pannal();
	delayM(1);
	vaultScore = 0;
	vaultTarget = 0;

	sequenceMain();
}

int vaultMain(void) {
	vaultOpening();
	while(1){
		clr_all_pannal();
		print_lcd(0, "System Locked");
		print_lcd(1, "Hacking...");
		print_lcd(2,"Knob = ");
		DrvADC_StartConvert();
		adc = DrvADC_GetConversionData(7);
		Show_Word(2,7,adc/1000+'0');
		Show_Word(2,8,adc%1000/100+'0');
		Show_Word(2,9,adc%100/10+'0');
		Show_Word(2,10,adc%10+'0');
		tegangan = ((float)adc/4096)*3300; // ??????????

		vaultGuess();

		if (vaultScore > 25) {
			vaultOpen();
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/*				NUMBER SEQUENCE GAME			*/
void sequenceOpening(void) {
	clr_all_pannal();
	print_lcd(0,"Stage: 2");
	delayM(1);
	print_lcd(1,"Number Sequence");
	delayM(3);

	clr_all_pannal();
	print_lcd(1,"Tekan keypad");
	print_lcd(2,"untuk memulai");

	// Randomizer
	while(!sequenceRand) {
		for (i = 1111; i < 9999; i+=33) {
			if (Scankey()) {
				sequenceRand = i;
				break;
			}
		}
	}
}

// Filtering angka 0
void sequenceFilter(void) {
	seqTarget[0] = sequenceRand/1000;
	if (seqTarget[0] == 0) seqTarget[0] = 1;
	seqTarget[1] = (sequenceRand/100) % 10;
	if (seqTarget[1] == 0) seqTarget[1] = 2;
	seqTarget[2] = (sequenceRand/10) % 10;
	if (seqTarget[2] == 0) seqTarget[2] = 3;
	seqTarget[3] = sequenceRand%10;
	if (seqTarget[3] == 0) seqTarget[3] = 4;
}

void sequenceShow(void) {
	clr_all_pannal();
			   //----------------
	print_lcd(1,"Ingat urutan");
	print_lcd(2,"angka berikut");
	delayM(4);
	clr_all_pannal();
	Show_Word(2,6, seqTarget[0]+'0');
	Show_Word(2,7, seqTarget[1]+'0');
	Show_Word(2,8, seqTarget[2]+'0');
	Show_Word(2,9, seqTarget[3]+'0');
	delayM(1);
	clr_all_pannal();
}

void sequenceGuess(void) {
	while(seqGuessing < 4) {
		print_lcd(0, "Masukkan Nomor");
		Show_Word(1,0,seqGuessing+1+'0');

		if(Scankey()) {
			temp = Scankey();
			close_seven_segment();
			show_seven_segment(seqSevSeg, temp);
			seqGuess[seqGuessing] = temp;
			DrvGPIO_ClrBit(E_GPC, 12);
			seqGuessing++;
			seqSevSeg--;
		}
		delayM(1);
		DrvGPIO_SetBit(E_GPC, 12);
	}
}

void sequenceCheck(void) {
	clr_all_pannal();

	for (i = 0; i < 4; i++) {
		if(seqTarget[i] != seqGuess[i]) {
			seqFail = 1;
		}
	}
	while (1) {
		if (seqFail) {
			print_lcd(1,"GAGAL");
			delayM(1);
			duar();
		} else {
			print_lcd(0,"Number Matched");
			DrvGPIO_ClrBit(E_GPA, 13);
			DrvGPIO_ClrBit(E_GPB, 11);
			delayM(1);
			DrvGPIO_SetBit(E_GPA, 12);
			DrvGPIO_SetBit(E_GPA, 13);
			DrvGPIO_SetBit(E_GPA, 14);
			DrvGPIO_SetBit(E_GPB, 11);
			close_seven_segment();
			wireMain();
		}
	}
}

void sequenceMain(void) {
	sequenceOpening();
	sequenceFilter();
	sequenceShow();
	sequenceGuess();
	sequenceCheck();
}

///////////////////////////////////////////////////////////////////////////////////
/*				CUT THE WIRE GAME			*/

// Activate RGB LED based on integer input 0-7
void rgb(uint32_t c, uint32_t t) {
	if (c % 2) { DrvGPIO_ClrBit(E_GPA,12); }
	else { DrvGPIO_SetBit(E_GPA,12); }
	c /= 2;
	if (c % 2) { DrvGPIO_ClrBit(E_GPA,13); }
	else { DrvGPIO_SetBit(E_GPA,13); }
	c /= 2;
	if (c % 2) { DrvGPIO_ClrBit(E_GPA,14); }
	else { DrvGPIO_SetBit(E_GPA,14); }

	// "Optional" delay
	if (t) {
		delayM(t);
		DrvGPIO_SetBit(E_GPA,12);
		DrvGPIO_SetBit(E_GPA,13);
		DrvGPIO_SetBit(E_GPA,14);
		delayM(t);
	}
}

void printWarna(uint32_t warna, uint32_t baris) {
	print_lcd(baris,"                ");
	switch(warna) {
	case 1: print_lcd(baris, "Biru"); break;
	case 2: print_lcd(baris, "Hijau"); break;
	case 3: print_lcd(baris, "Biru Muda"); break;
	case 4: print_lcd(baris, "Merah"); break;
	case 5: print_lcd(baris, "Ungu"); break;
	case 6: print_lcd(baris, "Kuning"); break;
	case 7: print_lcd(baris, "Putih"); break;
	}
}

// Opening sekaligus wireTarget randomizer
void wireOpening(void) {
	clr_all_pannal();
	print_lcd(0,"Stage: 3");
	delayM(1);
	print_lcd(1,"CUT THE WIRE");
	delayM(3);

	clr_all_pannal();
	print_lcd(1,"Tekan keypad");
	print_lcd(2,"untuk memulai");;

	// Randomize ADC Target
	while(!wireRand) {
		for (i = 100; i <= 999; i++) {
			if (Scankey()) {
				wireRand = i;
				break;
			}
		}
	}
}

// Filtering angka 0,8,9 dari wireTargetRand (range target 1-7)
void wireFilter() {
	temp = (wireRand % 10) % 8;
	if (temp < 1) {
		temp++;
	}
	wireTarget += temp;

	temp = ((wireRand/10) % 10) % 8;
	if (temp < 1) {
		temp++;
	}
	wireTarget += (temp * 10);

	temp = (wireRand/100) % 8;
	if (temp < 1) {
		temp++;
	}
	wireTarget += (temp *100);
	temp = 0;
}

// Flash 3x berdasarkan nilai wireTarget
void wireFlash(void) {
	clr_all_pannal();
	print_lcd(1,"Kabel 1");
	rgb(wireTarget/100,1);
	print_lcd(1,"Kabel 2");
	rgb((wireTarget/10)%10,1);
	print_lcd(1,"Kabel 3");
	rgb(wireTarget%10,1);
}

void select(void) {
	switch(wireNumber) {
	case 1: wireGuess += (temp*100); break;
	case 2: wireGuess += (temp*10); break;
 	case 3: wireGuess += (temp); break;
	}
	wireNumber++;
}

void wireSelect(void) {
	clr_all_pannal();
			   //----------------
	print_lcd(0,"Potong kabel");
	print_lcd(1,"secara berurutan");
	delayM(4);
	clr_all_pannal();
			   //----------------
	print_lcd(0,"Gunakan Keypad");
	print_lcd(1,"1 : Potong kabel");
	print_lcd(2,"3 : Ganti warna");
	print_lcd(3,"v           v");
	delayM(7);
	clr_all_pannal();
	print_lcd(1,"     GO!!!      ");
	delayM(1);

	temp = 1; // Default on blue
	clr_all_pannal();
	print_lcd(0,"Kabel ");
	while(wireNumber <= 3) {
		Show_Word(0,6, wireNumber+'0');

		if (Scankey() == 3) {
			temp++;
			DrvGPIO_ClrBit(E_GPC, 12);
		}
		if (Scankey() == 1) {
			select();
			DrvGPIO_ClrBit(E_GPC, 12);
		}
		temp %= 8;
		if (temp < 1) {
			temp++;
		}

		printWarna(temp, wireNumber);
		rgb(temp, 0);
		delayM(1);
		DrvGPIO_SetBit(E_GPC, 12);
	}
}

void wireWin(void) {
	clr_all_pannal();
	   	   	   //----------------
	print_lcd(1,"BOMB DEFUSED");
	DrvGPIO_SetBit(E_GPA,12);
	DrvGPIO_SetBit(E_GPA,14);
	DrvGPIO_ClrBit(E_GPB,11);
	DrvGPIO_ClrBit(E_GPA,13);
	delayM(1);
	DrvGPIO_SetBit(E_GPB,11);
	while(1) {

	}
}

void wireMain(void) {
	wireOpening();
	wireFilter();
	clr_all_pannal();
			   //----------------
	print_lcd(0,"Ingat urutan");
	print_lcd(1,"3 warna kabel");
	print_lcd(2,"berikut!");
	delayM(5);
	clr_all_pannal();
	print_lcd(1,"PERHATIKAN");
	print_lcd(3,"vvv");
	delayM(3);
	wireFlash();

	wireSelect();
	if (wireGuess == wireTarget) {
		wireWin();
	} else {
		duar();
	}
}

int main(void){
	Init();
	Initial_pannel();
	clr_all_pannal();
	OpenKeyPad();
	DrvGPIO_ClrBit(E_GPD, 14);

	print_lcd(1, "DEFUSE THE BOMB");
	delayM(5);

	while(1) {
		vaultMain();
	}
}
