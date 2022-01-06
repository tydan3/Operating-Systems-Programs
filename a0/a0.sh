# Question #1
# --------------------------------------------------------------------
echo ; echo “command \#1: ps aux \| wc -l”
ps aux | wc -l
# Question #2
# --------------------------------------------------------------------
echo ; echo “command \#2: ps -eo nlwp \| tail -n +2 \| awk \'{ num_threads += $1 } END { print num_threads }\'”
ps -eo nlwp | tail -n +2 | awk '{ num_threads += $1 } END { print num_threads }'
# Question #3
# --------------------------------------------------------------------
echo ; echo “command \#3: uname -r”
uname -r
# Question #4
# --------------------------------------------------------------------
echo ; echo “command \#4: lscpu \| egrep \'Model name\'”
lscpu | egrep 'Model name'
# Question #5
# --------------------------------------------------------------------
echo ; echo “command \#5: grep MemTotal /proc/meminfo”
grep MemTotal /proc/meminfo
# Question #6
# --------------------------------------------------------------------
echo ; echo “command \#6: df -h /”
df -h /
# Question #7
# --------------------------------------------------------------------
echo ; echo “command \#7: df -ih /”
df -ih /
# Question #8
# --------------------------------------------------------------------
echo ; echo “command \#8: ping -c 10 www.google.com”
ping -c 10 www.google.com
# Question #9
# --------------------------------------------------------------------
echo ; echo “command \#9: nmcli connection show”
nmcli connection show
# Question #10
# --------------------------------------------------------------------
echo ; echo “command \#10: df -T /”
df -T /
# Question #11
# --------------------------------------------------------------------
echo ; echo “command \#11: ip -o addr show scope global \| awk \'\{split\(\$4, a, \"/\"\)\; print \$2\" : \"a[1]\}\'”
ip -o addr show scope global | awk '{split($4, a, "/"); print $2" : "a[1]}'
# Question #12
# --------------------------------------------------------------------
