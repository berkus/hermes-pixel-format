#!/bin/sh

debug ()
# print out a debug message if DEBUG is a defined variable
{
  if test ! -z "$DEBUG"
  then
    echo "DEBUG: $1"
  fi
}

version_check ()
# check the version of a package
# first argument : package name (executable)
# second argument : optional path where to look for it instead
# third argument : source download url
# rest of arguments : major, minor, micro version
# all consecutive ones : suggestions for binaries to use
# (if not specified in second argument)
{
  PACKAGE=$1
  PKG_PATH=$2
  URL=$3
  MAJOR=$4
  MINOR=$5
  MICRO=$6

  # for backwards compatibility, we let PKG_PATH=PACKAGE when PKG_PATH null
  if test -z "$PKG_PATH"; then PKG_PATH=$PACKAGE; fi
  debug "major $MAJOR minor $MINOR micro $MICRO"
  VERSION=$MAJOR
  if test ! -z "$MINOR"; then VERSION=$VERSION.$MINOR; else MINOR=0; fi
  if test ! -z "$MICRO"; then VERSION=$VERSION.$MICRO; else MICRO=0; fi

  debug "major $MAJOR minor $MINOR micro $MICRO"
  
  for SUGGESTION in $PKG_PATH; do 
    COMMAND="$SUGGESTION"

    # don't check if asked not to
    test -z "$NOCHECK" && {
      echo -n "  checking for $COMMAND >= $VERSION ... "
    } || {
      # we set a var with the same name as the package, but stripped of
      # unwanted chars
      VAR=`echo $PACKAGE | sed 's/-//g'`
      debug "setting $VAR"
      eval $VAR="$COMMAND"
      return 0
    }

    debug "checking version with $COMMAND"
    ($COMMAND --version) < /dev/null > /dev/null 2>&1 || 
    {
      echo "not found."
      continue
    }
    # the following line is carefully crafted sed magic
    # you don't want to mess with it
    #pkg_version=`$COMMAND --version|head -n 1|sed 's/^[a-zA-z\.\ ()]*//;s/ .*$//'`
    pkg_version=`$COMMAND --version|head -n 1|sed 's/^.*) //'|sed 's/ (.*)//'`
    debug "pkg_version $pkg_version"
    # remove any non-digit characters from the version numbers to permit numeric
    # comparison
    pkg_major=`echo $pkg_version | cut -d. -f1 | sed s/[a-zA-Z\-].*//g`
    pkg_minor=`echo $pkg_version | cut -d. -f2 | sed s/[a-zA-Z\-].*//g`
    pkg_micro=`echo $pkg_version | cut -d. -f3 | sed s/[a-zA-Z\-].*//g`
    test -z "$pkg_major" && pkg_major=0
    test -z "$pkg_minor" && pkg_minor=0
    test -z "$pkg_micro" && pkg_micro=0
    debug "found major $pkg_major minor $pkg_minor micro $pkg_micro"

    #start checking the version
    debug "version check"

    # reset check
    WRONG=

    if [ ! "$pkg_major" -gt "$MAJOR" ]; then
      debug "major: $pkg_major <= $MAJOR"
      if [ "$pkg_major" -lt "$MAJOR" ]; then
        debug "major: $pkg_major < $MAJOR"
        WRONG=1
      elif [ ! "$pkg_minor" -gt "$MINOR" ]; then
        debug "minor: $pkg_minor <= $MINOR"
        if [ "$pkg_minor" -lt "$MINOR" ]; then
          debug "minor: $pkg_minor < $MINOR"
          WRONG=1
        elif [ "$pkg_micro" -lt "$MICRO" ]; then
          debug "micro: $pkg_micro < $MICRO"
	  WRONG=1
        fi
      fi
    fi

    if test ! -z "$WRONG"; then
      echo "found $pkg_version, not ok !"
      continue
    else
      echo "found $pkg_version, ok."
      # we set a var with the same name as the package, but stripped of
      # unwanted chars
      VAR=`echo $PACKAGE | sed 's/-//g'`
      debug "setting $VAR"
      eval $VAR="$COMMAND"
      return 0
    fi
  done

  echo "not found !"
  echo "You must have $PACKAGE installed to compile $package."
  echo "Download the appropriate package for your distribution,"
  echo "or get the source tarball at $URL"
  return 1;
}

die_check ()
{
  # call with $DIE
  # if set to 1, we need to print something helpful then die
  DIE=$1
  if test "x$DIE" = "x1";
  then
    echo
    echo "- Please get the right tools before proceeding."
    echo "- Alternatively, if you're sure we're wrong, run with --nocheck."
    exit 1
  fi
}

tool_run ()
{
  tool=$1
  options=$2
  echo "+ running $tool $options..."
  $tool $options || {
    echo
    echo $tool failed
    exit 1
  }
}

# this is specificly for mandrake 8.2
WANT_AUTOCONF_2_5=1; export WANT_AUTOCONF_2_5

version_check "aclocal" "$AUTOMAKE aclocal aclocal-1.7 aclocal-1.6 aclocal-1.5" \
		"ftp://ftp.gnu.org/pub/gnu/automake/" 1 5 || DIE=1

version_check "automake" "$AUTOMAKE automake automake-1.7 automake-1.6 automake-1.5" \
		"ftp://ftp.gnu.org/pub/gnu/automake/" 1 5 || DIE=1

# autoconf >= 2.50 is required here, earlier versions might fail at
# detecting some libraries
#
version_check "autoconf" "$AUTOCONF autoconf autoconf-2.54 autoconf-2.53 autoconf-2.52 autoconf-2.51 autoconf-2.50" \
		"ftp://ftp.gnu.org/pub/gnu/autoconf/" 2 50 || DIE=1

die_check $DIE

tool_run "$aclocal"

tool_run "$automake" "--add-missing"

tool_run "$autoconf"

# EOF #
