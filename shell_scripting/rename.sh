#!/bin/csh
# rename -- simple script to rename .txt files to .dat
#
if ($#argv < 1) then
    echo "Usage: $0 txt_file [ txt_file ... ]"
    exit 1
endif
#
foreach txt_file ($argv)
    echo $txt_file
    set dat_file = `echo $txt_file | sed s/.txt/.dat/`
    mv -f $txt_file $dat_file
end