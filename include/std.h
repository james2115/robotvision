/* ---------------- (c) 2015 James Fisher (james@waters-fisher.id.au) - */ /*!

	\file

	\brief

	\details

	\copyright	2015 James Fisher (james@waters-fisher.id.au)

*/ /* --------------------------------------------------------------------- */

#ifndef __STD_H__
#define __STD_H__

#define __STDC_FORMAT_MACROS

#include <stdint.h>
#include <inttypes.h>

using namespace std;

/* -------------------------------------------------------------------- */ /*!

	Basic macros.

*/ /* --------------------------------------------------------------------- */

#ifndef ABS
#define ABS(_x) ((_x) >= 0 ? (_x) : -(_x))
#endif

#ifndef SGN
#define SGN(_x) ((_x) == 0 ? (0) : (_x) < 0 ? (-1) : (1))
#endif

#ifndef ASIZE
#define ASIZE(_x) (sizeof(_x)/sizeof(_x[0]))
#endif

/* -------------------------------------------------------------------- */ /*!

	Expand #define macros to a string.

*/ /* --------------------------------------------------------------------- */

#define strEXP(_x) #_x
#define STREXP(_x) strEXP(_x)

#endif
