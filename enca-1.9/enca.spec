# @(#) $Id: enca.spec.in,v 1.28 2005/12/18 12:05:30 yeti Exp $
Summary: A program detecting encoding of text files.
Name: enca
Version: 1.9
Release: 1
License: GNU GPL v2
Group: Applications/Text
Requires: sed
Source: http://trific.ath.cx/Ftp/enca/enca-1.9.tar.bz2
URL: http://trific.ath.cx/software/enca/
Packager: David Necas (Yeti) <yeti@physics.muni.cz>
Vendor: Trific soft.
Prefix: %{_prefix}
BuildRoot: %{_tmppath}/%{name}-%{version}-buildroot

%description
Enca is an Extremely Naive Charset Analyser. It detects character set and
encoding of text files and can also convert them to other encodings using
either a built-in convertor or external libraries and tools like libiconv,
librecode, or cstocs.

Currently, it has support for Belarussian, Bulgarian, Croatian, Czech,
Estonian, Latvian, Lithuanian, Polish, Russian, Slovak, Slovene, Ukrainian,
Chinese, and some multibyte encodings (mostly variants of Unicode)
independent on the language.

This package also contains shared Enca library other programs can make use of.

Install Enca if you need to cope with text files of dubious origin
and unknown encoding and convert them to some reasonable encoding.

%package devel
Summary: Header files and libraries for Enca development.
Group: Development/Libraries
Requires: %{name} = %{version}
%description devel
The enca-devel package contains the static libraries and header files
for writing programs using the Extremely Naive Charset Analyser library,
and its API documentation.

Install enca-devel if you are going to create applications using the Enca
library.

%prep
%setup

%build
%configure
%__make

%install
[ "$RPM_BUILD_ROOT" != "/" ] && %__rm -rf $RPM_BUILD_ROOT
%makeinstall HTML_DIR=$RPM_BUILD_ROOT/%{_datadir}/gtk-doc/html

%clean
[ "$RPM_BUILD_ROOT" != "/" ] && %__rm -rf $RPM_BUILD_ROOT

%files
%defattr(755,root,root)
%{_bindir}/enca
%{_bindir}/enconv
%{_libexecdir}/%{name}/extconv/*
%dir %{_libexecdir}/%{name}/extconv
%dir %{_libexecdir}/%{name}
%{_libdir}/libenca.so.*
%defattr(644,root,root)
%doc %{_mandir}/man1/enca.1*
%doc %{_mandir}/man1/enconv.1*
%defattr(-,root,root)
%doc AUTHORS COPYING ChangeLog ChangeLog.prelib FAQ INSTALL NEWS README README.devel THANKS TODO

%files devel
%defattr(-,root,root)
%{_includedir}/enca.h
%{_libdir}/pkgconfig/enca.pc
%{_libdir}/libenca.a
%{_libdir}/libenca.la
%{_libdir}/libenca.so
%doc %{_datadir}/gtk-doc/html/libenca/*
%doc %dir %{_datadir}/gtk-doc/html/libenca
%doc %dir %{_datadir}/gtk-doc/html
%doc %dir %{_datadir}/gtk-doc

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%changelog
* Sun Dec 18 2005 David Necas (Yeti) <yeti@physics.muni.cz>
- fixed 0644 permissions on doc directory
* Mon May 17 2004 David Necas (Yeti) <yeti@physics.muni.cz>
- doubled percents in changelog
* Mon Dec 22 2003 David Necas (Yeti) <yeti@physics.muni.cz>
- moved wrappers to libexec
* Thu Nov  6 2003 David Necas (Yeti) <yeti@physics.muni.cz>
- added b-piconv
- fixed HTML doc install paths
* Tue Oct 14 2003 David Necas (Yeti) <yeti@physics.muni.cz>
- testing whether $RPM_BUILD_ROOT is not /
- updated for new HTML doc location
- changed make -> %%__make, rm -> %%__rm
* Sat Aug  2 2003 David Necas (Yeti) <yeti@physics.muni.cz>
- cleaning $RPM_BUILD_ROOT in %%install
* Sat Jun 28 2003 David Necas (Yeti) <yeti@physics.muni.cz>
- removed --disable-gtk-doc, no longer needed
* Fri Jun 20 2003 David Necas (Yeti) <yeti@physics.muni.cz>
- added enca.pc to devel package
* Sat Jun 14 2003 David Necas (Yeti) <yeti@physics.muni.cz>
- updated description
- added --disable-gtk-doc
* Mon Dec 23 2002 David Necas (Yeti) <yeti@physics.muni.cz>
- added libenca.so
* Fri Dec 20 2002 David Necas (Yeti) <yeti@physics.muni.cz>
- fixed URL and Source to trific.ath.cx
* Mon Oct 21 2002 David Necas (Yeti) <yeti@physics.muni.cz>
- added FAQ to docs
* Thu Oct 10 2002 David Necas (Yeti) <yeti@physics.muni.cz>
- removed twice-listed %%{docdir}/html
* Sat Sep 21 2002 David Necas (Yeti) <yeti@physics.muni.cz>
- added b-umap
* Sun Sep 15 2002 David Necas (Yeti) <yeti@physics.muni.cz>
- added enconv
* Thu Aug 29 2002 David Necas (Yeti) <yeti@physics.muni.cz>
- removed bzip2-devel buildprereq
* Sat Aug 24 2002 David Necas (Yeti) <yeti@physics.muni.cz>
- added postinstall and postuninstall scriptlets
* Wed Aug 21 2002 David Necas (Yeti) <yeti@physics.muni.cz>
- updated to enca-0.10.0-pre2
- added libenca
- split into enca and enca-devel
- removed cache
- fixed HTML_DIR
* Tue Jul 10 2001 David Necas (Yeti) <yeti@physics.muni.cz>
- changed rpm macros in Source and URL to autoconf macros to ease debian/
  stuff generation
* Sun May 20 2001 David Necas (Yeti) <yeti@physics.muni.cz>
- added BuildPrereq: bzip2-devel
* Wed May  2 2001 David Necas (Yeti) <yeti@physics.muni.cz>
- changed group to standard (but much less appropriate) Applications/Text
- rpm macros are used instead of autoconf macros (after the first definition)
* Sun Mar 11 2001 David Necas (Yeti) <yeti@physics.muni.cz>
- added defattr, doc attributes
- uses global configure cache
- heavy use of predefined directories
- configure moved to build section as is usual
* Sun Feb 25 2001 David Necas (Yeti) <yeti@physics.muni.cz>
- updated to enca-0.9.0pre4 (including files and descriptions)
- added sed dependency
* Sun Oct 25 2000 David Necas (Yeti) <yeti@physics.muni.cz>
- updated to enca-0.7.5
* Sun Oct 11 2000 David Necas (Yeti) <yeti@physics.muni.cz>
- removed redundant Provides: enca
* Sun Oct  1 2000 David Necas (Yeti) <yeti@physics.muni.cz>
- updated to enca-0.7.1
- man page forced to be intstalled to ${prefix}/share/man
* Tue Sep 26 2000 David Necas (Yeti) <yeti@physics.muni.cz>
- updated to enca-0.7.0
- spec autogenerated by configure
* Tue Sep 19 2000 David Necas (Yeti) <yeti@physics.muni.cz>
- fixed not installing bcstocs
* Wed Sep 13 2000 David Necas (Yeti) <yeti@physics.muni.cz>
- first packaged (0.6.2)

