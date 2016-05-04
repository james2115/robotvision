/* ---------------- (c) 2016 James Fisher (james@waters-fisher.id.au) - */ /*!

	\file		gearbox.h

	\brief

	\details

	\copyright	2016 James Fisher (james@waters-fisher.id.au)

*/ /* --------------------------------------------------------------------- */

#ifndef __gearbox_H__
#define __gearbox_H__

#include <exception>

/* -------------------------------------------------------------------- */ /*!

	Defines.

*/ /* --------------------------------------------------------------------- */

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

	Classes.

*/ /* --------------------------------------------------------------------- */

class ratio
{
private:

public:
	ratio();
	virtual ~ratio();
};

class gearbox 
{
private:

public:
	gearbox();
	virtual ~gearbox();

};

/* -------------------------------------------------------------------- */ /*!

	Functions.

*/ /* --------------------------------------------------------------------- */

#endif
