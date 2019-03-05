#ifndef DEBUG_H

#define DEBUG_H
#include "../libft/includes/libft.h"

#define is_aligned(POINTER, BYTE_COUNT) \
	    (((uintptr_t)(const void *)(POINTER)) % (BYTE_COUNT) == 0)
#define ba ft_putstr(" ");
#define debug(fname,lineno, fxname) { \
	ft_putstr(fname); \
	ba \
	ft_putnbr(lineno); \
	ba \
	ft_putendl(fxname);}
#define d debug(__FILE__, __LINE__, __func__);
#define s ft_putendl("");

#endif
