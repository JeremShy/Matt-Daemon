docker run --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -t -i --name matt_test -v "/Users/$(whoami)/Docker_binded":/bind --rm matt
