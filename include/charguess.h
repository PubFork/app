/*
	libcharguess	-	Guess the encoding/charset of a string
    Copyright (C) 2003  Stephane Corbe <noubi@users.sourceforge.net>
	Based on Mozilla sources

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "aura/aura/aura.h"

#if defined(_AURA_CHARGUESS)
#define CHARGUESS_API  CLASS_DECL_EXPORT
#else
#define CHARGUESS_API  CLASS_DECL_IMPORT
#endif

typedef void * charguess;

BEGIN_EXTERN_C

CHARGUESS_API charguess CharGuessInit(void);
CHARGUESS_API string GuessChardet(charguess * p, const char *str);
CHARGUESS_API void CharGuessDestroy(charguess * p);


END_EXTERN_C
















