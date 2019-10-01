#!/bin/bash
mkdir /tmp/scripts
cd /tmp/scripts
cp  -a  /etc/pam.d   /tmp/scripts
mv pam.d test
chown -R lee test
chmod -R a-- test

