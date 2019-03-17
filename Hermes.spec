%define version 1.3.2
%define prefix /usr

Summary: HERMES pixel format conversion library
Name: Hermes
Version: %{version}
Release: 1
Copyright: LGPL
Group: Development/Libraries
Source: http://dark.x.dtu.dk/~mbn/clanlib/download/Hermes-%{version}.tar.gz
BuildRoot: /tmp/hermes-root
Packager: brn (c.nentwich@cs.ucl.ac.uk)
URL: http://clanlib.org/hermes


%description
HERMES is a library designed to convert a source buffer with a specified 
pixel format to a destination buffer with possibly a different format at
the maximum possible speed.

On x86 and MMX architectures, handwritten assembler routines are taking over
the job and doing it lightning fast.

On top of that, HERMES provides fast surface clearing, stretching and some
dithering. Supported platforms are basically all that have an ANSI C
compiler as there is no platform specific code but those are supported: DOS,
Win32 (Visual C), Linux, FreeBSD (IRIX, Solaris are on hold at the moment),
some BeOS support.


%prep
%setup


%build
CC=gcc CFLAGS="-O6 -mpentium -malign-functions=2 -malign-loops=2 -malign-jumps=2" ./configure --prefix=%{prefix}
make


%install
make prefix=$RPM_BUILD_ROOT%{prefix} install


%clean
make distclean
rm -rf $RPM_BUILD_ROOT

%files
%doc AUTHORS CHANGES COPYING INSTALL.DOS INSTALL.unix TODO TODO.conversion docs/api/*.htm
%attr(-, root, root) %{prefix}/lib/*
%attr(-, root, root) %{prefix}/include/*
