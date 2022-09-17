#1/bin/csh
set run_values = (10 100 1000)

if  ($#argv !=) then 
    echo $0 takes no arguments
    exit 1 
endif
#
foreach value ($run_values)
    echo Starting run with value = $value
    ./myprof $value >&! log$value
    if ($status) echo warning: problem during execution
end