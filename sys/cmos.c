#include <sys/types.h>
#include <sys/defs.h>
#include <sys/x86.h>
#include <sys/traps.h>

// cmos.c

#define		CURRENT_YEAR		2000	// not crucially accurate, YY value
										// lass than the lower two digits - 10
										// will be assumed to be in the future

#define		JULIAN_EPOCH		2440588  // this is 1970-01-01 Julian date

#define		CMOS_UPDATE_FLAG	0x40

#define		CMOS_CTRL_PORT		0x70
#define		CMOS_DATA_PORT		0x71

#define		CMOS_FLOPPY_REG		0x10
#define		CMOS_SEC_REG		0x00
#define		CMOS_MIN_REG		0x02
#define		CMOS_HOUR_REG		0x04
#define		CMOS_DOW_REG		0x06
#define		CMOS_DAY_REG		0x07
#define		CMOS_MONTH_REG		0x08
#define		CMOS_YEAR_REG		0x09
#define		CMOS_CENTURY_REG	0x32		// often doesn't exist
#define		CMOS_STAT_A_REG		0x0a
#define		CMOS_STAT_B_REG		0x0b
#define		CMOS_STAT_C_REG		0x0c

int64_t	unixtime = 0;

enum dow {
	MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
};

enum months { 
	JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY,
	AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
};

struct cmos_time_struct {
	
	uint8_t	sec;
	uint8_t	min;
	uint8_t	hour;
	uint8_t	dow;				// day of week - we don't use this since
								// many cmos chips don't keep this updated
	uint8_t	day;
	uint8_t	month;
	uint8_t	year;
	uint8_t	stat_a;
	uint8_t	stat_b;
};

struct cmos_time_struct cmos_time;

uint64_t cmos_to_julian() {

	uint32_t a = (14 - cmos_time.month) / 12;
	uint32_t y = (cmos_time.year + 2000) + 4800 - a;
	uint32_t m = cmos_time.month + 12 * a - 3;

	// we're off by one here and I don't know why, this should be fixed !
	return (cmos_time.day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045);
}

uint8_t bcd2dec(uint8_t bcd) {
	return (((bcd & 0xF0) >> 4) * 10) + (bcd & 0x0F);
}

int64_t sys_time () {
	return unixtime;
}

void update_unixtime() {

	unixtime = cmos_time.sec + cmos_time.min * 60 + cmos_time.hour * 60 * 60 
		+ (cmos_to_julian() - JULIAN_EPOCH) * 60 * 60 * 24;
}

void cmos_read_values() {

	outb(CMOS_CTRL_PORT, CMOS_SEC_REG);
	cmos_time.sec = bcd2dec(inb(CMOS_DATA_PORT));
	
	outb(CMOS_CTRL_PORT, CMOS_MIN_REG);
	cmos_time.min = bcd2dec(inb(CMOS_DATA_PORT));
	
	outb(CMOS_CTRL_PORT, CMOS_HOUR_REG);
	cmos_time.hour = bcd2dec(inb(CMOS_DATA_PORT));
	
	outb(CMOS_CTRL_PORT, CMOS_DAY_REG);
	cmos_time.day = bcd2dec(inb(CMOS_DATA_PORT));

	outb(CMOS_CTRL_PORT, CMOS_MONTH_REG);
	cmos_time.month = bcd2dec(inb(CMOS_DATA_PORT));

	outb(CMOS_CTRL_PORT, CMOS_YEAR_REG);
	cmos_time.year = bcd2dec(inb(CMOS_DATA_PORT));
}

void rtcintr() {

//	cprintf("IRQ_RTC\n");

	cmos_read_values();

	update_unixtime();

	outb(CMOS_CTRL_PORT, CMOS_STAT_C_REG);		// must read C reg to allow
											// further interrupts
	inb(CMOS_DATA_PORT);

	return;
}

void cmosinit() {

	outb(CMOS_CTRL_PORT, CMOS_STAT_B_REG);
	outb(CMOS_DATA_PORT, 0x10); // IRQ 8 on update
	picenable(IRQ_RTC);
	ioapicenable(IRQ_RTC, 1);

//	cprintf("CMOS time %d-%d-%d %d:%d.%d\n", cmos_time.year + 2000, cmos_time.month, 
//			cmos_time.day, cmos_time.hour, cmos_time.min, cmos_time.sec);

//	cprintf("Julian date: %d\n", cmos_to_julian());
}
