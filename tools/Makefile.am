bin_PROGRAMS = ddjvu djvu2mask

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

djvu2mask_SOURCES = djvu2mask.cpp
djvu2mask_CPPFLAGS = -I$(top_srcdir) $(AM_CPPFLAGS)
djvu2mask_LDADD = $(DJLIB)

dist_man1_MANS =  ddjvu.1 




