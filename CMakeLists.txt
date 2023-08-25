cmake_minimum_required(VERSION 3.10)

project(2UNU)

# Add each C file as an executable
add_executable(arch ./arch/arch.c)

add_library(curl_lib STATIC ./curl/curl.c)

add_executable(base64 ./base64/base64.c)
target_include_directories(base64 PRIVATE include)
target_link_libraries(base64 PRIVATE crypto m)

add_executable(basename ./basename/basename.c)
add_executable(cat ./cat/cat.c)
add_executable(chgrp ./chgrp/chgrp.c)
add_executable(chown ./chown/chown.c)
add_executable(clear ./clear/clear.c)
add_executable(cmp ./cmp/cmp.c)

add_executable(cp ./cp/cp.c)
target_include_directories(curl_lib PRIVATE include)
target_link_libraries(curl_lib PRIVATE curl)

add_executable(date ./date/date.c)
add_executable(dir ./dir/dir.c)
add_executable(dircolors ./dircolors/dircolors.c)
add_executable(dirname ./dirname/dirname.c)
add_executable(dos2unix ./dos2unix/dos2unix.c)
add_executable(echo ./echo/echo.c)
add_executable(env ./env/env.c)
add_executable(exit ./exit/exit.c)
add_executable(expand ./expand/expand.c)
add_executable(export ./export/export.c)
add_executable(false ./false/false.c)
add_executable(groupadd ./groupadd/groupadd.c)
add_executable(head ./head/head.c)
add_executable(history ./history/history.c)
add_executable(hostname ./hostname/hostname.c)
add_executable(id ./id/id.c)
add_executable(kill ./kill/kill.c)
add_executable(link ./link/link.c)
add_executable(ln ./ln/ln.c)
add_executable(logname ./logname/logname.c)
add_executable(ls ./ls/ls.c)
add_executable(man ./man/man.c)
add_executable(mkdir ./mkdir/mkdir.c)
add_executable(mkfile ./mkfile/mkfile.c)
add_executable(mv ./mv/mv.c)
add_executable(nl ./nl/nl.c)
add_executable(pkill ./pkill/pkill.c)
add_executable(printenv ./printenv/printenv.c)
add_executable(printf ./printf/printf.c)
add_executable(pwd ./pwd/pwd.c)
add_executable(reboot ./reboot/reboot.c)
add_executable(rm ./rm/rm.c)
add_executable(rmdir ./rmdir/rmdir.c)
add_executable(sh ./sh/sh.c)
add_executable(shutdown ./shutdown/shutdown.c)
add_executable(sleep ./sleep/sleep.c)
add_executable(sort ./sort/sort.c)
add_executable(sum ./sum/sum.c)
add_executable(tac ./tac/tac.c)
add_executable(tail ./tail/tail.c)
add_executable(touch ./touch/touch.c)
add_executable(true ./true/true.c)
add_executable(tty ./tty/tty.c)
add_executable(uname ./uname/uname.c)
add_executable(uptime ./uptime/uptime.c)
add_executable(users ./users/users.c)

add_executable(wget ./wget/wget.c)
target_include_directories(wget PRIVATE include)
target_link_libraries(wget PRIVATE curl_lib)

add_executable(who ./who/who.c)
add_executable(whoami ./whoami/whoami.c)
add_executable(yes ./yes/yes.c)

# Set the output directory for the executables
set_target_properties(
    arch
    base64
    basename
    cat
    chgrp
    chown
    clear
    cmp
    cp
    curl_lib
    date
    dir
    dircolors
    dirname
    dos2unix
    echo
    env
    exit
    expand
    export
    false
    groupadd
    head
    history
    hostname
    id
    kill
    link
    ln
    logname
    ls
    man
    mkdir
    mkfile
    mv
    nl
    pkill
    printenv
    printf
    pwd
    reboot
    rm
    rmdir
    sh
    shutdown
    sleep
    sort
    sum
    tac
    tail
    touch
    true
    tty
    uname
    uptime
    users
    wget
    who
    whoami
    yes
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
