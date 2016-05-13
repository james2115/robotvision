/* ---------------- (c) 2016 James Fisher (james@waters-fisher.id.au) - */ /*!

	\file		gearbox.cpp

	\brief

	\details

	\copyright	2016 James Fisher (james@waters-fisher.id.au)

*/ /* --------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

#include "std.h"
#include "debug.h"

#include "gearbox.h"

void test(void)
{
	lhsgearbox = new gearbox();

	/* Define the motor first */

	motorshaft = new shaft();

	motorgear = new gear(14);

//	motorgear->set();
	
	motorshaft->add(motorgear);

	lhsgearbox->add(motorshaft);

	/* Now define the 1st level step down */

	stepshaft = new shaft();

	stepgearbase = new gear(50);

	stepgearbase->link(motorgear);

	stepshaft->add(stepgearbase);

	stepgearout = new gear(19);

	stepshaft->add(stepgearout);

	lhsgearbox->add(stepshaft);

	/* Now define the final drive shaft */

	outputshaft = new shaft();

	outputgear = new gear(45);

	outputgear->link(stepgearout);

	outputshaft->add(outputgear);

	/* and the wheel */

	drivewheel = new wheel(4 * INCHES);

	outputshaft->add(drivewheel);

	/* Add the output to the gearbox */

	lhsgearbox->add(outputshaft);
}

/* -------------------------------------------------------------------- */ /*!

	

*/ /* --------------------------------------------------------------------- */

char gearboxerrlog::buffer_[512];

/* -------------------------------------------------------------------- */ /*!

	

*/ /* --------------------------------------------------------------------- */

const char *gearboxerr::errors_[] =
{
	"internal error",
};

/* -------------------------------------------------------------------- */ /*!

	\details

	\attention

	\verbatim
	\endverbatim

	\author		James Fisher (james@waters-fisher.id.au)
	\date		

	\param

	\throw

	\retval

	\see
	\todo

*/ /* --------------------------------------------------------------------- */

ratio::ratio()
{
	ENTRY();

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details

	\attention

	\verbatim
	\endverbatim

	\author		James Fisher (james@waters-fisher.id.au)
	\date		

	\param

	\throw

	\retval

	\see
	\todo

*/ /* --------------------------------------------------------------------- */

ratio::~ratio()
{
	ENTRY();

	EXIT();
}
/* -------------------------------------------------------------------- */ /*!

	\details

	\attention

	\verbatim
	\endverbatim

	\author		James Fisher (james@waters-fisher.id.au)
	\date		

	\param

	\throw

	\retval

	\see
	\todo

*/ /* --------------------------------------------------------------------- */

gearbox::gearbox()
{
	ENTRY();

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details

	\attention

	\verbatim
	\endverbatim

	\author		James Fisher (james@waters-fisher.id.au)
	\date		

	\param

	\throw

	\retval

	\see
	\todo

*/ /* --------------------------------------------------------------------- */

gearbox::~gearbox()
{
	ENTRY();

	EXIT();
}
