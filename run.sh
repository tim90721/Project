#!/bin/bash

echo $project_name
qt_project_filename="${project_name}.pro"
buildDir=./build
qmake -project -o ${buildDir}/${qt_project_filename}
sed -i '$a QT += widgets' ${buildDir}/${qt_project_filename}
sed -i 's/INCLUDEPATH.*$/INCLUDEPATH += \/home\/daitor\/Qt\/5.12.0\/gcc_64\/include \./g' ${buildDir}/${qt_project_filename}
qmake ${buildDir}/${qt_project_filename} -o ${buildDir}
make -C ${buildDir} 
./${buildDir}/${project_name}
