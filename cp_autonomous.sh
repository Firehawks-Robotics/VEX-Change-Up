
#definitions
side="controls/include//side.h"
controlssrc="controls/src/*"
controlsinclude="controls/include/*"

#All autonomous programs need to start with "Auto"
matchautonomousprograms=autonomous*

skillsautonomous=skills-autonomous


#now copy all files from the controls program except side
for dir in $matchautonomousprograms
do
    echo
    echo Copying to program \"${dir}\"

    #src
    find ${controlssrc} ! -name "side.h" -exec cp -vrfp {} ${dir}/src/ \;

    #include
    find ${controlsinclude} ! -name "side.h" -exec cp -vrfp {} ${dir}/include/ \;
done

#Copy all but autonomous AND side to skillsautonomous
echo
echo Copying to skills autonomous
find ${controlssrc} ! -name "side.h" ! -name "autonomous.cpp" -exec cp -vrfp {} $skillsautonomous/src/ \;
find ${controlsinclude} ! -name "side.h" -exec cp -vrfp {} $skillsautonomous/include/ \;

