#! /bin/sh
# @(#) $Id: test-convlist.sh,v 1.2 2003/11/17 12:27:39 yeti Exp $
# Purpose: check whether --list convertors and --version are consistent
. $srcdir/setup.sh
rm -f $TESTNAME.expected 2>/dev/null
$ENCA --list convertors | grep "^librecode$" >>$TESTNAME.expected
if $ENCA --version | grep " +librecode-interface " >/dev/null; then
  echo librecode >>$TESTNAME.actual
fi
$ENCA --list convertors | grep "^iconv$" >>$TESTNAME.expected
if $ENCA --version | grep " +iconv-interface " >/dev/null; then
  echo iconv >>$TESTNAME.actual
fi
$ENCA --list convertors | grep "^extern$" >>$TESTNAME.expected
if $ENCA --version | grep " +external-convertor " >/dev/null; then
  echo extern >>$TESTNAME.actual
fi
. $srcdir/finish.sh
rm -f $TESTNAME.expected 2>/dev/null
