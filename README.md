# mini-docker: illustrate what docker really is in 100 lines of C/C++

This is a reference C/C++ implemetation of [Containers From Scratch • Liz Rice • GOTO 2018](https://www.youtube.com/watch?app=desktop&v=8fi7uSYlOdc&feature=youtu.be),
which illustrates the idea of docker in a few lines of Go. A detailed explanation of each line of code can be found on my [Zhihu answer](https://www.zhihu.com/question/28300645/answer/2488146755).


To test the filesystem isolation of this mini-docker, you must first have an extra ubuntu filesystem for mini-docker running and mounting on.
You can prepare this from your own ubuntu with following commands:
```
sudo tar -cpf ubuntu-fs.tar --exclude=/home --one-file-system /
mv ubuntu-fs.tar /parent/path/to/mini-docker
cd /parent/path/to/mini-docker
mkdir ubuntu-fs
mv ubuntu-fs.tar ubuntu-fs
cd ubuntu-fs
sudo tar xf ubuntu-fs.tar
```
[Here](https://askubuntu.com/questions/524418/how-would-i-use-tar-for-full-backup-and-restore-with-system-on-ssd-and-home-on-h) is a detailed explanation
of the `tar` command above. Note that I generally execute all above commands under my `$HOME`, so the `ubuntu-fs.tar` is also excluded by
`--exclude=/home` option. If you don't execute these commands under your `$HOME`, you may specify `ubuntu-fs.tar` manually.

After the prerparation above, you have a `ubuntu-fs` folder in `mini-docker`'s parent path. Now you can test it:
```
make 
sudo make run
```
You will see output as following:
```
./mocker run /bin/bash
Parent running /bin/bash as 43378
Child running /bin/bash as 1
root@container:/# 
```
which means, hostname is isolated. And you `ps aux` to see:
```
root@container:/# ps aux
USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root           1  0.0  0.0  12916  4216 ?        S    20:21   0:00 /bin/bash
root          10  0.0  0.0  14568  3524 ?        R+   20:22   0:00 ps aux
```
This implies, pid namespace is isolated. `ls` to see:
```
root@container:/# ls
bin  boot  cdrom  dev  etc  lib  lib32  lib64  libx32  lost+found  media  mnt  opt  proc  root  run  sbin  snap  srv  swapfile  sys  tmp  ubuntu-fs.tar  usr  var
```
Filesystem is isolated too, you can even find `ubuntu-fs.tar` under your `/`.

List proc pseudo-filesystem mounts in host to find container mount points are invisible out of container:
```
host@linux:~/mini-docker$ cat /proc/mounts | grep ^proc
proc /proc proc rw,nosuid,nodev,noexec,relatime 0 0
```
