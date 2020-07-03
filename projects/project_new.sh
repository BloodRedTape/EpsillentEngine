#!/bin/bash

TEMPLATE=""

function error {
    echo "[ERROR]: $1"
    exit -1
}
function info {
    echo "[INFO]: $1"
}

function create_project_structure {
    info "Creating project structure"
    mkdir $1
    mkdir $1/out
    mkdir $1/sources
    mkdir $1/resources
    info "Copying Engine resources"
    cp -r ../engine/resources $1
}

function generate_makefiles {
    info "Configuring build system"
    cp ../engine/misc/Project_Makefile $1/Makefile
    touch $1/ProjectConfig.mk
    echo "GAME_TITLE := $1" > $1/ProjectConfig.mk 
    cat ../engine/misc/Project_Config >> $1/ProjectConfig.mk 
    cat ../engine/misc/Project_gitignore > $1/.gitignore
}

function example {
    echo "Do you want to load an example application? (y/n)"
    read answer
    shopt -s extglob
    if [ $answer = y ]
    then
        cat ../engine/misc/Project_main > $1/sources/main.cpp
    elif [ $answer = n ]
    then
        echo
    else
        example $1
    fi
}

if [ $# -ne 1 ] ; then
    error "Please, enter a project name"
fi

if [ -d "$1" ]; then
    error "this directory has already been created"
fi

create_project_structure "$1"
generate_makefiles "$1"
example "$1"
info "Done"
