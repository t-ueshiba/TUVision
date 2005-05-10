#
#  $Id: Makefile,v 1.9 2005-05-10 05:20:26 ueshiba Exp $
#
#################################
#  User customizable macros	#
#################################
DEST		= $(LIBDIR)
INCDIR		= $(HOME)/include/TU
INCDIRS		= -I$(HOME)/include -I$(X11HOME)/include

NAME		= $(shell basename $(PWD))

CPPFLAGS	= -DUseXaw -DTUBrepPP_DEBUG
CFLAGS		= -O -g
CCFLAGS		= -O -g
LDFLAGS		=
LINKER		= $(CCC)
ifeq ($(CCC), icpc)
  CCFLAGS	= -O3 -parallel
endif

#########################
#  Macros set by mkmf	#
#########################
SUFFIX		= .cc:sC
EXTHDRS		= /home/ueshiba/include/TU/Array++.h \
		/home/ueshiba/include/TU/Brep/Brep++.h \
		/home/ueshiba/include/TU/Geometry++.h \
		/home/ueshiba/include/TU/Image++.h \
		/home/ueshiba/include/TU/List++.h \
		/home/ueshiba/include/TU/Manip.h \
		/home/ueshiba/include/TU/Object++.h \
		/home/ueshiba/include/TU/Vector++.h \
		/home/ueshiba/include/TU/types.h \
		/home/ueshiba/include/TU/v/CanvasPane.h \
		/home/ueshiba/include/TU/v/CanvasPaneDC.h \
		/home/ueshiba/include/TU/v/CmdPane.h \
		/home/ueshiba/include/TU/v/CmdWindow.h \
		/home/ueshiba/include/TU/v/Colormap.h \
		/home/ueshiba/include/TU/v/DC.h \
		/home/ueshiba/include/TU/v/Menu.h \
		/home/ueshiba/include/TU/v/TUv++.h \
		/home/ueshiba/include/TU/v/Widget-Xaw.h \
		/home/ueshiba/include/TU/v/XDC.h \
		TU/v/Vision++.h
HDRS		= Vision++.h
SRCS		= BrepCanvasPane.cc \
		BrepCmdPane.cc
OBJS		= BrepCanvasPane.o \
		BrepCmdPane.o

#########################
#  Macros used by RCS	#
#########################
REV		= $(shell echo $Revision: 1.9 $	|		\
		  sed 's/evision://'		|		\
		  awk -F"."					\
		  '{						\
		      for (count = 1; count < NF; count++)	\
			  printf("%d.", $$count);		\
		      printf("%d", $$count + 1);		\
		  }')

include $(PROJECT)/lib/l.mk
###
BrepCanvasPane.o: TU/v/Vision++.h /home/ueshiba/include/TU/Brep/Brep++.h \
	/home/ueshiba/include/TU/Object++.h /home/ueshiba/include/TU/types.h \
	/home/ueshiba/include/TU/Geometry++.h \
	/home/ueshiba/include/TU/Vector++.h \
	/home/ueshiba/include/TU/Array++.h \
	/home/ueshiba/include/TU/v/CmdPane.h \
	/home/ueshiba/include/TU/v/CmdWindow.h \
	/home/ueshiba/include/TU/v/TUv++.h \
	/home/ueshiba/include/TU/v/Colormap.h \
	/home/ueshiba/include/TU/Image++.h /home/ueshiba/include/TU/List++.h \
	/home/ueshiba/include/TU/v/Widget-Xaw.h \
	/home/ueshiba/include/TU/v/CanvasPaneDC.h \
	/home/ueshiba/include/TU/v/XDC.h /home/ueshiba/include/TU/v/DC.h \
	/home/ueshiba/include/TU/Manip.h \
	/home/ueshiba/include/TU/v/CanvasPane.h \
	/home/ueshiba/include/TU/v/Menu.h
BrepCmdPane.o: TU/v/Vision++.h /home/ueshiba/include/TU/Brep/Brep++.h \
	/home/ueshiba/include/TU/Object++.h /home/ueshiba/include/TU/types.h \
	/home/ueshiba/include/TU/Geometry++.h \
	/home/ueshiba/include/TU/Vector++.h \
	/home/ueshiba/include/TU/Array++.h \
	/home/ueshiba/include/TU/v/CmdPane.h \
	/home/ueshiba/include/TU/v/CmdWindow.h \
	/home/ueshiba/include/TU/v/TUv++.h \
	/home/ueshiba/include/TU/v/Colormap.h \
	/home/ueshiba/include/TU/Image++.h /home/ueshiba/include/TU/List++.h \
	/home/ueshiba/include/TU/v/Widget-Xaw.h \
	/home/ueshiba/include/TU/v/CanvasPaneDC.h \
	/home/ueshiba/include/TU/v/XDC.h /home/ueshiba/include/TU/v/DC.h \
	/home/ueshiba/include/TU/Manip.h \
	/home/ueshiba/include/TU/v/CanvasPane.h \
	/home/ueshiba/include/TU/v/Menu.h
