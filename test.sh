git submodule update --init --recursive

# setup tarantool
curl http://download.tarantool.org/tarantool/1.6/gpgkey | sudo apt-key add -
release=`lsb_release -c -s`

sudo tee /etc/apt/sources.list.d/tarantool_1_6.list <<- EOF
deb http://download.tarantool.org/tarantool/1.6/debian/ $release main
deb-src http://download.tarantool.org/tarantool/1.6/debian/ $release main
EOF
sudo apt-get update > /dev/null
sudo apt-get -q -y install tarantool tarantool-dev

# test
cmake . -DCMAKE_BUILD_TYPE=RelWithDebInfo
make
make check
