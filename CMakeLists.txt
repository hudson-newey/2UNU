cmake_minimum_required(VERSION 3.10)

project(MyProject)

# Add each C file as an executable
add_executable(arch ./arch/arch.c)
add_executable(cat ./cat/cat.c)
add_executable(chown ./chown/chown.c)
add_executable(clear ./clear/clear.c)
add_executable(cmp ./cmp/cmp.c)
add_executable(cp ./cp/cp.c)
add_executable(date ./date/date.c)
add_executable(dir ./dir/dir.c)
add_executable(echo ./echo/echo.c)
add_executable(exit ./exit/exit.c)
add_executable(expand ./expand/expand.c)
add_executable(export ./export/export.c)
add_executable(false ./false/false.c)
add_executable(hostname ./hostname/hostname.c)
add_executable(ln ./ln/ln.c)
add_executable(logname ./logname/logname.c)
add_executable(ls ./ls/ls.c)
add_executable(man ./man/man.c)
add_executable(mkdir ./mkdir/mkdir.c)
add_executable(mv ./mv/mv.c)
add_executable(printf ./printf/printf.c)
add_executable(pwd ./pwd/pwd.c)
add_executable(rm ./rm/rm.c)
add_executable(rmdir ./rmdir/rmdir.c)
add_executable(sh ./sh/sh.c)
add_executable(sleep ./sleep/sleep.c)
add_executable(sort ./sort/sort.c)
add_executable(touch ./touch/touch.c)
add_executable(true ./true/true.c)
add_executable(tty ./tty/tty.c)
add_executable(uname ./uname/uname.c)
add_executable(uptime ./uptime/uptime.c)
add_executable(who ./who/who.c)
add_executable(whoami ./whoami/whoami.c)
add_executable(yes ./yes/yes.c)

# Set the output directory for the executables
set_target_properties(
    arch
    cat
    chown
    clear
    cmp
    cp
    date
    dir
    echo
    exit
    expand
    export
    false
    hostname
    ln
    logname
    ls
    man
    mkdir
    mv
    printf
    pwd
    rm
    rmdir
    sh
    sleep
    sort
    touch
    true
    tty
    uname
    uptime
    who
    whoami
    yes
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)