name=$0
input=$1
arch=

function usage {
    echo "usage: $name [type]"
    echo "  1      arm64-v8a"
    echo "  2      armeabi-v7a"
    echo "  3      x86_64"
    echo "  4      x86"
    echo "  e.g) glog_test.sh 1"
    exit 0
}

if [[ "$input" -eq 0 ]]
then
    usage
elif [[ "$input" -eq 1 ]]
then
    arch="arm64-v8a"
elif [[ "$input" -eq 2 ]]
then
    arch="armeabi-v7a"
elif [[ "$input" -eq 3 ]]
then
    arch="x86_64"
elif [[ "$input" -eq 4 ]]
then
    arch="x86"
else
    usage
fi

adb push ./scanner/build/intermediates/cmake/debug/obj/$arch/libscanner.so /data/local/tmp/
adb push ./scanner/build/intermediates/cmake/debug/obj/$arch/scanner_tester /data/local/tmp/
adb shell chmod 775 /data/local/tmp/scanner_tester
adb shell "LD_LIBRARY_PATH=${LD_LIBRARY}:/data/local/tmp /data/local/tmp/scanner_tester"
