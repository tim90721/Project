#!/bin/bash

echo "project name: $project_name test"
qt_project_filename="${project_name}.pro"
buildDir=./build_test
newestFileinTestSrc=$(ls -t src/ | head -1)
echo "newest file $newestFileinTestSrc"
newerFile=$(find ../main/src/ -newer src/$newestFileinTestSrc | grep -E '.*cpp$|.*h$')
if [ "${newerFile}" != "" ]; then
    echo "newer file $newerFile"
    cp $newerFile ./src/
else
    echo "no new file"
fi

#cp ../main/src/*.h ./src/
test -e ./src/mainGUI.h && rm ./src/mainGUI.h
test -e ./src/mainGUI.cpp && rm ./src/mainGUI.cpp
test -e ./src/main.cpp && rm ./src/main.cpp
#rm ./src/mainGUI.h
#rm ./src/mainGUI.cpp
#rm ./src/main.cpp
qmake -project -o ${buildDir}/${qt_project_filename}
sed -i '$a QT += widgets' ${buildDir}/${qt_project_filename}
sed -i 's/INCLUDEPATH.*$/INCLUDEPATH += \/home\/daitor\/Qt\/5.12.0\/gcc_64\/include \./g' ${buildDir}/${qt_project_filename}
qmake ${buildDir}/${qt_project_filename} -o ${buildDir}
make -C ${buildDir} && ./${buildDir}/${project_name}

