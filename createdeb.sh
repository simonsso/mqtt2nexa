#!/bin/bash

APP="mqtt2nexa"

base=$PWD

#Make sure we dont have any old debs here...
rm -f *.deb 

# First part: 
# collect data and create a control file.

pushd .|| exit 2

#Or some git info...
VER=$(date +'%Y%m%d%H%M')
NUM="1"
ARCH=$(dpkg --print-architecture)

USER=$(git config user.name)
MAIL=$(git config user.email)

NAME=$APP"_"$VER"-"$NUM"_"$ARCH

mkdir -p $base/$NAME/DEBIAN || exit 10
control=$base/$NAME/DEBIAN/control

echo "Package: "$APP        >  $control
echo "Version: "$VER"-"$NUM >> $control
echo "Section: base"        >> $control
echo "Priority: optional"   >> $control
echo "Architecture: "$ARCH  >>  $control

echo "Depends: "            >>  $control
echo "Maintainer: "$USER" <"$MAIL">" >>  $control

cat >> $control << EOF
Description: Starfader rpi mqtt to pwm
  Exprimental debian package
EOF

#Misc git info...
## echo "  git describe: "$(git describe --tags)     >> $control
echo "  git log: "$(git log --oneline | head -n1) >> $control

qmake
make
#copy skeleton

(cd debian/; tar c . )|(cd $NAME ; tar x)
for i in `grep Default-Start $NAME/etc/init.d/$APP |sed s/.*://`
do
   install -d $NAME/etc/rc$i.d
   (cd $NAME/etc/rc$i.d ; ln -s ../init.d/$APP S80$APP)
done
for i in `grep Default-Stop $NAME/etc/init.d/$APP |sed s/.*://`
do
   install -d $NAME/etc/rc$i.d
   (cd $NAME/etc/rc$i.d ; ln -s ../init.d/$APP K20$APP)
done

install -d $NAME/usr/sbin
cp $APP $NAME/usr/sbin/

# And the create the package
popd
dpkg-deb --build $NAME || exit 40
rm -rf $NAME/ || exit 50

echo "Done..."
exit 0
