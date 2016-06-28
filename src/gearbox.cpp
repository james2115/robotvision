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

	\details	gear constructor.

	\author		James Fisher (james@waters-fisher.id.au)
	\date		Tuesday 17 May 2016 03:36:38pm

	\param		_teeth			Number of teeth on the gear.

*/ /* --------------------------------------------------------------------- */

gear::gear(int _teeth)
{
	ENTRY();

	teeth_	  = _teeth;

	rotation_ = 1.0f / teeth_;

	parent_ = NULL;
	child_  = NULL;

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details	gear destructor.

	\author		James Fisher (james@waters-fisher.id.au)
	\date		Tuesday 17 May 2016 03:39:01pm

*/ /* --------------------------------------------------------------------- */

gear::~gear()
{
	ENTRY();

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details	Keep track of the shaft this wheel has been added to.

	\author		James Fisher (james@waters-fisher.id.au)
	\date		Tuesday 28 June 2016 03:49:16P	

	\param		_shaft		Shaft this wheel has been added to.

*/ /* --------------------------------------------------------------------- */

void gear::add(shaft *_shaft)
{
	ENTRY();

	shaft_ = _shaft;

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details	Link this gear to another gear.

	\author		James Fisher (james@waters-fisher.id.au)
	\date		Tuesday 17 May 2016 03:39:48pm

	\param		_gear		Pointer to the \ref gear to link to.

*/ /* --------------------------------------------------------------------- */

void gear::link(gear *_gear)
{
	ENTRY();

	child_ = _gear;

	_gear->parent = this;

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details	wheel constructor.

	\author		James Fisher (james@waters-fisher.id.au)
	\date		Tuesday 17 May 2016 03:41:39pm

	\param		_radius		Radius of the wheel in mm.

*/ /* --------------------------------------------------------------------- */

wheel::wheel(double _radius)
{
	ENTRY();

	circumference_ = 2.0f * PI * _radius;

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details	Keep track of the shaft this wheel has been added to.

	\author		James Fisher (james@waters-fisher.id.au)
	\date		Tuesday 28 June 2016 03:49:16P	

	\param		_shaft		Shaft this wheel has been added to.

*/ /* --------------------------------------------------------------------- */

void wheel::add(shaft *_shaft)
{
	ENTRY();

	shaft_ = _shaft;

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details	wheel destructor.

	\author		James Fisher (james@waters-fisher.id.au)
	\date		Tuesday 17 May 2016 03:42:26pm

*/ /* --------------------------------------------------------------------- */

wheel::~wheel()
{
	ENTRY();

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details	shaft constructor.

	\author		James Fisher (james@waters-fisher.id.au)
	\date		Tuesday 17 May 2016 03:43:18pm

*/ /* --------------------------------------------------------------------- */

shaft::shaft()
{
	ENTRY();

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details	shaft destructor.

	\author		James Fisher (james@waters-fisher.id.au)
	\date		Tuesday 17 May 2016 03:43:55pm

*/ /* --------------------------------------------------------------------- */

shaft::~shaft()
{
	ENTRY();

	for(auto i : gears_)
	{
	}

	for(auto i : wheels_)
	{
	}

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details	Add a \ref gear to this shaft.

	\author		James Fisher (james@waters-fisher.id.au)
	\date		Tuesday 17 May 2016 03:44:39pm

	\param		_gear		Pointer to the gear to add to the shaft.

*/ /* --------------------------------------------------------------------- */

void shaft::add(gear *_gear)
{
	ENTRY();

	gears_.push_front(_gear);

	_gear->add(this);

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details	Add a \ref wheel to this shaft.

	\author		James Fisher (james@waters-fisher.id.au)
	\date		Tuesday 17 May 2016 03:45:41pm

	\param		_wheel		Pointer to the wheel to add to the shaft.

*/ /* --------------------------------------------------------------------- */

void shaft::add(wheel *_wheel)
{
	ENTRY();

	wheels_.push_front(_wheel);

	_wheel->add(this);

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details	gearbox constructor.

	\author		James Fisher (james@waters-fisher.id.au)
	\date		Tuesday 17 May 2016 03:46:34pm

*/ /* --------------------------------------------------------------------- */

gearbox::gearbox()
{
	ENTRY();

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details	gearbox destructor.

	\author		James Fisher (james@waters-fisher.id.au)
	\date		Tuesday 17 May 2016 03:47:04pm

*/ /* --------------------------------------------------------------------- */

gearbox::~gearbox()
{
	ENTRY();

	for(auto i : shafts_)
	{
	}

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details	Add a shaft to this gearbox.

	\author		James Fisher (james@waters-fisher.id.au)
	\date		Tuesday 17 May 2016 03:47:27pm

	\param		_shaft		Pointer to the shaft to add.

*/ /* --------------------------------------------------------------------- */

void gearbox::add(shaft *_shaft)
{
	ENTRY();

	shaft_.push_front(_shaft);

	EXIT();
}
