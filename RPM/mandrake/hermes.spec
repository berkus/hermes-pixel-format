%define name hermes
%define version 1.3.3
%define release 0.CVS.20011017
%define prefix %{_prefix}
%define lib_name_orig libhermes
%define lib_major 1
%define lib_name %{lib_name_orig}%{lib_major}

Name: %{name}
Summary: Hermes pixel format conversion library
Version: %{version}
Release: %{release}
Copyright: LGPL
Group: System/Libraries
Source: http://dark.x.dtu.dk/~mbn/clanlib/download/Hermes-%{version}.tar.bz2
Packager: Jeroen Janssen <japj@clanlib.org>
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

%package -n %{lib_name}
Summary: Main library for %{name}
Group: System/Libraries
Obsoletes: Hermes hermes
Provides: Hermes hermes

%description -n %{lib_name}
This package contains the library needed to run programs dynamically
linked with %{name}.

%package -n %{lib_name}-devel
Summary: Headers for developing programs that will use %{name}
Group: Development/C
Requires: %{lib_name} = %{version}
Provides: %{lib_name_orig}-devel
Obsoletes: Hermes-devel hermes-devel
Provides: Hermes-devel hermes-devel

%description -n %{lib_name}-devel
This package contains the headers that programmers will need to develop
applications which will use %{name}.

%post -n %{lib_name} -p /sbin/ldconfig

%postun -n %{lib_name} -p /sbin/ldconfig

%prep
%setup -q -n Hermes-%{version}

%build
./autogen.sh
%configure
make

%install
%makeinstall

%clean
rm -rf $RPM_BUILD_ROOT

%files -n %{lib_name}
%defattr(-, root, root, 0755)
%doc AUTHORS COPYING INSTALL.DOS INSTALL.unix TODO TODO.conversion 
%{_libdir}/lib*.so.*

%files -n %{lib_name}-devel
%defattr(-, root, root)
%doc docs/api/*.htm
%{_includedir}/*
%{_libdir}/lib*.so
%{_libdir}/*.?a


%changelog
* Wed Oct 17 2001 Jeroen Janssen <japj@clanlib.org> 1.3.3-0.CVS.20011017
- upgrade to hermes 1.3.3

* Thu Aug 30 2001 Guillaume Cottenceau <gc@mandrakesoft.com> 1.3.2-6mdk
- fix provides

* Mon Nov 27 2000 Guillaume Cottenceau <gc@mandrakesoft.com> 1.3.2-5mdk
- new lib policy

* Tue Nov  7 2000 Guillaume Cottenceau <gc@mandrakesoft.com> 1.3.2-4mdk
- provides Hermes for compatibility

* Fri Nov  3 2000 Guillaume Cottenceau <gc@mandrakesoft.com> 1.3.2-3mdk
- change name to hermes (e.g. uppercase names suck)

* Wed Aug 23 2000 Guillaume Cottenceau <gc@mandrakesoft.com> 1.3.2-2mdk
- automatically added packager tag

* Mon Jul 24 2000 Guillaume Cottenceau <gc@mandrakesoft.com> 1.3.2-1mdk
- 1.3.2

* Tue Jul 18 2000 Guillaume Cottenceau <gc@mandrakesoft.com> 1.3.1-5mdk
- BM

* Mon Jul 10 2000 Guillaume Cottenceau <gc@mandrakesoft.com> 1.3.1-4mdk
- macros

* Mon Jul 10 2000 Lenny Cartier <lenny@mandrakesoft.com> 1.3.1-3mdk
- bzip2 sources

* Sat Jul 01 2000 Stefan van der Eijk <s.vandereijk@chello.nl> 1.3.1-2mdk
- makeinstall macro

* Wed May 31 2000 Guillaume Cottenceau <gc@mandrakesoft.com> 1.3.1-1mdk
- took SRPM from Hermes web site
- (a lot of) Mandrake adaptations including split between main and devel
