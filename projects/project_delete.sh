#!/bin/bash

function error {
    echo "[ERROR]: $1"
    exit -1
}
function info {
    echo "[INFO]: $1"
}

function delete {
    info "Deleting project $1"
    rm -rf $1
    info "Done!"
}

if [ $# -ne 1 ]; then
    error "Please, enter a project name"
fi

if ! [ -d $1 ]; then
    error "This project does not exist"
fi

delete $1

