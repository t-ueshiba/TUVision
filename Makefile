#
#  $Id: Makefile,v 1.3 2002-07-29 00:09:06 ueshiba Exp $
#
#################################
#  User customizable macros	#
#################################
DEST		= $(LIBDIR)
INCDIR		= $(HOME)/include/TU/v
INCDIRS		= -I$(HOME)/include -I$(X11HOME)/include

NAME		= $(shell basename $(PWD))

CPPFLAGS	= -DUseXaw -DTUBrepPP_DEBUG
CFLAGS		= -g
CCFLAGS		= -g

LINKER		= $(CCC)

#########################
#  Macros set by mkmf	#
#########################
SUFFIX		= .cc:sC
EXTHDRS		= /Users/ueshiba/include/TU/Array++.h \
		/Users/ueshiba/include/TU/Brep/Brep++.h \
		/Users/ueshiba/include/TU/Geometry++.h \
		/Users/ueshiba/include/TU/Image++.h \
		/Users/ueshiba/include/TU/List++.h \
		/Users/ueshiba/include/TU/Manip.h \
		/Users/ueshiba/include/TU/Object++.h \
		/Users/ueshiba/include/TU/Vector++.h \
		/Users/ueshiba/include/TU/types.h \
		/Users/ueshiba/include/TU/v/CanvasPane.h \
		/Users/ueshiba/include/TU/v/CanvasPaneDC.h \
		/Users/ueshiba/include/TU/v/CmdPane.h \
		/Users/ueshiba/include/TU/v/CmdWindow.h \
		/Users/ueshiba/include/TU/v/Colormap.h \
		/Users/ueshiba/include/TU/v/DC.h \
		/Users/ueshiba/include/TU/v/Menu.h \
		/Users/ueshiba/include/TU/v/TUv++.h \
		/Users/ueshiba/include/TU/v/Widget-Xaw.h \
		/Users/ueshiba/include/TU/v/XDC.h \
		TU/v/Vision++.h
HDRS		= Vision++.h
SRCS		= BrepCanvasPane.cc \
		BrepCmdPane.cc
OBJS		= BrepCanvasPane.o \
		BrepCmdPane.o

#########################
#  Macros used by RCS	#
#########################
REV		= $(shell echo $Revision: 1.3 $	|		\
		  sed 's/evision://'		|		\
		  awk -F"."					\
		  '{						\
		      for (count = 1; count < NF; count++)	\
			  printf("%d.", $$count);		\
		      printf("%d", $$count + 1);		\
		  }')

include $(PROJECT)/lib/l.mk
include $(PROJECT)/lib/RCS.mk
###
BrepCanvasPane.o: TU/v/Vision++.h /Users/ueshiba/include/TU/Brep/Brep++.h \
	/Users/ueshiba/include/TU/Object++.h \
	/Users/ueshiba/include/TU/types.h \
	/Users/ueshiba/include/TU/Geometry++.h \
	/Users/ueshiba/include/TU/Vector++.h \
	/Users/ueshiba/include/TU/Array++.h \
	/Users/ueshiba/include/TU/v/CmdPane.h \
	/Users/ueshiba/include/TU/v/CmdWindow.h \
	/Users/ueshiba/include/TU/v/TUv++.h \
	/Users/ueshiba/include/TU/v/Colormap.h \
	/Users/ueshiba/include/TU/Image++.h \
	/Users/ueshiba/include/TU/List++.h \
	/Users/ueshiba/include/TU/v/Widget-Xaw.h \
	/Users/ueshiba/include/TU/v/CanvasPaneDC.h \
	/Users/ueshiba/include/TU/v/XDC.h /Users/ueshiba/include/TU/v/DC.h \
	/Users/ueshiba/include/TU/Manip.h \
	/Users/ueshiba/include/TU/v/CanvasPane.h \
	/Users/ueshiba/include/TU/v/Menu.h
BrepCmdPane.o: TU/v/Vision++.h /Users/ueshiba/include/TU/Brep/Brep++.h \
	/Users/ueshiba/include/TU/Object++.h \
	/Users/ueshiba/include/TU/types.h \
	/Users/ueshiba/include/TU/Geometry++.h \
	/Users/ueshiba/include/TU/Vector++.h \
	/Users/ueshiba/include/TU/Array++.h \
	/Users/ueshiba/include/TU/v/CmdPane.h \
	/Users/ueshiba/include/TU/v/CmdWindow.h \
	/Users/ueshiba/include/TU/v/TUv++.h \
	/Users/ueshiba/include/TU/v/Colormap.h \
	/Users/ueshiba/include/TU/Image++.h \
	/Users/ueshiba/include/TU/List++.h \
	/Users/ueshiba/include/TU/v/Widget-Xaw.h \
	/Users/ueshiba/include/TU/v/CanvasPaneDC.h \
	/Users/ueshiba/include/TU/v/XDC.h /Users/ueshiba/include/TU/v/DC.h \
	/Users/ueshiba/include/TU/Manip.h \
	/Users/ueshiba/include/TU/v/CanvasPane.h \
	/Users/ueshiba/include/TU/v/Menu.h
