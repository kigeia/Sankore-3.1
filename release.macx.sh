# --------------------------------------------------------------------
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# ---------------------------------------------------------------------

#!/bin/bash

# Executables
QMAKE="/usr/local/Trolltech/Qt-4.7.3/bin/qmake"
MACDEPLOYQT="`pwd`/../Qt-sankore3.1/bin/macdeployqt"
DMGUTIL="`pwd`/../Sankore-ThirdParty/refnum/dmgutil/dmgutil.pl"
DSYMUTIL=/usr/bin/dsymutil
STRIP=/usr/bin/strip
PLISTBUDDY=/usr/libexec/PlistBuddy

# Directories
BUILD_DIR="build/macx/release"
PRODUCT_DIR="$BUILD_DIR/product"

function notify {
    GROWLNOTIFY=`which growlnotify`
    if [ -x "$GROWLNOTIFY" ]; then
        $GROWLNOTIFY --name uniboard-build --iconpath /Developer/Applications/Xcode.app --message "$1" "Uniboard"
    fi
    printf "\033[32m--->\033[0m $1\n"
}

function abort {
    printf "\033[31merror:\033[0m $1\n"
    exit 1
}

function warn {
    abort "$1"
}

function checkExecutable {
    if [ ! -x "$1" ]; then
        abort "$1 not found"
    fi
}

trap "defaults write com.mnemis.Uniboard.release Running -bool NO" EXIT

notify "Running Uniboard release script (`date`)"

script_is_running=`defaults read com.mnemis.Uniboard.release Running 2>/dev/null`
if [[ $? -eq 0 ]] && [[ "$script_is_running" = "1" ]]; then
    trap EXIT
    abort "another release script already running"
fi
defaults write com.mnemis.Uniboard.release Running -bool YES

# Check for executables
checkExecutable "$QMAKE"
checkExecutable "$MACDEPLOYQT"
checkExecutable "$DMGUTIL"
checkExecutable "$DSYMUTIL"
checkExecutable "$STRIP"
checkExecutable "$PLISTBUDDY"


# delete the build directory
notify "Cleaning ..."
rm -rf "$BUILD_DIR"

# generate Makefiles
notify "Generating Makefile ..."

QMAKE_CMD="$QMAKE -spec macx-g++"

$QMAKE_CMD

# build
notify "Compiling ..."
make -j4 release

VERSION=`cat "$BUILD_DIR/version"`
if [ ! -f "$BUILD_DIR/version" ]; then
    echo "version not found"
    exit 1
else
    LAST_COMMITED_VERSION="`git describe $(git rev-list --tags --max-count=1)`"
    if [ "v$VERSION" != "$LAST_COMMITED_VERSION" ]; then
	echo creating a tag with the version $VERSION
	git tag -a "v$VERSION" -m "Generated setup for v$VERSION"
	git push origin --tags
    fi
fi
  
if [ $? != 0 ]; then
    abort "compilation failed"
fi


NAME="Sankore 3.1"

DMG="$NAME.dmg"
VOLUME="/Volumes/$NAME"
APP="$PRODUCT_DIR/Sankore 3.1.app"
DSYM_NAME="$NAME (r$SVN_REVISION).dSYM"
DSYM="$PRODUCT_DIR/$DSYM_NAME"
GSYM_i386="$PRODUCT_DIR/$NAME i386.sym"
INFO_PLIST="$APP/Contents/Info.plist"

rm -f "$APP/Contents/Resources/empty.lproj"

notify "Removing .svn directories ..."
find "$APP" -name .svn -exec rm -rf {} \; 2> /dev/null

# set various version infomration in Info.plist
$PLISTBUDDY -c "Set :CFBundleVersion $SVN_REVISION" "$INFO_PLIST"
$PLISTBUDDY -c "Set :CFBundleShortVersionString $VERSION" "$INFO_PLIST"
$PLISTBUDDY -c "Set :CFBundleGetInfoString $NAME" "$INFO_PLIST"

# bundle Qt Frameworks into the app bundle
notify "Bulding frameworks ..."
$MACDEPLOYQT "$APP"

notify "Extracting debug information ..."
$DSYMUTIL "$APP/Contents/MacOS/Sankore 3.1" -o "$DSYM"
$STRIP -S "$APP/Contents/MacOS/Sankore 3.1"

notify "Creating dmg ..."
umount "$VOLUME" 2> /dev/null
$DMGUTIL --open --volume="$NAME" "$DMG"

cp -R "$APP" "$VOLUME"
ln -s /Applications "$VOLUME"

$DMGUTIL --set --iconsize=96 --toolbar=false --icon=resources/macx/UniboardDmg.icns "$VOLUME"
$DMGUTIL --set --x=20 --y=60 --width=580 --height=312 "$VOLUME"
$DMGUTIL --set --x=180 --y=160 "$VOLUME/`basename \"$APP\"`"
$DMGUTIL --set --x=400 --y=160 "$VOLUME/Applications"

$DMGUTIL --close --volume="$NAME" "$DMG"

notify "$NAME is built"

PRODUCT_DIR="install/mac/"

if [ ! -d "${PRODUCT_DIR}" ]; then
    mkdir -p "${PRODUCT_DIR}"
fi

mv "$DMG" "${PRODUCT_DIR}"

exit 0

