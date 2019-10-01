#author:breeze chou
#date 2019.9.29
#version 1.0
#
#




#!/bin/bash
i=`grep -o 'root'  /etc/passwd | cut -d: -f1 | head -n1`
[ -d /tmp/scripts ] || mkdir /tmp/scripts
if  cp -rf /etc/pam.d /tmp/scripts  ; then
    cd /tmp/scripts/
    mv pam.d/ test/
    if [ i = $0 ]; then
    chown -R redhat:root test/
    else
    useradd redhat
    chown -R redhat:root test/
    chmod -R o-rwx test/
    fi
fi
#done
#

