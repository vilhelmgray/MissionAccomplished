dnl Copyright (C) 2015 William Breathitt Gray
dnl
dnl This file is part of Mission Accomplished.
dnl
dnl Mission Accomplished is free software: you can redistribute it
dnl and/or modify it under the terms of the GNU General Public License
dnl as published by the Free Software Foundation, either version 3 of
dnl the License, or (at your option) any later version.
dnl
dnl Mission Accomplished is distributed in the hope that it will be
dnl useful, but WITHOUT ANY WARRANTY; without even the implied warranty
dnl of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with Mission Accomplished.  If not, see
dnl <http://www.gnu.org/licenses/>.

AC_PREREQ([2.69])
AC_INIT([MissionAccomplished], [1.0], [vilhelm.gray@gmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/MissionAccomplished.cpp])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

SDL_VERSION=2.0.1
AM_PATH_SDL2($SDL_VERSION,
             :,
             AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
)
CXXFLAGS="$CXXFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"

AC_SEARCH_LIBS([IMG_Init], [SDL2_image],
               [],
               AC_MSG_ERROR([*** SDL2_image library not found])
)

AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_OUTPUT
