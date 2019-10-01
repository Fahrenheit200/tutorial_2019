#!/bin/sh

mkdir /tmp/scripts
cd /tmp/scripts
cp -r /etc/pam.d /tmp/scripts
mv pam.d test
sudo chown -R redhat test
sudo chmod -R 770 test
