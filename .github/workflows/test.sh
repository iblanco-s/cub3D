#!/bin/bash
execPath="Cub3D"
makePath="."
mapsPath='maps/'

termwidth="$(tput cols)"
green='\e[1;32m'
yellow='\e[93m'
blueBg='\e[46m'
blue='\e[34m'
red='\e[31m'
end='\e[0m'
passed=0
failed=0
total=0

head () {
  padding="$(printf '%0.1s' \#{1..500})"
  printf "\n${yellow}%*.*s %s %*.*s${end}\n" 0 "$(((termwidth-5-${#1})/2))" "$padding" "  $1  " 0 "$(((termwidth-6-${#1})/2))" "$padding"
}

log () {
  padding="$(printf '%0.1s' ={1..500})"
  printf "${blue}%*.*s %s %*.*s${end}\n" 0 "$(((termwidth-5-${#1})/2))" "$padding" "  $1  " 0 "$(((termwidth-6-${#1})/2))" "$padding"
}

pass () {
  let "passed+=1"
  padding="$(printf '%0.1s' -{1..500})"
  printf "${green}%*.*s %s %*.*s${end}\n\n" 0 "$(((termwidth-5-8)/2))" "$padding" " Passed " 0 "$(((termwidth-6-${#1})/2))" "$padding"
}

fail () {
  let "failed+=1"
  padding="$(printf '%0.1s' -{1..500})"
  printf "${red}%*.*s %s %*.*s${end}\n\n" 0 "$(((termwidth-5-8)/2))" "$padding" " Failed " 0 "$(((termwidth-6-${#1})/2))" "$padding"
}

launch () {
  log $1
  let "total+=1"
  if ./${execPath} ${mapsPath}$1;
  then
    if [ "$2" = "pass" ]; then
      pass
    else
      fail
    fi
  else
    if [ "$2" = "pass" ]; then
      fail
    else
      pass
    fi
  fi
}

result () {
  if [ "$failed" -eq 0 ]; then
    printf "${green}YEAH ! All tests successfully passed ! Good job !${end}\n"
  else
    printf "${green}${passed}${end} tests passed, ${red}${failed}${end} tests failed.\n"
    printf "Don't worry, im sure you can fix it ! Keep it up !\n"
  fi
}

generate_junit_report () {
  echo '<?xml version="1.0" encoding="UTF-8"?>
  <testsuites>
    <testsuite name="Cub3D Tests" tests="'$total'" failures="'$failed'">
      <testcase name="Resolution Tests" status="'$([[ $failed_resolution -eq 0 ]] && echo "passed" || echo "failed")'"/>
      <testcase name="NO Texture Tests" status="'$([[ $failed_no_texture -eq 0 ]] && echo "passed" || echo "failed")'"/>
      <testcase name="RGB Tests" status="'$([[ $failed_rgb -eq 0 ]] && echo "passed" || echo "failed")'"/>
      <testcase name="Spawn Tests" status="'$([[ $failed_spawn -eq 0 ]] && echo "passed" || echo "failed")'"/>
      <testcase name="Working Maps Tests" status="'$([[ $failed_working_maps -eq 0 ]] && echo "passed" || echo "failed")'"/>
    </testsuite>
  </testsuites>'
}

head "Infos"
log "Make logs"
make -C ${makePath}
log "Date:"
date
log "Last commit:"
git --no-pager log --decorate=short --pretty=oneline -n1

failed_resolution=0
head "Testing Resolution"
launch "errors/map-res-0.cub" "fail" || let "failed_resolution+=1"
launch "errors/map-res-1.cub" "fail" || let "failed_resolution+=1"
launch "errors/map-res-2.cub" "fail" || let "failed_resolution+=1"
launch "errors/map-res-3.cub" "fail" || let "failed_resolution+=1"
launch "errors/map-res-4.cub" "fail" || let "failed_resolution+=1"

failed_no_texture=0
head "Testing NO texture"
launch "errors/map-no-0.cub" "fail" || let "failed_no_texture+=1"
launch "errors/map-no-1.cub" "fail" || let "failed_no_texture+=1"
launch "errors/map-no-2.cub" "fail" || let "failed_no_texture+=1"
launch "errors/map-no-3.cub" "fail" || let "failed_no_texture+=1"
launch "errors/map-no-4.cub" "fail" || let "failed_no_texture+=1"

failed_rgb=0
head "Testing RGB"
launch "errors/map-rgb-0.cub" "fail" || let "failed_rgb+=1"
launch "errors/map-rgb-1.cub" "fail" || let "failed_rgb+=1"
launch "errors/map-rgb-2.cub" "fail" || let "failed_rgb+=1"
launch "errors/map-rgb-3.cub" "fail" || let "failed_rgb+=1"
launch "errors/map-rgb-4.cub" "fail" || let "failed_rgb+=1"

failed_spawn=0
head "Testing spawns"
launch "errors/map-spawn-0.cub" "fail" || let "failed_spawn+=1"
launch "errors/map-spawn-1.cub" "fail" || let "failed_spawn+=1"
launch "errors/map-spawn-2.cub" "fail" || let "failed_spawn+=1"

log "Notes:"
printf "If a test is successful you should close the opened Cub3d to continue.\n"
printf "If it failed your Cub3d should handle this error and print a message accordingly.\n"

failed_working_maps=0
head "Testing working maps"
launch "weirds/map-triangle.cub" "pass" || let "failed_working_maps+=1"
launch "weirds/map-triangle2.cub" "pass" || let "failed_working_maps+=1"
launch "weirds/map-litle.cub" "pass" || let "failed_working_maps+=1"

head "DONE"
result

# Generate JUnit XML report
generate_junit_report > test-results.xml
