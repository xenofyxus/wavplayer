#ifndef CTRLREGS_H
#define CTRLREGS_H

// comments will refer to pages in the PIC32MX3XX/4XX family datasheet

// Macros don't end with semicolon because fuck VS2015 indenting following statements if there isn't one in the code
// Dat autocomplete/intellisense though

#define REGPADDING unsigned int : 32; long long : 64
#define EMPTYREG long long : 64; long long : 64
#define EMPTYREG10 EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG
#define UNIMPL(x) unsigned : x

// Interrupt registers (page 53)

typedef struct
{
	union
	{
		unsigned int WORD;
		struct
		{
			unsigned INT0EP : 1;
			unsigned INT1EP : 1;
			unsigned INT2EP : 1;
			unsigned INT3EP : 1;
			unsigned INT4EP : 1;
			UNIMPL(3);
			unsigned TPC : 3;
			UNIMPL(1);
			unsigned MVEC : 1;
			UNIMPL(3);
			unsigned SS0 : 1;
		};
	} CON;
	REGPADDING;
	union
	{
		unsigned int WORD;
		struct
		{
			unsigned VEC : 6;
			UNIMPL(2);
			unsigned SRIPL : 3;
		};
	} STAT;
	REGPADDING;
	unsigned int TMR;
	REGPADDING;
	struct
	{
		union
		{
			unsigned int IFS0_WORD;
			struct
			{
				unsigned CT : 1;
				unsigned CS0 : 1;
				unsigned CS1 : 1;
				unsigned INT0 : 1;
				unsigned T1 : 1;
				unsigned IC1 : 1;
				unsigned OC1 : 1;
				unsigned INT1 : 1;
				unsigned T2 : 1;
				unsigned IC2 : 1;
				unsigned OC2 : 1;
				unsigned INT2 : 1;
				unsigned T3 : 1;
				unsigned IC3 : 1;
				unsigned OC3 : 1;
				unsigned INT3 : 1;
				unsigned T4 : 1;
				unsigned IC4 : 1;
				unsigned OC4 : 1;
				unsigned INT4 : 1;
				unsigned T5 : 1;
				unsigned IC5 : 1;
				unsigned OC5 : 1;
				unsigned SPI1E : 1;
				unsigned SPI1TX : 1;
				unsigned SPI1RX : 1;
				unsigned U1E : 1;
				unsigned U1RX : 1;
				unsigned U1TX : 1;
				unsigned I2C1B : 1;
				unsigned I2C1S : 1;
				unsigned I2C1M : 1;
			};
		};
		REGPADDING;
		union
		{
			unsigned int IFS1_WORD;
			struct
			{
				unsigned CN : 1;
				unsigned AD1 : 1;
				unsigned PMP : 1;
				unsigned CMP1 : 1;
				unsigned CMP2 : 1;
				unsigned SPI2E : 1;
				unsigned SPI2TX : 1;
				unsigned SPI2RX : 1;
				unsigned U2E : 1;
				unsigned U2RX : 1;
				unsigned U2TX : 1;
				unsigned I2C2B : 1;
				unsigned I2C2S : 1;
				unsigned I2C2M : 1;
				unsigned FSCM : 1;
				unsigned RTCC : 1;
				UNIMPL(8);
				unsigned FCE : 1;
			};
		};
		REGPADDING;
	} IFS;
	EMPTYREG;
	struct
	{
		union
		{
			unsigned int IEC0_WORD;
			struct
			{
				unsigned CT : 1;
				unsigned CS0 : 1;
				unsigned CS1 : 1;
				unsigned INT0 : 1;
				unsigned T1 : 1;
				unsigned IC1 : 1;
				unsigned OC1 : 1;
				unsigned INT1 : 1;
				unsigned T2 : 1;
				unsigned IC2 : 1;
				unsigned OC2 : 1;
				unsigned INT2 : 1;
				unsigned T3 : 1;
				unsigned IC3 : 1;
				unsigned OC3 : 1;
				unsigned INT3 : 1;
				unsigned T4 : 1;
				unsigned IC4 : 1;
				unsigned OC4 : 1;
				unsigned INT4 : 1;
				unsigned T5 : 1;
				unsigned IC5 : 1;
				unsigned OC5 : 1;
				unsigned SPI1E : 1;
				unsigned SPI1TX : 1;
				unsigned SPI1RX : 1;
				unsigned U1E : 1;
				unsigned U1RX : 1;
				unsigned U1TX : 1;
				unsigned I2C1B : 1;
				unsigned I2C1S : 1;
				unsigned I2C1M : 1;
			};
		};
		REGPADDING;
		union
		{
			unsigned int IEC1_WORD;
			struct
			{
				unsigned CN : 1;
				unsigned AD1 : 1;
				unsigned PMP : 1;
				unsigned CMP1 : 1;
				unsigned CMP2 : 1;
				unsigned SPI2E : 1;
				unsigned SPI2TX : 1;
				unsigned SPI2RX : 1;
				UNIMPL(5);
				unsigned I2C2M : 1;
				unsigned FSCM : 1;
				unsigned RTCC : 1;
				UNIMPL(8);
				unsigned FCE : 1;
			};
		};
		REGPADDING;
	} IEC;
	EMPTYREG;
	struct
	{
		union
		{
			unsigned int IPC0_WORD;
			struct
			{
				unsigned IS : 2;
				unsigned IP : 3;
			} CT;
			struct
			{
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} CS0;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} CS1;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} INT0;
		};
		REGPADDING;
		union
		{
			unsigned int IPC1_WORD;
			struct
			{
				unsigned IS : 2;
				unsigned IP : 3;
			} T1;
			struct
			{
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} IC1;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} OC1;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} INT1;
		};
		REGPADDING;
		union
		{
			unsigned int IPC2_WORD;
			struct
			{
				unsigned IS : 2;
				unsigned IP : 3;
			} T2;
			struct
			{
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} IC2;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} OC2;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} INT2;
		};
		REGPADDING;
		union
		{
			unsigned int IPC3_WORD;
			struct
			{
				unsigned IS : 2;
				unsigned IP : 3;
			} T3;
			struct
			{
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} IC3;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} OC3;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} INT3;
		};
		REGPADDING;
		union
		{
			unsigned int IPC4_WORD;
			struct
			{
				unsigned IS : 2;
				unsigned IP : 3;
			} T4;
			struct
			{
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} IC4;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} OC4;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} INT4;
		};
		REGPADDING;
		union
		{
			unsigned int IPC5_WORD;
			struct
			{
				unsigned IS : 2;
				unsigned IP : 3;
			} T5;
			struct
			{
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} IC5;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} OC5;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} SPI1;
		};
		REGPADDING;
		union
		{
			unsigned int IPC6_WORD;
			struct
			{
				unsigned IS : 2;
				unsigned IP : 3;
			} U1;
			struct
			{
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} I2C1;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} CN;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} AD1;
		};
		REGPADDING;
		union
		{
			unsigned int IPC7_WORD;
			struct
			{
				unsigned IS : 2;
				unsigned IP : 3;
			} PMP;
			struct
			{
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} CMP1;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} CMP2;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} SPI2;
		};
		REGPADDING;
		union
		{
			unsigned int IPC8_WORD;
			struct
			{
				unsigned IS : 2;
				unsigned IP : 3;
			} U2;
			struct
			{
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} I2C2;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} FSCM;
			struct
			{
				UNIMPL(8);
				UNIMPL(8);
				UNIMPL(8);
				unsigned IS : 2;
				unsigned IP : 3;
			} RTCC;
		};
		REGPADDING;
		EMPTYREG;
		EMPTYREG;
		union
		{
			unsigned int IPC11_WORD;
			struct
			{
				unsigned IS : 2;
				unsigned IP : 3;
			} FCE;
		};
		REGPADDING;
	} IPC;
} st_INT;

// /Interrupt registers

// Port registers (pages 70-76)
// TODO: explore unknown pins

union st_PORTB_WORDLAYOUT
{
	unsigned int WORD;
	struct
	{
		unsigned BIT0 : 1;
		unsigned BIT1 : 1;
		unsigned BIT2 : 1;
		unsigned BIT3 : 1;
		unsigned BIT4 : 1;
		unsigned BIT5 : 1;
		unsigned BIT6 : 1;
		unsigned BIT7 : 1;
		unsigned BIT8 : 1;
		unsigned BIT9 : 1;
		unsigned BIT10 : 1;
		unsigned BIT11 : 1;
		unsigned BIT12 : 1;
		unsigned BIT13 : 1;
		unsigned BIT14 : 1;
		unsigned BIT15 : 1;
	} BITS;
};

union st_PORTC_WORDLAYOUT
{
	unsigned int WORD;
	struct
	{
		UNIMPL(12);
		unsigned unknown1 : 4;
	};
	struct
	{
		unsigned BIT0 : 1;
		unsigned BIT1 : 1;
		unsigned BIT2 : 1;
		unsigned BIT3 : 1;
		unsigned BIT4 : 1;
		unsigned BIT5 : 1;
		unsigned BIT6 : 1;
		unsigned BIT7 : 1;
		unsigned BIT8 : 1;
		unsigned BIT9 : 1;
		unsigned BIT10 : 1;
		unsigned BIT11 : 1;
		unsigned BIT12 : 1;
		unsigned BIT13 : 1;
		unsigned BIT14 : 1;
		unsigned BIT15 : 1;
	} BITS;
};

union st_PORTD_WORDLAYOUT
{
	unsigned int WORD;
	union
	{
		unsigned FULL : 5;
		struct
		{
			unsigned OC1 : 1;
			unsigned OC2 : 1;
			unsigned OC3 : 1;
			unsigned OC4 : 1;
			unsigned OC5 : 1;
		};
	} OCx;
	union
	{
		struct
		{
			unsigned : 5;
			unsigned FULL : 3;
		};
		struct
		{
			unsigned : 5;
			unsigned BTN2 : 1;
			unsigned BTN3 : 1;
			unsigned BTN4 : 1;
		};
	} BTN;
	union
	{
		struct
		{
			unsigned : 8;
			unsigned FULL : 4;
		};
		struct
		{
			unsigned : 8;
			unsigned SW1 : 1;
			unsigned SW2 : 1;
			unsigned SW3 : 1;
			unsigned SW4 : 1;
		};
	} SW;
	struct
	{
		unsigned BIT0 : 1;
		unsigned BIT1 : 1;
		unsigned BIT2 : 1;
		unsigned BIT3 : 1;
		unsigned BIT4 : 1;
		unsigned BIT5 : 1;
		unsigned BIT6 : 1;
		unsigned BIT7 : 1;
		unsigned BIT8 : 1;
		unsigned BIT9 : 1;
		unsigned BIT10 : 1;
		unsigned BIT11 : 1;
	} BITS;
};

union st_PORTE_WORDLAYOUT
{
	unsigned int WORD;
	union
	{
		unsigned FULL : 8;
		struct
		{
			unsigned LED0 : 1;
			unsigned LED1 : 1;
			unsigned LED2 : 1;
			unsigned LED3 : 1;
			unsigned LED4 : 1;
			unsigned LED5 : 1;
			unsigned LED6 : 1;
			unsigned LED7 : 1;
		};
	} LED;
	struct
	{
		unsigned BIT0 : 1;
		unsigned BIT1 : 1;
		unsigned BIT2 : 1;
		unsigned BIT3 : 1;
		unsigned BIT4 : 1;
		unsigned BIT5 : 1;
		unsigned BIT6 : 1;
		unsigned BIT7 : 1;
		unsigned BIT8 : 1;
	} BITS;
};

union st_PORTF_WORDLAYOUT
{
	unsigned int WORD;
	struct
	{
		UNIMPL(1);
		unsigned BTN1 : 1;
	};
	struct
	{
		unsigned BIT0 : 1;
		unsigned BIT1 : 1;
		unsigned BIT2 : 1;
		unsigned BIT3 : 1;
		unsigned BIT4 : 1;
		unsigned BIT5 : 1;
		unsigned BIT6 : 1;
	} BITS;
};

union st_PORTG_WORDLAYOUT
{
	unsigned int WORD;

	struct
	{
		unsigned BIT0 : 1;
		unsigned BIT1 : 1;
		unsigned BIT2 : 1;
		unsigned BIT3 : 1;
		unsigned BIT4 : 1;
		unsigned BIT5 : 1;
		unsigned BIT6 : 1;
		unsigned BIT7 : 1;
		unsigned BIT8 : 1;
		unsigned BIT9 : 1;
	} BITS;
};

typedef struct
{
	struct
	{
		union st_PORTB_WORDLAYOUT TRIS;
		REGPADDING;
		union st_PORTB_WORDLAYOUT PORT;
		REGPADDING;
		union st_PORTB_WORDLAYOUT LAT;
		REGPADDING;
		union st_PORTB_WORDLAYOUT ODC;
		REGPADDING;
	} B;
	struct
	{
		union st_PORTC_WORDLAYOUT TRIS;
		REGPADDING;
		union st_PORTC_WORDLAYOUT PORT;
		REGPADDING;
		union st_PORTC_WORDLAYOUT LAT;
		REGPADDING;
		union st_PORTC_WORDLAYOUT ODC;
		REGPADDING;
	} C;
	struct
	{
		union st_PORTD_WORDLAYOUT TRIS;
		REGPADDING;
		union st_PORTD_WORDLAYOUT PORT;
		REGPADDING;
		union st_PORTD_WORDLAYOUT LAT;
		REGPADDING;
		union st_PORTD_WORDLAYOUT ODC;
		REGPADDING;
	} D;
	struct
	{
		union st_PORTE_WORDLAYOUT TRIS;
		REGPADDING;
		union st_PORTE_WORDLAYOUT PORT;
		REGPADDING;
		union st_PORTE_WORDLAYOUT LAT;
		REGPADDING;
		union st_PORTE_WORDLAYOUT ODC;
		REGPADDING;
	} E;
	struct
	{
		union st_PORTF_WORDLAYOUT TRIS;
		REGPADDING;
		union st_PORTF_WORDLAYOUT PORT;
		REGPADDING;
		union st_PORTF_WORDLAYOUT LAT;
		REGPADDING;
		union st_PORTF_WORDLAYOUT ODC;
		REGPADDING;
	} F;
	struct
	{
		union st_PORTG_WORDLAYOUT TRIS;
		REGPADDING;
		union st_PORTG_WORDLAYOUT PORT;
		REGPADDING;
		union st_PORTG_WORDLAYOUT LAT;
		REGPADDING;
		union st_PORTG_WORDLAYOUT ODC;
		REGPADDING;
	} G;
} st_PORTS;

// /Port registers

// Timer registers (page 56)

union st_T1CON
{
	unsigned int WORD;
	struct
	{
		UNIMPL(1);
		unsigned TCS : 1;
		unsigned TSYNC : 1;
		UNIMPL(1);
		unsigned TCKPS : 2;
		UNIMPL(1);
		unsigned TGATE : 1;
		UNIMPL(3);
		unsigned TWIP : 1;
		unsigned TWDIS : 1;
		unsigned SIDL : 1;
		UNIMPL(1);
		unsigned ON : 1;
	};
};

union st_TxACON
{
	unsigned int WORD;
	struct
	{
		UNIMPL(1);
		unsigned TCS : 1;
		UNIMPL(2);
		unsigned TCKPS : 3;
		unsigned TGATE : 1;
		UNIMPL(5);
		unsigned SIDL : 1;
		UNIMPL(1);
		unsigned ON : 1;
	};
};

union st_TxBCON
{
	unsigned int WORD;
	struct
	{
		UNIMPL(1);
		unsigned TCS : 1;
		UNIMPL(1);
		unsigned T32 : 1;
		unsigned TCKPS : 3;
		unsigned TGATE : 1;
		UNIMPL(5);
		unsigned SIDL : 1;
		UNIMPL(1);
		unsigned ON : 1;
	};
};

typedef struct
{
	struct
	{
		union st_T1CON CON;
		REGPADDING;
		unsigned int TMR;
		REGPADDING;
		unsigned int PR;
		REGPADDING;
	} T1;
	EMPTYREG10; EMPTYREG10;
	EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG;
	struct
	{
		union st_TxBCON CON;
		REGPADDING;
		unsigned int TMR;
		REGPADDING;
		unsigned int PR;
		REGPADDING;
	} T2;
	EMPTYREG10; EMPTYREG10;
	EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG;
	struct
	{
		union st_TxACON CON;
		REGPADDING;
		unsigned int TMR;
		REGPADDING;
		unsigned int PR;
		REGPADDING;
	} T3;
	EMPTYREG10; EMPTYREG10;
	EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG;
	struct
	{
		union st_TxBCON CON;
		REGPADDING;
		unsigned int TMR;
		REGPADDING;
		unsigned int PR;
		REGPADDING;
	} T4;
	EMPTYREG10; EMPTYREG10;
	EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG;
	struct
	{
		union st_TxACON CON;
		REGPADDING;
		unsigned int TMR;
		REGPADDING;
		unsigned int PR;
		REGPADDING;
	} T5;
} st_TIMERS;

// /Timer Registers

// SPI registers (page 61)

union st_SPIxCON
{
	unsigned int WORD;
	struct
	{
		UNIMPL(5);
		unsigned MSTEN : 1;
		unsigned CKP : 1;
		unsigned SSEN : 1;
		unsigned CKE : 1;
		unsigned SMP : 1;
		unsigned MODE16 : 1;
		unsigned MODE32 : 1;
		unsigned DISSDO : 1;
		unsigned SIDL : 1;
		UNIMPL(1);
		unsigned ON : 1;
		UNIMPL(1);
		unsigned SPIFE : 1;
		UNIMPL(6);
		UNIMPL(5);
		unsigned FRMPOL : 1;
		unsigned FRMSYNC : 1;
		unsigned FRMEN : 1;
	};
};

union st_SPIxSTAT
{
	unsigned int WORD;
	struct
	{
		unsigned SPIRBF : 1;
		UNIMPL(2);
		unsigned SPITBE : 1;
		UNIMPL(2);
		unsigned SPIROV : 1;
		UNIMPL(2);
		UNIMPL(2);
		unsigned SPIBUSY : 1;
	};
};

typedef struct
{
	struct
	{
		union st_SPIxCON CON;
		REGPADDING;
		union st_SPIxSTAT STAT;
		REGPADDING;
		unsigned int BUF;
		REGPADDING;
		unsigned int BRG;
		REGPADDING;
	} SPI1;
	EMPTYREG10; EMPTYREG10;
	EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG;
	struct
	{
		union st_SPIxCON CON;
		REGPADDING;
		union st_SPIxSTAT STAT;
		REGPADDING;
		unsigned int BUF;
		REGPADDING;
		unsigned int BRG;
		REGPADDING;
	} SPI2;
} st_SPI;

// /SPI registers

// ADC registers (pages 62-63)

union st_ADCBUF
{
	unsigned int FULL;
	struct
	{
		unsigned LOW : 8;
		unsigned HIGH : 8;
	};
};

typedef struct
{
	struct
	{
		union
		{
			unsigned int CON1_WORD;
			struct
			{
				unsigned DONE : 1;
				unsigned SAMP : 1;
				unsigned ASAM : 1;
				UNIMPL(1);
				unsigned CLRASAM : 1;
				unsigned SSRC : 3;
				unsigned FORM : 3;
				UNIMPL(2);
				unsigned SIDL : 1;
				UNIMPL(1);
				unsigned ON : 1;
			};
		};
		REGPADDING;
		union
		{
			unsigned int CON2_WORD;
			struct
			{
				unsigned ALTS : 1;
				unsigned BUFM : 1;
				unsigned SMPI : 4;
				UNIMPL(1);
				unsigned BUFS : 1;
				UNIMPL(2);
				unsigned CSNA : 1;
				UNIMPL(1);
				unsigned OFFCAL : 1;
				unsigned VCFG : 3;
			};
		};
		REGPADDING;
		union
		{
			unsigned int CON3_WORD;
			struct
			{
				unsigned ADCS : 8;
				unsigned SAMC : 5;
				UNIMPL(2);
				unsigned ADRC : 1;
			};
		};
		REGPADDING;
	} CON;
	EMPTYREG;
	union
	{
		unsigned int WORD;
		struct
		{
			UNIMPL(16);
			unsigned CH0SA : 4;
			UNIMPL(3);
			unsigned CH0NA : 1;
			unsigned CH0SB : 4;
			UNIMPL(3);
			unsigned CH0NB : 1;
		};
	} CHS;
	REGPADDING;
	union
	{
		unsigned int WORD;
		struct
		{
			unsigned CSSL0 : 1;
			unsigned CSSL1 : 1;
			unsigned CSSL2 : 1;
			unsigned CSSL3 : 1;
			unsigned CSSL4 : 1;
			unsigned CSSL5 : 1;
			unsigned CSSL6 : 1;
			unsigned CSSL7 : 1;
			unsigned CSSL8 : 1;
			unsigned CSSL9 : 1;
			unsigned CSSL10 : 1;
			unsigned CSSL11 : 1;
			unsigned CSSL12 : 1;
			unsigned CSSL13 : 1;
			unsigned CSSL14 : 1;
			unsigned CSSL15 : 1;
		};
	} CSSL;
	REGPADDING;
	union
	{
		unsigned int WORD;
		struct
		{
			unsigned PCFG0 : 1;
			unsigned PCFG1 : 1;
			unsigned PCFG2 : 1;
			unsigned PCFG3 : 1;
			unsigned PCFG4 : 1;
			unsigned PCFG5 : 1;
			unsigned PCFG6 : 1;
			unsigned PCFG7 : 1;
			unsigned PCFG8 : 1;
			unsigned PCFG9 : 1;
			unsigned PCFG10 : 1;
			unsigned PCFG11 : 1;
			unsigned PCFG12 : 1;
			unsigned PCFG13 : 1;
			unsigned PCFG14 : 1;
			unsigned PCFG15 : 1;
		};
	} PCFG;
	REGPADDING;
	struct
	{
		union st_ADCBUF BUF0;
		REGPADDING;
		union st_ADCBUF BUF1;
		REGPADDING;
		union st_ADCBUF BUF2;
		REGPADDING;
		union st_ADCBUF BUF3;
		REGPADDING;
		union st_ADCBUF BUF4;
		REGPADDING;
		union st_ADCBUF BUF5;
		REGPADDING;
		union st_ADCBUF BUF6;
		REGPADDING;
		union st_ADCBUF BUF7;
		REGPADDING;
		union st_ADCBUF BUF8;
		REGPADDING;
		union st_ADCBUF BUF9;
		REGPADDING;
		union st_ADCBUF BUFA;
		REGPADDING;
		union st_ADCBUF BUFB;
		REGPADDING;
		union st_ADCBUF BUFC;
		REGPADDING;
		union st_ADCBUF BUFD;
		REGPADDING;
		union st_ADCBUF BUFE;
		REGPADDING;
		union st_ADCBUF BUFF;
		REGPADDING;
	} BUF;
} st_ADC;

// /ADC registers

// OC registers (page 58)

union st_OCxCON
{
	unsigned int WORD;
	struct
	{
		unsigned OCM : 3;
		unsigned OCTSEL : 1;
		unsigned OCFLT : 1;
		unsigned OC32 : 1;
		UNIMPL(2);
		UNIMPL(5);
		unsigned SIDL : 1;
		UNIMPL(1);
		unsigned ON : 1;
	};
};

typedef struct
{
	struct
	{
		union st_OCxCON CON;
		REGPADDING;
		unsigned int R;
		REGPADDING;
		unsigned int RS;
		REGPADDING;
	} OC1;
	EMPTYREG10; EMPTYREG10;
	EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG;
	struct
	{
		union st_OCxCON CON;
		REGPADDING;
		unsigned int R;
		REGPADDING;
		unsigned int RS;
		REGPADDING;
	} OC2;
	EMPTYREG10; EMPTYREG10;
	EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG;
	struct
	{
		union st_OCxCON CON;
		REGPADDING;
		unsigned int R;
		REGPADDING;
		unsigned int RS;
		REGPADDING;
	} OC3;
	EMPTYREG10; EMPTYREG10;
	EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG;
	struct
	{
		union st_OCxCON CON;
		REGPADDING;
		unsigned int R;
		REGPADDING;
		unsigned int RS;
		REGPADDING;
	} OC4;
	EMPTYREG10; EMPTYREG10;
	EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG; EMPTYREG;
	struct
	{
		union st_OCxCON CON;
		REGPADDING;
		unsigned int R;
		REGPADDING;
		unsigned int RS;
		REGPADDING;
	} OC5;
} st_OC;

// /OC registers

// IC registers (page 57)

union st_ICxCON
{
	unsigned int WORD;
	struct
	{
		unsigned ICM : 3;
		unsigned ICBNE : 1;
		unsigned ICOV : 1;
		unsigned ICI : 2;
		unsigned ICTMR : 1;
		unsigned C32 : 1;
		unsigned FEDGE : 1;
		UNIMPL(3);
		unsigned SIDL : 1;
		UNIMPL(1);
		unsigned ON : 1;
	};
};

typedef struct
{
	struct
	{
		union st_ICxCON CON;
		REGPADDING;
		unsigned int BUF;
		REGPADDING;
	} IC1;
	EMPTYREG10; EMPTYREG10; EMPTYREG10;
	EMPTYREG; EMPTYREG;
	struct
	{
		union st_ICxCON CON;
		REGPADDING;
		unsigned int BUF;
		REGPADDING;
	} IC2;
	EMPTYREG10; EMPTYREG10; EMPTYREG10;
	EMPTYREG; EMPTYREG;
	struct
	{
		union st_ICxCON CON;
		REGPADDING;
		unsigned int BUF;
		REGPADDING;
	} IC3;
	EMPTYREG10; EMPTYREG10; EMPTYREG10;
	EMPTYREG; EMPTYREG;
	struct
	{
		union st_ICxCON CON;
		REGPADDING;
		unsigned int BUF;
		REGPADDING;
	} IC4;
	EMPTYREG10; EMPTYREG10; EMPTYREG10;
	EMPTYREG; EMPTYREG;
	struct
	{
		union st_ICxCON CON;
		REGPADDING;
		unsigned int BUF;
		REGPADDING;
	} IC5;
	EMPTYREG10; EMPTYREG10; EMPTYREG10;
	EMPTYREG; EMPTYREG;
} st_IC;

// /IC registers

// CN registers (page 77)

typedef struct
{
	union
	{
		unsigned int WORD;
		struct
		{
			UNIMPL(8);
			UNIMPL(5);
			unsigned SIDL : 1;
			UNIMPL(1);
			unsigned ON : 1;
		};
	} CON;
	REGPADDING;
	union
	{
		unsigned int WORD;
		struct
		{
			unsigned CN0 : 1;
			unsigned CN1 : 1;
			unsigned CN2 : 1;
			unsigned CN3 : 1;
			unsigned CN4 : 1;
			unsigned CN5 : 1;
			unsigned CN6 : 1;
			unsigned CN7 : 1;
			unsigned CN8 : 1;
			unsigned CN9 : 1;
			unsigned CN10 : 1;
			unsigned CN11 : 1;
			unsigned CN12 : 1;
			unsigned CN13 : 1;
			unsigned CN14 : 1;
			unsigned CN15 : 1;
			unsigned CN16 : 1;
			unsigned CN17 : 1;
			unsigned CN18 : 1;
		};
	} EN;
	REGPADDING;
	union
	{
		unsigned int WORD;
		struct
		{
			unsigned CN0 : 1;
			unsigned CN1 : 1;
			unsigned CN2 : 1;
			unsigned CN3 : 1;
			unsigned CN4 : 1;
			unsigned CN5 : 1;
			unsigned CN6 : 1;
			unsigned CN7 : 1;
			unsigned CN8 : 1;
			unsigned CN9 : 1;
			unsigned CN10 : 1;
			unsigned CN11 : 1;
			unsigned CN12 : 1;
			unsigned CN13 : 1;
			unsigned CN14 : 1;
			unsigned CN15 : 1;
			unsigned CN16 : 1;
			unsigned CN17 : 1;
			unsigned CN18 : 1;
		};
	} PUEN;
} st_CN;

// /CN registers

volatile st_PORTS* PORTS;	//pages 70-76
volatile st_INT* INT;		//page 53
volatile st_TIMERS* TIMERS; //page 56
volatile st_SPI* SPI;		//page 61
volatile st_ADC* ADC;		//pages 62-63
volatile st_OC* OC;			//page 58
volatile st_IC* IC;			//page 57
volatile st_CN* CN;			//page 77

#endif // CTRLREGS_H
