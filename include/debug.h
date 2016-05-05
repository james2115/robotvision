/* ---------------- (c) 2015 James Fisher (james@waters-fisher.id.au) - */ /*!

	\file

	\brief

	\details

	\copyright	2015 James Fisher (james@waters-fisher.id.au)

*/ /* --------------------------------------------------------------------- */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

#include "std.h"

#define	DEBUG_DEFAULTS_FILE	"./.default"

/* ---------------------------------------------------------------------------
 *
 *	Data and #define's.
 *
 * ------------------------------------------------------------------------ */

enum
{
	DEBUG_FATAL		= 0x00000001,	/*!Really bad error messages.			*/
	DEBUG_ERRNO		= 0x00000002,	/*!Show 'errno' information.			*/
	DEBUG_PRINTF	= 0x00000004,	/*!Normal printf() output.				*/

	DEBUG_DEBUG		= 0x00000010,	/*!Enable DEBUG messages.				*/
	DEBUG_INFO1		= 0x00000020,	/*!Debug code.							*/
	DEBUG_INFO2		= 0x00000040,	/*!More info.							*/

	DEBUG_ENTRYEXIT	= 0x00000100,	/*!Show entry/exit for tracking.    	*/

	DEBUG_HEADER	= 0x00001000,	/*!Show file/line/function header.		*/
	DEBUG_HEADER_D	= 0x00002000,	/*!Date stampheader.					*/
	DEBUG_HEADER_T	= 0x00004000,	/*!Time stampheader.					*/
	DEBUG_HEADER_F	= 0x00008000,	/*!Include function name.				*/
};

#if DEBUG_BUILD == 0

#define	DEBUG_DEFAULT	(DEBUG_FATAL | DEBUG_ERRNO | DEBUG_PRINTF)

#else

#define	DEBUG_DEFAULT (DEBUG_FATAL | DEBUG_ERRNO | DEBUG_PRINTF | DEBUG_DEBUG |	DEBUG_HEADER | DEBUG_HEADER_D | DEBUG_HEADER_T | DEBUG_HEADER_F)

#endif

#define	xprinth(fptr)														\
	if(::debug().isset(DEBUG_HEADER)) {										\
		if(::debug().isset(DEBUG_HEADER_D | DEBUG_HEADER_T)) {				\
			struct timeval now;												\
			gettimeofday(&now, NULL);										\
			tm *real = localtime(&now.tv_sec);								\
			if(::debug().isset(DEBUG_HEADER_D)) {								\
				fprintf(fptr, "%04d/%02d/%02d ", 1900+real->tm_year, 1+real->tm_mon, real->tm_mday);		\
			}																\
			if(::debug().isset(DEBUG_HEADER_T)) {								\
				fprintf(fptr, "%02d:%02d:%02d.%-6ld ", real->tm_hour, real->tm_min, real->tm_sec, now.tv_usec);		\
			}																\
		}																	\
		fprintf(fptr, "%s(%d) ", __FILE__, __LINE__);						\
		if(::debug().isset(DEBUG_HEADER_F)) {								\
			fprintf(fptr, "[%s] ", __PRETTY_FUNCTION__);					\
		}																	\
	}

#define	xprinte(fptr, level)												\
	if(level & DEBUG_ERRNO) {												\
		fprintf(fptr, "(errno=%d, \"%s\") ", errno, strerror(errno));		\
	}

#define xprintx(fptr, level, format...)										\
	do {																	\
		if(::debug().isset(level)) {											\
			fprintf(fptr, format);											\
			::fflush(fptr);													\
		}																	\
	} while(0)

#define xprintf(fptr, level, format...)										\
	do {																	\
		if(::debug().isset(level)) {										\
			xprinth(fptr);													\
			xprinte(fptr, level);											\
			fprintf(fptr, format);											\
			::fflush(fptr);													\
		}																	\
	} while(0)

#define	FATAL(format...)	xprintf(stderr, DEBUG_FATAL, format)
#define	ERRNO(format...)	xprintf(stdout, (DEBUG_FATAL | DEBUG_ERRNO), format)
#define	PRINTF(format...)	xprintf(stdout, DEBUG_PRINTF, format)
#define	DEBUG(format...)	xprintf(stdout, DEBUG_DEBUG, format)
#define	INFO1(format...)	xprintf(stdout, DEBUG_INFO1, format)
#define	INFO2(format...)	xprintf(stdout, DEBUG_INFO2, format)

#define	ENTRY()				xprintf(stdout, DEBUG_ENTRYEXIT, "-> ENTRY\n")
#define	EXIT()				xprintf(stdout, DEBUG_ENTRYEXIT, "<- EXIT\n")
#define	ENTRYPAR(format...)	xprintf(stdout, DEBUG_ENTRYEXIT, "-> "); xprintx(stdout, DEBUG_ENTRYEXIT, format)
#define	EXITPAR(format...)	xprintf(stdout, DEBUG_ENTRYEXIT, "<- "); xprintx(stdout, DEBUG_ENTRYEXIT, format)

#define	WIP()				PRINTF("WIP\n")
#define	HERE()				PRINTF("** Here!\n")

#define	DUMP(_b, _l)		PRINTF("** Memory Dump -> "); debug().dump((_b), (_l));
#define	DUMPW(_b, _l, _w)	PRINTF("** Memory Dump -> "); debug().dump((_b), (_l), (_w));

/* ----------------------------------------------------------------------------
 *
 *	External data and function prototypes.
 *
 * ------------------------------------------------------------------------- */

class debugc
{
private:
	char		version_[64];

	uint32_t	verbosity_;

public:
	debugc();
	~debugc();

	bool		isset(uint32_t _level);

	void		set(uint32_t _level);
	void		add(uint32_t _level);
	void		remove(uint32_t _level);
	uint32_t	get(void);

	void	check(int _argc, char **_argv);

	void	dump(unsigned char *_buffer, int _size, int _width =16);

	void	version(const char *_dir);
	char   *version(void);
};

extern	debugc	&debug(void);
	
extern	void	mybacktrace(void);

#endif
