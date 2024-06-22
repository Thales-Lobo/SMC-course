#!/bin/bash

case "$1" in
    client)
        shift
        ./bin/client/client "$@"
        ;;
    server)
        shift
        ./bin/server/server "$@"
        ;;
    generate_graphs)
        shift
        python3 analysis/plot_delay.py "$@"
        ;;
    *)
        echo "Usage: $0 {client|server|generate_graphs} [arguments...]"
        exit 1
        ;;
esac
