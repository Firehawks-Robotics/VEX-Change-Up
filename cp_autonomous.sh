
#definitions
side="controls/include//side.h"
controlssrc="controls/src/*"
controlsinclude="controls/include/*"

#All autonomous programs need to start with "Auto"
autonomousprograms=Auto*

#now copy all files from the controls program except side
for dir in $autonomousprograms
do
    echo
    echo Copying to program \"${dir}\"

    #src
    find ${controlssrc} ! -name "side.h" -exec cp -vrfp {} ${dir}/src/ \;

    #include
    find ${controlsinclude} ! -name "side.h" -exec cp -vrfp {} ${dir}/include/ \;
done

