mkdir /tmp/scripts
cd /tmp/scripts
cp -r /etc/pam.d /tmp/scripts/test
chown -R redhat /tmp/scripts/test
chomd -R o=--- /tmp/scripts/test
