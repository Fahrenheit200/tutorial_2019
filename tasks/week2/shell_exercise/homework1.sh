mkdir /tmp/scripts 
cd /tmp/scripts
cp -R /etc/pam.d ./test
sudo chown -R redhat ./test
sudo chmod -R o-rwx ./test