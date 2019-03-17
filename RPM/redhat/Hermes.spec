Name: Hermes 
Summary: HERMES pixel format conversion library
Version: 1.3.3
Release: 0.CVS20011016
Copyright: LGPL
Group: System Environment/Libraries
Source: http://dark.x.dtu.dk/~mbn/clanlib/download/%{name}-%{version}.tar.bz2
BuildRoot: %{_tmppath}/%{name}-buildroot
URL: http://clanlib.org/hermes

%description
HERMES is a library designed to convert a source buffer with a specified pixel
format to a destination buffer with possibly a different format at the maximum
possible speed.

On x86 and MMX architectures, handwritten assembler routines are taking over
the job and doing it lightning fast.

On top of that, HERMES provides fast surface clearing, stretching and some
dithering. Supported platforms are basically all that have an ANSI C compiler
as there is no platform specific code but those are supported: DOS, Win32
(Visual C), Linux, FreeBSD (IRIX, Solaris are on hold at the moment), some BeOS
support.

%package devel
Summary: development tools for %{name}
Group: Development/Libraries
Requires: %{name}

%description devel
The %{name}-devel package contains the static libraries and header files
needed for development with %{name}.

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%prep
%setup -q

%build
./autogen.sh
%configure
make

%install
%makeinstall

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-, root, root, 0755)
%doc AUTHORS COPYING INSTALL.unix TODO TODO.conversion 
%{_libdir}/lib*.so.*

%files devel
%defattr(-, root, root)
%doc docs/api/*.htm
%{_includedir}/*
%{_libdir}/lib*.so
%{_libdir}/*.?a

%changelog
* Tue Oct 16 2001 Jeroen Janssen <japj@clanlib.org>
- upgrading to Hermes 1.3.3
- fixed ./autogen.sh not being called from %build

* Thu Jan  4 2001 Tim Powers <timp@redhat.com>
- fixed bad groups

* Tue Nov 28 2000 Bernhard Rosenkraenzer <bero@redhat.com>
- move to Powertools (was Extrabinge)
- Fix build on alpha
- Don't include INSTALL.DOS in the docs

