#define SYSCLK	72000000
#define HCLK	SYSCLK
#define PCLK2	HCLK
#define PCLK1	(HCLK/2)
#define TIMXCLK ((HCLK == PCLK1)?(PCLK1):(PCLK1*2))

#define RAM_START	0x20000000
#define RAM_END		0x20004FFF
#define HEAP_BASE	(((unsigned int)&__ZI_LIMIT__ + 0x7) & ~0x7)
#define HEAP_SIZE	(4*1024)
#define HEAP_LIMIT	(HEAP_BASE + HEAP_SIZE)

#define PSP_LIMIT	(HEAP_LIMIT + 8)
#define PSP_BASE	(MSP_LIMIT)
#define PSP_SIZE	(PSP_BASE - PSP_LIMIT)

#define MSP_BASE	(RAM_END + 1)
#define MSP_SIZE	(1*1024)
#define MSP_LIMIT	(MSP_BASE - MSP_SIZE)


