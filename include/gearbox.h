/* ---------------- (c) 2016 James Fisher (james@waters-fisher.id.au) - */ /*!

	\file		gearbox.h

	\brief

	\details

	\copyright	2016 James Fisher (james@waters-fisher.id.au)

*/ /* --------------------------------------------------------------------- */

#ifndef __gearbox_H__
#define __gearbox_H__

#include <exception>
#include <list>

/* -------------------------------------------------------------------- */ /*!

	Defines.

*/ /* --------------------------------------------------------------------- */

#define INCHES	25.4f

#define gearboxERR(_x) gearboxerrlog((char *) __FILE__, __LINE__, (char *) __FUNCTION__, gearboxerr::_x)

/* -------------------------------------------------------------------- */ /*!

	Error class.

*/ /* --------------------------------------------------------------------- */

class gearboxerr : public exception
{
public:
	enum errcode
	{
		InternalError,
	};

	static const char *errors_[];

private:
	errcode	error_;

public:
	gearboxerr(errcode _error) : error_(_error)
	{
	}

	virtual const char *what(void) const throw()
	{
		return(errors_[error_]);
	}
};

/* -------------------------------------------------------------------- */ /*!

	Logging error class.

*/ /* --------------------------------------------------------------------- */

class gearboxerrlog : public gearboxerr
{
private:
	char   *file_;
	int		line_;
	char   *function_;

	static	char	buffer_[512];

public:
	gearboxerrlog(char *_file, int _line, char *_function, gearboxerr::errcode _error)
	: gearboxerr(_error), file_(_file), line_(_line), function_(_function)
	{
	}

	virtual const char *what(void) const throw()
	{
		sprintf(buffer_, "%s [%s(%d)]", gearboxerr::what(), file_, line_);

		return(&buffer_[0]);
	}
};

/* -------------------------------------------------------------------- */ /*!

	Types.

*/ /* --------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */ /*!

	\class		gear

	\details

*/ /* --------------------------------------------------------------------- */

class gear
{
private:
	int		teeth_;						/*!< Number of teeth on this gear.	*/
	double	rotation_;					/*!< Angle of rotation per tooth.	*/

	gear   *parent_;					/*!< Gear linked to this gear.		*/
	gear   *child_;						/*!< Gear this gear is linked to.	*/

	shaft  *shaft_;						/*!< Shaft this gear is on.			*/

public:
	gear(int _teeth);
	virtual ~gear();

	void	add(shaft *_shaft);
	void	link(gear *_gear);
};

/* -------------------------------------------------------------------- */ /*!

	\class		wheel

	\details

*/ /* --------------------------------------------------------------------- */

class wheel
{
private:
	double	circumference_;				/*!< Wheel circumference in mm.		*/

	shaft  *shaft_;						/*!< Shaft this gear is on.			*/

public:
	wheel(double _radius);
	virtual ~wheel();

	void	add(shaft *_shaft);
};

/* -------------------------------------------------------------------- */ /*!

	\class		shaft

	\details

*/ /* --------------------------------------------------------------------- */

class shaft
{
private:
	std::list<gear *>	gears_;			/*!< List of gears on this shaft.	*/
	std::list<wheel *>	wheels_;		/*!< List of wheels on this shaft.	*/

public:
	shaft();
	virtual ~shaft();
	
	void	add(gear *_gear);
	void	add(wheel *_wheel);
};

/* -------------------------------------------------------------------- */ /*!

	\class		gearbox

	\details

*/ /* --------------------------------------------------------------------- */

class gearbox 
{
private:
	std::list<shaft *>	shafts_;		/*!< List of shafts in this gearbox	*/

public:
	gearbox();
	virtual ~gearbox();

	void	add(shaft *_shaft);
};

/* -------------------------------------------------------------------- */ /*!

	Functions.

*/ /* --------------------------------------------------------------------- */

#endif
