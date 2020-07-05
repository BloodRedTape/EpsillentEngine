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
    info "Copying Game resources"
    cp -r ../engine/resources $1
    cat ../engine/misc/Project_main > $1/sources/main.cpp
}

function config_unix {
    info "Configuring Unix build system"
    cp ../engine/misc/Project_Makefile $1/Makefile
    touch $1/ProjectConfig.mk
    echo "GAME_TITLE := $1" > $1/ProjectConfig.mk 
    cat ../engine/misc/Project_Config >> $1/ProjectConfig.mk 
    cat ../engine/misc/Project_gitignore > $1/.gitignore
}


function config_windows {
    info "Configuring Windows build system"
    sed "s/TemplateProject/$1/g" ../engine/misc/Project_Solution > $1/$1.sln
    sed "s/TemplateProject/$1/g" ../engine/misc/Project_vcxproj > $1/$1.vcxproj
    cp ../engine/misc/Project_vcxproj_filters $1/$1.vcxproj.filters
}

if [ $# -ne 1 ] ; then
    error "Please, enter a project name"
fi

if [ -d "$1" ]; then
    error "this directory has already been created"
fi

create_project_structure "$1"
config_unix "$1"
config_windows "$1"
info "Done"
