readonly infile="tests/assets/ls_tail"
readonly prog="xdp"

cat << __EOF__ >> .lldbinit && lldb --local-lldbinit && rm .lldbinit
settings set prompt "(${prog} lldb) "
settings set target.run-args ${infile}
command alias rr register read
command alias vars frame variable

target create ${prog}
__EOF__

