#!/bin/bash
mkdir -p tmp/script/
cd tmp/script/
cp -r /etc/pam.d test/
chown -R redhat test/
chmod -R o-rwx test/
