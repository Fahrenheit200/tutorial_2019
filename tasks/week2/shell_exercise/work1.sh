#!/bin/bash
if [ ! -d /tmp/scripts ];then
    mkdir /tmp/scripts
fi
cd /tmp/scripts
if cp -r /etc/pam.d /tmp/scripts ; then
    if [  -d /test/pam.d ];then
        mv pam.d/ test/
    fi
    useradd redhat
    chown -R redhat:root test/
    chmod -R o-rwx test/
fi
