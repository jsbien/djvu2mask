bin_PROGRAMS = ddjvu

jb2cmp_SOURCES = jb2cmp/classify.cpp jb2cmp/cuts.cpp		\
 jb2cmp/frames.cpp jb2cmp/patterns.cpp jb2cmp/classify.h	\
 jb2cmp/mdjvucfg.h jb2cmp/minidjvu.h jb2cmp/patterns.h

AM_CPPFLAGS = -I$(top_srcdir)/libdjvu
AM_CXXFLAGS = $(PTHREAD_CFLAGS)

DJLIB = $(top_builddir)/libdjvu/libdjvulibre.la


ddjvu_SOURCES = ddjvu.cpp tiff2pdf.c tiff2pdf.h
ddjvu_CPPFLAGS = -I$(top_srcdir)  $(AM_CPPFLAGS) $(TIFF_CFLAGS)
if HAVE_OS_WIN32
ddjvu_CPPFLAGS += -D__USE_MINGW_ANSI_STDIO
endif
ddjvu_CFLAGS = $(THREAD_CFLAGS)
ddjvu_LDADD = $(DJLIB) $(TIFF_LIBS) $(PTHREAD_LIBS)

dist_man1_MANS =  ddjvu.1 



