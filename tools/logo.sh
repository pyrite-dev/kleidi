#!/bin/sh
# $Id$
povray +W256 +H256 +Ologo.png resource/logo/logo.pov
mv logo.png resource/logo/
magick resource/logo/logo.png -scale x64 resource/logo/logo64.png
