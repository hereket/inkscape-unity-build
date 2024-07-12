# set -x
set -e

mkdir -p __build
pushd __build

mkdir -p install_dir/share/locale
SRC=$(realpath ..)/src



CFLAGS="-std=c++20"
CFLAGS="$CFLAGS -fmax-errors=3"
# CFLAGS_MAIN="$CFLAGS_MAIN -Wfatal-errors"
# CFLAGS="$CFLAGS -g"
CFLAGS="$CFLAGS -Wno-deprecated"
CFLAGS="$CFLAGS -Wno-deprecated-declarations"
CFLAGS="$CFLAGS -DWITH_IMAGE_MAGICK=OFF -DWITH_GRAPHICS_MAGICK=ON"


#-------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------
START_MEASUREMENT () {
    GLOBAL_CURRENT_START_TIME=`date +%s.%N`
    GLOBAL_MEASURE_NAME=$1
}
END_MEASUREMENT () {
    current_time=`date +%s.%N`
    runtime=$( echo "$current_time - $GLOBAL_CURRENT_START_TIME" | bc -l )
    echo $GLOBAL_MEASURE_NAME: $runtime seconds
}
#--------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------
START_MEASUREMENT  'Copy data files'
mkdir -p install_dir/share/inkscape/
cp -r ../share/* install_dir/share/inkscape/
cp $SRC/../config.h.cmake $SRC/../__generated/config.h

PROJECT_NAME='inkscape'
PACKAGE_LOCALE_DIR='share/locale'
CMAKE_INSTALL_PREFIX=$(realpath .)/install_dir
INKSCAPE_DATADIR=$CMAKE_INSTALL_PREFIX/share

sed -i 's/cmakedefine/define/g' $SRC/../__generated/config.h
sed -i "s/\${PROJECT_NAME}/$PROJECT_NAME/g" $SRC/../__generated/config.h
sed -i "s#\${PACKAGE_LOCALE_DIR}#$PACKAGE_LOCALE_DIR#g" $SRC/../__generated/config.h
sed -i "s#\${CMAKE_INSTALL_PREFIX}#$CMAKE_INSTALL_PREFIX#g" $SRC/../__generated/config.h
sed -i "s#\${INKSCAPE_DATADIR}#$INKSCAPE_DATADIR#g" $SRC/../__generated/config.h
END_MEASUREMENT
#--------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------



START_MEASUREMENT  'Compile lib2geom.so'
CFLAGS_2GEOM=$CFLAGS
CFLAGS_2GEOM="$CFLAGS_2GEOM -I$SRC/3rdparty/2geom/include/"
CFLAGS_2GEOM="$CFLAGS_2GEOM -I$SRC/3rdparty/2geom/src/"
CFLAGS_2GEOM="$CFLAGS_2GEOM $(pkg-config --cflags glib-2.0)"
g++ -shared -fPIC \
    $CFLAGS_2GEOM \
    $SRC/3rdparty/2geom/src/2geom/all_geom.cpp \
    -o lib2geom.so
END_MEASUREMENT



START_MEASUREMENT  'Compile liblivarot_LIB.a'
CFLAGS_LIVAROT=$CFLAGS
CFLAGS_LIVAROT="$CFLAGS_LIVAROT -I$SRC/3rdparty/2geom/include/"
CFLAGS_LIVAROT="$CFLAGS_LIVAROT -I$SRC/"
CFLAGS_LIVAROT="$CFLAGS_LIVAROT $(pkg-config --cflags glib-2.0)"
CFLAGS_LIVAROT="$CFLAGS_LIVAROT $(pkg-config --cflags glibmm-2.68)"
CFLAGS_LIVAROT="$CFLAGS_LIVAROT $(pkg-config --cflags libxml-2.0)"
g++ -c $CFLAGS_LIVAROT $SRC/livarot/all_livarot.cpp -o all_livarot.o
ar rcs liblivarot_LIB.a all_livarot.o
END_MEASUREMENT




START_MEASUREMENT  'Compile libutil_LIB.a'
CFLAGS_UTIL=$CFLAGS
CFLAGS_UTIL="$CFLAGS_UTIL -I$SRC/"
CFLAGS_UTIL="$CFLAGS_UTIL $(pkg-config --cflags gtkmm-4.0)"
CFLAGS_UTIL="$CFLAGS_UTIL $(pkg-config --cflags glibmm-2.68)"
CFLAGS_UTIL="$CFLAGS_UTIL $(pkg-config --cflags atk)"
CFLAGS_UTIL="$CFLAGS_UTIL -I$SRC/3rdparty/2geom/include/"
CFLAGS_UTIL="$CFLAGS_UTIL $(pkg-config --cflags libxml-2.0)"
g++ -c $CFLAGS_UTIL $SRC/util/all_utils.cpp -o all_utils.o
ar rcs libutil_LIB.a all_utils.o
END_MEASUREMENT




START_MEASUREMENT  'Compile libuemf_LIB.a'
CFLAGS_UTIL=" -I$SRC/"
gcc $CFLAGS_UTIL -c $SRC/3rdparty/libuemf/all_uemf.c -o all_uemf.o
ar rcs libuemf_LIB.a all_uemf.o
END_MEASUREMENT




START_MEASUREMENT  'Compile libcroco_LIB.a'
CFLAGS_CROCO=-Wno-unused-result
CFLAGS_CROCO="$CFLAGS_CROCO -I$SRC/"
CFLAGS_CROCO="$CFLAGS_CROCO $(pkg-config --cflags glib-2.0)"
CFLAGS_CROCO="$CFLAGS_CROCO $(pkg-config --cflags libxml-2.0)"
gcc -c $CFLAGS_CROCO $SRC/3rdparty/libcroco/src/all_croco.c -o all_croco.o
ar rcs libcroco_LIB.a all_croco.o
END_MEASUREMENT




START_MEASUREMENT  'Compile libdepixelize_LIB.a'
CFLAGS_TRACER="$CFLAGS"
CFLAGS_TRACER="$CFLAGS_TRACER $(pkg-config --cflags glibmm-2.68)"
CFLAGS_TRACER="$CFLAGS_TRACER $(pkg-config --cflags gtkmm-4.0)"
CFLAGS_TRACER="$CFLAGS_TRACER -I$SRC/3rdparty/2geom/include/"
g++ -c $CFLAGS_TRACER $SRC/3rdparty/libdepixelize/kopftracer2011.cpp -o src_3rdparty_libdepixelize_kopftracer2011.o
ar rcs libdepixelize_LIB.a  src_3rdparty_libdepixelize_kopftracer2011.o
END_MEASUREMENT




START_MEASUREMENT  'Compile libavoid_LIB.a'
CFLAGS_AVOID="$CFLAGS"
CFLAGS_AVOID="$CFLAGS_AVOID -I$SRC/"
CFLAGS_AVOID="$CFLAGS_AVOID -I$SRC/3rdparty/adaptagrams"
g++ -c $CFLAGS_AVOID $SRC/3rdparty/adaptagrams/libavoid/all_avoid.cpp -o all_avoid.o
ar rcs libavoid_LIB.a all_avoid.o
END_MEASUREMENT




START_MEASUREMENT  'Compile libcola_LIB.a'
CFLAGS_COLA="$CFLAGS_COLA -I$SRC/"
CFLAGS_COLA="$CFLAGS_COLA -I$SRC/3rdparty/adaptagrams"
g++ -c $CFLAGS_COLA $SRC/3rdparty/adaptagrams/libcola/all_cola.cpp -o all_cola.o
ar rcs libcola_LIB.a all_cola.o
END_MEASUREMENT




START_MEASUREMENT  'Compile libvpsc_LIB.a'
CFLAGS_VPSC="$CFLAGS_VPSC -I$SRC/3rdparty/adaptagrams"
CFLAGS_VPSC="$CFLAGS_VPSC -I$SRC/"
g++ -c $CFLAGS_VPSC $SRC/3rdparty/adaptagrams/libvpsc/all_vpsc.cpp -o all_vpsc.o
ar rcs libvpsc_LIB.a all_vpsc.o
END_MEASUREMENT



START_MEASUREMENT  'Compile libautotrace_LIB.a'
CFLAGS_AUTOTRACE="$CFLAGS_AUTOTRACE -DHAVE_CONFIG_H"
CFLAGS_AUTOTRACE="$CFLAGS_AUTOTRACE -I$SRC/"
CFLAGS_AUTOTRACE="$CFLAGS_AUTOTRACE $(pkg-config --cflags glib-2.0)"
gcc -c $CFLAGS_AUTOTRACE $SRC/3rdparty/autotrace/all_autotrace.c -o all_autorace.o
ar rcs libautotrace_LIB.a all_autorace.o
END_MEASUREMENT



START_MEASUREMENT  'Compile libgc_LIB.a'
CFLAGS_INKGC="$CFLAGS -I$SRC/"
CFLAGS_INKGC="$CFLAGS_INKGC $(pkg-config --cflags glibmm-2.68)"
g++ -c $CFLAGS_INKGC $SRC/inkgc/gc.cpp -o src_inkgc_gc.o
ar rcs libgc_LIB.a src_inkgc_gc.o
END_MEASUREMENT





START_MEASUREMENT  'Compile inkscape binary'
CFLAGS_MAIN="$CFLAGS"
CFLAGS_MAIN="$CFLAGS_MAIN -w" # Disable all warnings temporarily
CFLAGS_MAIN="$CFLAGS_MAIN -DHAVE_POPPLER"
CFLAGS_MAIN="$CFLAGS_MAIN -DHAVE_CONFIG_H"
CFLAGS_MAIN="$CFLAGS_MAIN -D_FUNCTION_DEF"
CFLAGS_MAIN="$CFLAGS_MAIN -I$SRC/3rdparty/2geom/include/"
CFLAGS_MAIN="$CFLAGS_MAIN -I$SRC/3rdparty/adaptagrams/"
CFLAGS_MAIN="$CFLAGS_MAIN -I$SRC/"
CFLAGS_MAIN="$CFLAGS_MAIN -I$SRC/../__generated/"
CFLAGS_MAIN="$CFLAGS_MAIN -I$SRC/3rdparty/2geom/include/2geom"
CFLAGS_MAIN="$CFLAGS_MAIN $(pkg-config --cflags gtk4)"
CFLAGS_MAIN="$CFLAGS_MAIN $(pkg-config --cflags glib-2.0)"
CFLAGS_MAIN="$CFLAGS_MAIN $(pkg-config --cflags glibmm-2.68)"
CFLAGS_MAIN="$CFLAGS_MAIN $(pkg-config --cflags gtkmm-4.0)"
CFLAGS_MAIN="$CFLAGS_MAIN $(pkg-config --cflags libxml-2.0)"
CFLAGS_MAIN="$CFLAGS_MAIN $(pkg-config --cflags libxml-2.0)"
CFLAGS_MAIN="$CFLAGS_MAIN $(pkg-config --cflags poppler)"
CFLAGS_MAIN="$CFLAGS_MAIN $(pkg-config --cflags libcdr-0.1)"
CFLAGS_MAIN="$CFLAGS_MAIN $(pkg-config --cflags libvisio-0.1)"
CFLAGS_MAIN="$CFLAGS_MAIN $(pkg-config --cflags libwpg-0.3)"
CFLAGS_MAIN="$CFLAGS_MAIN $(pkg-config --cflags gtkmm-4.0)"
CFLAGS_MAIN="$CFLAGS_MAIN $(pkg-config --cflags GraphicsMagick++)"
LDFLAGS="$LDFLAGS -L."
LDFLAGS="$LDFLAGS -Wl,-rpath ."
LDFLAGS="$LDFLAGS -rdynamic"
LDFLAGS="$LDFLAGS -l2geom"
LDFLAGS="$LDFLAGS -lutil_LIB"
LDFLAGS="$LDFLAGS -lgc_LIB"
LDFLAGS="$LDFLAGS -ldepixelize_LIB"
LDFLAGS="$LDFLAGS -luemf_LIB"
LDFLAGS="$LDFLAGS -lautotrace_LIB"
LDFLAGS="$LDFLAGS -lavoid_LIB"
LDFLAGS="$LDFLAGS -lcola_LIB"
LDFLAGS="$LDFLAGS -lcroco_LIB"
LDFLAGS="$LDFLAGS -llivarot_LIB"
LDFLAGS="$LDFLAGS -lvpsc_LIB"
LDFLAGS="$LDFLAGS -lgc"
LDFLAGS="$LDFLAGS -lboost_filesystem"
LDFLAGS="$LDFLAGS -lpotrace"
LDFLAGS="$LDFLAGS -ldouble-conversion"
LDFLAGS="$LDFLAGS -lgio-2.0"
LDFLAGS="$LDFLAGS $(pkg-config --libs atk)"
LDFLAGS="$LDFLAGS $(pkg-config --libs glib-2.0)"
LDFLAGS="$LDFLAGS $(pkg-config --libs gmodule-2.0)"
LDFLAGS="$LDFLAGS $(pkg-config --libs gtk4)"
LDFLAGS="$LDFLAGS $(pkg-config --libs gtkmm-4.0)"
LDFLAGS="$LDFLAGS $(pkg-config --libs glibmm-2.68)"
LDFLAGS="$LDFLAGS $(pkg-config --libs libxml-2.0)"
LDFLAGS="$LDFLAGS $(pkg-config --libs sigc++-3.0)"
LDFLAGS="$LDFLAGS $(pkg-config --libs readline)"
LDFLAGS="$LDFLAGS $(pkg-config --libs poppler-glib)"
LDFLAGS="$LDFLAGS $(pkg-config --libs poppler)"
LDFLAGS="$LDFLAGS $(pkg-config --libs gsl)"
LDFLAGS="$LDFLAGS $(pkg-config --libs librevenge-stream-0.0)"
LDFLAGS="$LDFLAGS $(pkg-config --libs libvisio-0.1)"
LDFLAGS="$LDFLAGS $(pkg-config --libs libxslt)"
LDFLAGS="$LDFLAGS $(pkg-config --libs libwpg-0.3)"
LDFLAGS="$LDFLAGS $(pkg-config --libs libcdr-0.1)"
LDFLAGS="$LDFLAGS $(pkg-config --libs zlib)"
LDFLAGS="$LDFLAGS $(pkg-config --libs fontconfig)"
LDFLAGS="$LDFLAGS $(pkg-config --libs epoxy)"
LDFLAGS="$LDFLAGS $(pkg-config --libs pangofc)"
LDFLAGS="$LDFLAGS $(pkg-config --libs libpng)"
LDFLAGS="$LDFLAGS $(pkg-config --libs libjpeg)"
LDFLAGS="$LDFLAGS $(pkg-config --libs lcms2)"
LDFLAGS="$LDFLAGS $(pkg-config --libs pkg-config --libs openmp)"
LDFLAGS="$LDFLAGS $(pkg-config --libs GraphicsMagick++)"

# c++ $CFLAGS_MAIN \
#     $SRC/all.cpp \
#     -c -o inkscape.o \
#     $LDFLAGS \

# g++ -E $CFLAGS_MAIN $SRC/all.cpp  $LDFLAGS > /tmp/all.o

# c++ $CFLAGS_MAIN \
#     inkscape.o \
#     -o inkscape \
#     $LDFLAGS \
#     -v

c++ $CFLAGS_MAIN \
    $SRC/all.cpp \
    -o inkscape \
    $LDFLAGS 

END_MEASUREMENT


popd
