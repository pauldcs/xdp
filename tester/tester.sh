#!/bin/bash

set -uo pipefail

readonly PROG=$(basename $0)
readonly DEFAULT_PROGRAM="../hdump"
readonly DEFAULT_MODE="args"
readonly DEFAULT_INPUT_SUFFIX="in"
readonly DEFAULT_INPUT_DIRECTORY="tests"
readonly DEFAULT_OUTPUT_DIRECTORY="outfiles"
readonly DEFAULT_TIMEOUT=2

readonly GRN=$(tput setaf 2)
readonly RED=$(tput setaf 1)
readonly END=$(tput sgr0)

ShowUsage() {

    cat <<EOF

Usage: $0 [options]
Options
    -p   <program> (default: ${DEFAULT_PROGRAM})
          The program to test.

    -i   <input_directory> (default: ${DEFAULT_INPUT_DIRECTORY})
          The directory containing the input files.
    
    -a   <args>
          Extra arguments to pass to the program.
    
    -s   <input_file_suffix> (default: ${DEFAULT_INPUT_SUFFIX})
          The suffix of the input files. 
    
    -o   <output_directory> (default: ${DEFAULT_OUTPUT_DIRECTORY})
          The directory to write the output files to.
    
    -m   <mode> (default: ${DEFAULT_MODE})
          The mode in which to run the tests.
          Available modes:
              - args
              - path    
    -c    Don't do infile - outfile comparisons.
    
    -v    Run each test case through Valgrind.
  
    -r   <output_file>
          Redirect output (summary not included) to a file.
    
    -h    Show this help message.

EOF
}

while getopts "p:s:a:i:o:m:cvr:h" opt; do
    case $opt in
        p) program_name="$OPTARG";;
        m) mode="$OPTARG";;
        a) extra_args="$OPTARG";;
        s) input_file_suffix="$OPTARG";;
        i) input_directory="$OPTARG";;
        o) output_directory="$OPTARG";;
        v) run_under_valgrind=true;;
        r) do_redirection="$OPTARG";;
        c) compare=false;;
        h) ShowUsage; exit 0;;
        \?) ShowUsage; exit 1;;
    esac
done

program_name=${program_name:-$DEFAULT_PROGRAM}
mode=${mode:-$DEFAULT_MODE}
extra_args=${extra_args:=""}
input_file_suffix=${input_file_suffix:-$DEFAULT_INPUT_SUFFIX}
input_directory=${input_directory:-$DEFAULT_INPUT_DIRECTORY}
output_directory=${output_directory:-$DEFAULT_OUTPUT_DIRECTORY}
run_under_valgrind=${run_under_valgrind:-false}
do_redirection=${do_redirection:-false}
compare=${compare:-true}

ExitWithError() {
    >&2 printf "$PROG: %s\n" "${1}"
    exit 1
}

Output() {
    [[ "$do_redirection" != false ]] \
        && printf "%s\n" "${1}" >> "${do_redirection}" \
        || printf "%s\n" "${1}"
}

CheckPrerequisites() {
    [[ -x "${program_name}" ]] ||
        ExitWithError "${program_name}: Not an executable file (-p argument)" 

    [[ -d "${input_directory}" ]] ||
        ExitWithError "${input_directory}: Not found (-i argument)" 
    
    [[ -r "${input_directory}" ]] ||
        ExitWithError "${input_directory}: Not readable (-i argument)" 

    [[ -z "$(ls -A ${input_directory}/*.${input_file_suffix} 2> /dev/null)" ]] &&
        ExitWithError "${input_directory}: Is empty (-i argument)" 

    [[ -d "${output_directory}" ]] ||
        mkdir -vp "${output_directory}" &> /dev/null
    
    [[ -w "${output_directory}" ]] ||
        ExitWithError "${output_directory}: Not writable (-o argument)" 

    [[ "${run_under_valgrind}" == true ]] &&
    [[ ! -x "$(command -v valgrind)" ]]   &&
        ExitWithError "Valgrind: Not found (-v argument)" 
}

ArgsMode() {
    local input_file="${1}"
    local actual_output_file="${2}"
    local valgrind_log_file="${3}"

    if [[ "${run_under_valgrind}" == true ]];
        then
            timeout "${DEFAULT_TIMEOUT}"          \
            cat "${input_file}"                   \
            | xargs                               \
            valgrind                              \
                -q                                \
                --leak-check=full                 \
                --show-leak-kinds=all             \
                --track-origins=yes               \
                --log-file="${valgrind_log_file}" \
                --error-exitcode=1                \
                ./"${program_name}" ${extra_args} &> "${actual_output_file}"
        else
            timeout "${DEFAULT_TIMEOUT}" \
            cat "${input_file}"          \
            | xargs                      \
            ./"${program_name}" ${extra_args} &> "${actual_output_file}"
    fi

    exit_code=$?
    return $exit_code
}

PathMode() {
    local input_file="${1}"
    local actual_output_file="${2}"
    local valgrind_log_file="${3}"

    if [[ "${run_under_valgrind}" == true ]];
        then
            timeout "${DEFAULT_TIMEOUT}"          \
            valgrind                              \
                -q                                \
                --leak-check=full                 \
                --show-leak-kinds=all             \
                --track-origins=yes               \
                --log-file="${valgrind_log_file}" \
                --error-exitcode=1                \
                ./"${program_name}" ${extra_args} "${input_file}" &> "${actual_output_file}"
    else
        timeout "${DEFAULT_TIMEOUT}"                                               \
        ./"${program_name}" ${extra_args} "${input_file}" &> "${actual_output_file}"
    fi
    exit_code=$?
    return $exit_code
}

RunTest() {
    local name="${1}"
    local input_file="${2}"
    local actual_output_file="${3}"
    local valgrind_log_file="${4}"
    local expected_output_file="${5}"

    Output "$input_file"

    func="None"
    if   [[ "${mode}" == "args" ]]; then func='ArgsMode'
    elif [[ "${mode}" == "path" ]]; then func='PathMode'
    else
        Output "    └── Status: ${RED}Aborted${END}"
        ExitWithError "${mode}: Not supported"
    fi

    $func "${input_file}" "${actual_output_file}" "${valgrind_log_file}"

    exit_code="${?}"

    # Remove leading and trailing whitespaces from both the
    # expected and actual output
    # sed -i 's/^[ \t]*//;s/[ \t]*$//' "$actual_output_file"
    # sed -i 's/^[ \t]*//;s/[ \t]*$//' "$expected_output_file"

    [[ ! -f "${actual_output_file}" ]] \
        && {
            Output "    └── Status: ${RED}Incomplete${END}"
            Output "        └── Reason: Actual output not found"
            Output ""
            ((failed++))
            return
        }

    Output "    └── ${actual_output_file} (exit=${exit_code})"

    [[ "${exit_code}" = 124 ]] \
        && {
            Output "    └── Status: ${RED}TIMEOUT${END}"
            Output ""
            ((failed++))
            return 
        }

    if [[ "${compare}" == true ]]
        then
            if cmp -s "${actual_output_file}" "$expected_output_file"
                then
                    Output "    └── Status: ${GRN}OK${END}"
                    ((passed++))
                else
                    Output "    └── Status: ${RED}KO${END}"
                    Output "    └── Expected: $expected_output_file"
                    Output "    └── Actual: $actual_output_file"
                    Output ""
                    Output \
                        "$(\
                            2>&1                    \
                            diff --color            \
                            "$actual_output_file"   \
                            "$expected_output_file" \
                            | sed 's/^/        /'
                        )"
                    ((failed++))
            fi
        else
            ((skipped++))
    fi

    [[ -s "${valgrind_log_file}" ]] \
        && {
            sed -i 's/^==[0-9]*== //' "${valgrind_log_file}"
            Output "    └── Valgrind:"
            Output "        └── ${RED}MEMORY ERROR${END}"
            Output \
                "$(\
                    2>&1 cat "${valgrind_log_file}" \
                    | sed 's/^/      /'
                )"
            ((memory_errors++))
        }
    echo 
}


PrintSummary() {
    cat << EOF

    Summary: [${passed}/$((passed + failed + skipped))]
    --------------------------- 
    Memory errors: ${memory_errors}
    Tests Skipped: ${skipped}

EOF
}

CheckPrerequisites

passed=0
failed=0
skipped=0
memory_errors=0

for file in "${input_directory}"/*."${input_file_suffix}"; 
    do
        filename=$(basename -- "${file}")
        test_name="${filename%.*}"
 
        RunTest                                       \
            "${test_name}"                            \
            "${file}"                                 \
            "${output_directory}"/"${test_name}.out"  \
            "${output_directory}"/"${test_name}.valg" \
            "${input_directory}"/"${test_name}.out"
done

PrintSummary
rm -rf -- "${DEFAULT_OUTPUT_DIRECTORY}"

if [[ "${failed}" -eq 0 ]];
    then
        if [[ "${memory_errors}" -eq 0 ]];
            then
                exit 0
        fi
fi

exit 1

# Last update: 05.02.23