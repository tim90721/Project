#!/bin/bash

echo $project_name
qt_project_filename="${project_name}.pro"
buildDir=./build
qmake -project -o ${buildDir}/${qt_project_filename}
sed -i '$a QT += widgets' ${buildDir}/${qt_project_filename}
sed -i 's/INCLUDEPATH.*$/INCLUDEPATH += \/home\/daitor\/Qt\/5.12.0\/gcc_64\/include \.\.\/src \.\.\/include /g' ${buildDir}/${qt_project_filename}
#sed -i 's/INCLUDEPATH.*$/INCLUDEPATH += \/home\/daitor\/Qt\/5.12.0\/gcc_64\/include \.\/src /g' ${buildDir}/${qt_project_filename}
if [ ! -d "./log/" ]; then
    echo "log directory does not exist"
    mkdir log
fi

qmake ${buildDir}/${qt_project_filename} -o ${buildDir}
make -C ${buildDir} && ./${buildDir}/${project_name}

