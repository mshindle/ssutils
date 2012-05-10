# create our directory definitions
CPPFLAGS = -DASSETDIR=\"$(SSU_ASSETS_DIR)\" -DCACHEDIR=\"$(SSU_CACHE_DIR)\" -DTMPDIR=\"$(SSU_TMP_DIR)\" @CPPFLAGS@

# cgi dir and programs
cgidir=$(prefix)/cgi-bin
cgi_PROGRAMS = yph capture

# variables
CGIC_LIB = $(top_builddir)/lib/libcgic.a

# yph configuration
yph_SOURCES = yph.c
yph_LDADD = $(CGIC_LIB)

# capture configuration
capture_SOURCES = capture.c
capture_LDADD = $(CGIC_LIB)

