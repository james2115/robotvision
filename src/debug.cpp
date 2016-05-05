/* ---------------- (c) 2015 James Fisher (james@waters-fisher.id.au) - */ /*!

	\file

	\brief

	\details

	\copyright	2015 James Fisher (james@waters-fisher.id.au)

*/ /* --------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cxxabi.h>
#include <execinfo.h>

#include "std.h"

#include "debug.h"

/* ----------------------------------------------------------------------------
 *
 *	Data required for the debug output.
 *
 * ------------------------------------------------------------------------- */

debugc &debug(void)
{
	static	debugc	debugx;

	return(debugx);
}

/* -------------------------------------------- (c) 2008 James Fisher -- */ /*!
 * 
 *	{reason for the function here}
 *
 *	\brief		{quick description}
 *	\author		James Fisher
 *	\date		2008/../..
 *
 *	@param[in]
 *	@param[out]
 *
*/ /* ---------------------------------------------------------------------- */

debugc::debugc()
{
	sprintf(version_, "0.0.0.0");

	verbosity_ = DEBUG_DEFAULT;
}

/* -------------------------------------------- (c) 2008 James Fisher -- */ /*!
 * 
 *	{reason for the function here}
 *
 *	\brief		{quick description}
 *	\author		James Fisher
 *	\date		2008/../..
 *
 *	@param[in]
 *	@param[out]
 *
*/ /* ---------------------------------------------------------------------- */

debugc::~debugc()
{
}

/* -------------------------------------------- (c) 2008 James Fisher -- */ /*!
 * 
 *	{reason for the function here}
 *
 *	\brief		{quick description}
 *	\author		James Fisher
 *	\date		2008/../..
 *
 *	@param[in]
 *	@param[out]
 *
*/ /* ---------------------------------------------------------------------- */

bool debugc::isset(uint32_t _level)
{
	return((verbosity_ & _level) ? true : false);
}

/* -------------------------------------------------------------------- */ /*!

	\details

	\attention

	\author		James Fisher (james@waters-fisher.id.au)

	\date		2013/?/?

	\param

	\retval

	\see

*/ /* --------------------------------------------------------------------- */

void debugc::set(uint32_t _level)
{
	ENTRY();

	verbosity_ = _level;

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

void debugc::add(uint32_t _level)
{
	ENTRY();

	verbosity_ = verbosity_ | _level;

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

void debugc::remove(uint32_t _level)
{
	ENTRY();

	verbosity_ = verbosity_ & ~_level;

	EXIT();
}

/* -------------------------------------------------------------------- */ /*!

	\details

	\attention

	\author		James Fisher (james@waters-fisher.id.au)

	\date		2013/?/?

	\param

	\retval

	\see

*/ /* --------------------------------------------------------------------- */

uint32_t debugc::get(void)
{
	ENTRY();

	EXIT();

	return(verbosity_);
}

/* -------------------------------------------- (c) 2009 James Fisher -- */ /*!
 * 
 *	{reason for the function here}
 *
 *	\brief		{quick description}
 *	\author		James Fisher
 *	\date		2009/../..
 *
 *	@param[in]
 *	@param[out]
 *
*/ /* ---------------------------------------------------------------------- */

void debugc::version(const char *_dir)
{

#if 0

	char   *base;

	if((base = strstr((char *) svnver[1], _dir)) != NULL)
	{
		char   *bend;

		base = base + strlen(_dir);

		if((bend = strchr(base, '/')) != NULL)
		{
			int		size;

			size = bend - base;

			sprintf(version_, "%*.*s", size, size, base);
		}
	}

#endif

}

/* -------------------------------------------- (c) 2009 James Fisher -- */ /*!
 * 
 *	{reason for the function here}
 *
 *	\brief		{quick description}
 *	\author		James Fisher
 *	\date		2009/../..
 *
 *	@param[in]
 *	@param[out]
 *
*/ /* ---------------------------------------------------------------------- */

char *debugc::version(void)
{
	return(version_);
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

void debugc::check(int _argc, char **_argv)
{

#if 0

	if(cmdline.parse(_argc, _argv) != NULL)
	{
		std::string dlevel = cmdline.find("debug");

		if(dlevel.empty() == false)
		{
			debug().add(atoi(dlevel.c_str()));
		}
	}

#endif

}

/* -------------------------------------------------------------------- */ /*!

	\details

	\attention

	\author		James Fisher (james@waters-fisher.id.au)

	\date		2013/?/?

	\param

	\retval

	\see

*/ /* --------------------------------------------------------------------- */

void debugc::dump(uint8_t *_buffer, int _size, int _width)
{
	ENTRY();

	uint8_t	*buf = _buffer;

	int		i;
	int		offset = 0;

	printf("%p/0x%x(%d)\n", buf, _size, _size);

	do
	{
		printf("%08x ", offset);

		for(i = 0; i < _width; ++i)
		{
			if(i < _size)
			{
				printf("%02X ", buf[offset + i]);
			}
			else
			{
				printf("   ");
			}
		}

		for(i = 0; i < _width; ++i)
		{
			if(i < _size)
			{
				if((buf[offset + i] < 32) || (buf[offset + i] > 126))
				{
					printf(".");
				}
				else
				{
					printf("%c", buf[offset + i]);
				}
			}
			else
			{
				break;
			}
		}

		offset	= offset + _width;
		_size	= _size - _width;
		
		printf("\n");
		
	} while(_size > 0);

	EXIT();
}

/* -------------------------------------------- (c) 2010 James Fisher -- */ /*!
 * 
 *	{reason for the function here}
 *
 *	\brief		{quick description}
 *	\author		James Fisher
 *	\date		2010/../..
 *
 *	@param[in]
 *	@param[out]
 *
*/ /* ---------------------------------------------------------------------- */

#if 0

void mybacktrace(void)
{
	ENTRY();

	void   *pointers[16];

	size_t	count;

	char  **functions;

	count = backtrace(pointers, 16);

	functions = backtrace_symbols(pointers, count);

	size_t	i;

	for(i = 1; i < count; ++i)
	{
		size_t	sz = 200;

		char   *function = static_cast<char *>(malloc(sz));
		char   *begin = 0;
		char   *end = 0;

	    // find the parentheses and address offset surrounding the mangled name

		for(char *j = functions[i]; *j; ++j)
		{
			if (*j == '(')
			{
				begin = j;
			}
	        else
			{
				if (*j == '+')
				{
					end = j;
				}
			}
		}

		if(begin && end)
		{
			*begin++ = '\0';
			*end = '\0';

			// found our mangled name, now in [begin, end)

			int		status;

			char   *ret = abi::__cxa_demangle(begin, function, &sz, &status);

			if(ret != NULL)
			{
				// return value may be a realloc() of the input

				function = ret;
			}
			else
			{
				// demangling failed, just pretend it's a C function with no args

				strncpy(function, begin, sz);
				strncat(function, "()", sz);

				function[sz - 1] = '\0';
			}

			PRINTF("%s:%s\n", functions[i], function);
		}
		else
		{
			// didn't find the mangled name, just print the whole line

			PRINTF("%s\n", functions[i]);
		}

		free(function);
	}

	free(functions);

	EXIT();
}

#endif
