#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([cyberprobe], [0.30], [cyberprobe-general@lists.sourceforge.net])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_SRCDIR([src/target.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_AR

# Libtool
LT_INIT

# Checks for libraries.
# FIXME: Replace `main' with functions in libraries:
AC_CHECK_LIB([boost_regex], [main], [], 
			    [AC_MSG_ERROR(Library boost_regex missing.)])
AC_CHECK_LIB([expat], [main], [], [AC_MSG_ERROR(Library expat missing.)])
AC_CHECK_LIB([lua], [main], [], [AC_MSG_ERROR(Library lua missing.)])
AC_CHECK_LIB([ncurses], [main], [], [AC_MSG_ERROR(Library ncurses missing.)])
AC_CHECK_LIB([pcap], [main], [], [AC_MSG_ERROR(Library pcap missing.)])
AC_CHECK_LIB([pthread], [main], [], [AC_MSG_ERROR(Library pthread missing.)])
AC_CHECK_LIB([readline], [main], [], [AC_MSG_ERROR(Library readline missing.)])

# LUA specifics
#AC_CHECK_LIB([lua], [lua_open], [AC_DEFINE([HAVE_LUA_OPEN], 1, [I am a buynchy])])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netdb.h netinet/in.h stdint.h stdlib.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_CHECK_FUNCS([gethostbyname gettimeofday socket strdup uname])

AC_CONFIG_FILES([Makefile src/Makefile])

AC_OUTPUT