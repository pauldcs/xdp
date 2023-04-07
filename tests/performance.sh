#!/bin/bash

set -euo pipefail

# /*----------------------------------------------------------------------------------------*/
readonly  __script__=$(basename "${0}")
readonly  __author__="pducos"
readonly __version__="1.0"
# /*----------------------------------------------------------------------------------------*/

readonly   CRESET="$(tput sgr0)"
readonly    CINFO="$(tput setaf 2; tput bold)"
readonly   CDEBUG="$(tput setaf 4; tput bold)"
readonly CWARNING="$(tput setaf 3; tput bold)"
readonly   CERROR="$(tput setaf 1; tput bold)"

function DisplayUsage()
{
    cat << EOF && exit 0
Usage: $(basename "${0}") [option]
Options:
    -v --version  display version of the script
    -h --help     display this help message

EOF
    exit 0
}

function Log ()
{
    # print a log message by level:
    #     - info
    #     - debug
    #     - warning
    #     - error
    local color=""
    local level="${1}"
    shift

    case "${level}" in
        info)    color=$CINFO ;;
        debug)   color=$CDEBUG ;;
        warning) color=$CWARNING ;;
        error)   color=$CERROR ;;
        *)       color=$CDEFAULT ;;
    esac

    >&2 printf "[%s%s%s] %s\n" "$color" "${level}" "$CRESET" "${*}";
}


function ExitError()
{
    # exit script with error message
    Log error "${1}";
    exit 1;
}

function __entry__()
{

# /*----------------------------------------------------------------------------------------*/
#[[ $(id -u) != "0" ]] && ExitError "This script must be run as root"

    Log info "Starting tests...";
    runs=10

    total_time=0
    avg_time=0

   for ((i=1; i<=$runs; i++))
    do
        exec_time=$(time ../xdp -n "107374180" <(cat /dev/urandom) > /dev/null)
        #exec_time=$(time hexdump -n "107374180" -C <(cat /dev/urandom) > /dev/null)
        sleep 0.1
    done
  
# /*----------------------------------------------------------------------------------------*/

}

if [[ "${#}" -gt 0 ]]
    then
    {
        case "${1}" in
            -h | --help) DisplayUsage ;;
            -v | --version) \
                printf "%s (%s) by %s\n" \
                    "${__script__}"  \
                    "${__version__}" \
                    "${__author__}" 
                exit 0 ;;
            
            # add arguments
            
            *) ExitError "Invalid argument: ${1}" ;;
        esac
    }
fi

__entry__ 
