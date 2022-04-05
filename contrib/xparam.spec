Summary: XParam is a general-purpose librariy for parameter handling in C++
Name: xparam
Version: 1.22
Release: 1
Copyright: Revised GPL (GPL and LGPL compatible)
Group: System Environment/Libraries
URL: http://xparam.sourceforge.net/
Packager: Shachar Shemesh <xparamrpm@sun.consumer.org.il>
Source: http://prdownloads.sourceforge.net/xparam/%{name}-%{version}.tar.gz
BuildRoot: %_tmppath/%name-%version-root
Provides: %name = %version-%release

%package devel
Summary: XParam is a general-purpose librariy for parameter handling in C++
Group: Development/Libraries
Requires: %{name} = %{version}-%{release}
Provides: %{name}-devel = %{version}-{%release}

%description
XParam is an extensible, type-safe, non-intrusive, object-oriented tool
for general-purpose object serialization and deserialization in C++, good
for parsing command-line parameters and cross-program/cross-platform
communication. It can handle named parameters as well as object streams. It
recognizes class hierarchies, abstract interfaces, and polymorphism, and can
therefore serve as a plug-in management framework (e.g., for strategy
management).

%description devel
XParam is an extensible, type-safe, non-intrusive, object-oriented tool
for general-purpose object serialization and deserialization in C++, good
for parsing command-line parameters and cross-program/cross-platform
communication. It can handle named parameters as well as object streams. It
recognizes class hierarchies, abstract interfaces, and polymorphism, and can
therefore serve as a plug-in management framework (e.g., for strategy
management).

You need the development RPM in order to develop programs that use the XParam
library.

%prep
%setup -q %{name}-%{version}
tar cvzf doc/examples.tar.gz examples

%build
%configure --disable-config-examples
%__make
cat - << EOF > doc/README.Package
The "XPARAM_CLASSPATH" has been pointed at %_libdir/%{name}-plugins.
EOF

%install
DESTDIR=$RPM_BUILD_ROOT make install
install -d $RPM_BUILD_ROOT/%_libdir/%{name}-plugins
install -d $RPM_BUILD_ROOT/etc/profile.d
install contrib/25xparam.sh $RPM_BUILD_ROOT/etc/profile.d
install contrib/25xparam.csh $RPM_BUILD_ROOT/etc/profile.d
DESTDIR=$RPM_BUILD_ROOT make check

%post
/sbin/install-info --entry="`cat %_datadir/doc/%{name}-%{version}/infodescription`" \
	--section="Programming & development tools." \
	%{_infodir}/%{name}.info %{_infodir}/dir

%preun
if [ "$1" = 0 ]; then
	/sbin/install-info --remove \
		--entry="`cat %_datadir/doc/%{name}-%{version}/infodescription`" \
		--section="Programming & development tools." \
		%{_infodir}/%{name}.info %{_infodir}/dir
fi

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%_libdir/*.so*
%dir %_libdir/%{name}-plugins
/etc/profile.d/*
%_infodir/%{name}*
%doc AUTHORS BUGS ChangeLog INSTALL COPYING README TODO
%doc doc/*.html doc/infodescription doc/doc_examples doc/xparam.sgml

%files devel
%defattr(-,root,root)
%_libdir/*.a
%_libdir/*.la
%_includedir/*

%changelog
* Sat Nov 15 2002 Shachar Shemesh <xparamrpm@sun.consumer.org.il>
- Initial version

